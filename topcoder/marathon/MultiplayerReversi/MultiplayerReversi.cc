#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <set>
#include <vector>

//#define DBG
#define DEPTH 5
#define MOB_WEIGHT 0
#define CORNER_WEIGHT_MIN 40
#define CORNER_WEIGHT_MAX 40
#define MID_WEIGHT 2
#define SIDE_WEIGHT_MIN 6
#define SIDE_WEIGHT_MAX 2.5
#define PRE_SIDE_WEIGHT 2
#define WEIGHT 2
#define BRANCH 100
#define SORT false
#define INF 1E100

using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;

ll branches;
ll calls;

vector<string> toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  vector<string> ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
  }   
  free(ch);   
  return ret;   
}   

class ReversiState {
 public:
  ReversiState(const VS &board, int player)
    : players_(0),
      player_(player),
      n_(board.size()),
      moves_(0),
      empty_(0),
      next_move_x_(0),
      next_move_y_(-1) {
    memset(board_, 0, sizeof(board_));
    for (int i = 0; i < 5; ++i) {
      counts_[i] = 0;
    }
    counts_[0] = n_ * n_;
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        if (board[i][j] != '.') {
          ++empty_;
        }
      }
    }
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        if (board[i][j] != '.') {
          SetPlayer(i, j, board[i][j] - '0');
          players_ = max(players_, board[i][j] - '0');
        }
      }
    }
  }

  ReversiState(const ReversiState &copy)
    : player_(copy.player_),
      players_(copy.players_),
      n_(copy.n_),
      moves_(0),
      empty_(copy.empty_),
      next_move_x_(0),
      next_move_y_(-1) {
    memcpy(board_, copy.board_, sizeof(board_));
    memcpy(counts_, copy.counts_, sizeof(counts_));
  }

  bool operator=(const ReversiState &copy) {
    player_ = (copy.player_);
    players_ = (copy.players_);
    empty_ = (copy.empty_);
    n_ = (copy.n_);
    moves_ = 0;
    next_move_x_ = 0;
    next_move_y_ = -1;
    memcpy(board_, copy.board_, sizeof(board_));
    memcpy(counts_, copy.counts_, sizeof(counts_));
  }

  virtual ~ReversiState() { }

  virtual bool NextState(ReversiState *next_state, vector<int> *move) {
    while (true) {
      ++next_move_y_;
      if (next_move_y_ == n_) {
        ++next_move_x_;
        next_move_y_ = 0;
      }
      if (next_move_x_ == n_) {
        if (moves_ == 0) {
          next_state->player_ = next_state->player_ % players_ + 1;
          ++moves_;
          return true;
        }
        return false;
      }
      next_state->empty_ = empty_ - 1;
      if (next_state->DoMove(next_move_x_, next_move_y_)) {
        (*move)[0] = next_move_x_;
        (*move)[1] = next_move_y_;
        ++moves_;
        next_state->player_ = next_state->player_ % players_ + 1;
        return true;
      }
    }
    return false;
  }

  virtual int GetPlayer() const {
    // MultiplayerMinMax uses 0-based players
    return player_ - 1;
  }
  
  void PrintDebugString() const {
    for (int i = 0; i < 12; ++i) {
      fprintf(stderr, "%08x\n", board_[i]);
    }
  }

  void ComputeMobility() {
    memset(mobility_, 0, sizeof(mobility_));
    if (MOB_WEIGHT == 0) return;
    int dx[] = { 1, 1, 1, -1, -1, -1, 0 , 0 };
    int dy[] = { 1, -1, 0, 1, -1 , 0, 1, -1};

    for (int x = 0; x < n_; ++x) {
      for (int y = 0; y < n_; ++y) {
        if (GetPlayer(x, y) != 0) continue;
        int done[5] = {0};
        int num_done = 0;
        for (int i = 0; i < 8; ++i) {
          int nx = x + dx[i];
          int ny = y + dy[i];
          int c = 0;
          int nomob = 0;
          while (inbound(nx, ny)) {
            int npl = GetPlayer(nx, ny);
            if (npl == 0) {
              break;
            }
            if (done[npl]) {
              nx += dx[i];
              ny += dy[i];
              c++;
              continue;
            }
            if (c == 0) {
              nomob = npl;
            } else if (npl != nomob) {
              mobility_[npl] += MOB_WEIGHT;
              done[npl] = 1;
              ++num_done;
            }
            if (num_done == players_) {
              break;
            }
            nx += dx[i];
            ny += dy[i];
            c++;
          }
          if (num_done == players_) {
            break;
          }
        }
      }
    }
  }

  double counts_[5];
  int mobility_[5];
 private:
  inline double Normalize(double max, double min) {
    return min + (max - min) * empty_ / (int)(n_ * n_);
  }
  inline double GetWeight(int row, int col) {
    if (row == 0 && col == 0) return Normalize(CORNER_WEIGHT_MAX, CORNER_WEIGHT_MIN);
    if (row == 0 && col == n_ - 1) return Normalize(CORNER_WEIGHT_MAX, CORNER_WEIGHT_MIN);
    if (row == n_ - 1 && col == 0) return Normalize(CORNER_WEIGHT_MAX, CORNER_WEIGHT_MIN);
    if (row == n_ - 1 && col == n_ - 1) return Normalize(CORNER_WEIGHT_MAX, CORNER_WEIGHT_MIN);
    if (row == 0 || col == 0) return Normalize(SIDE_WEIGHT_MAX, SIDE_WEIGHT_MIN);
    if (row == n_ - 1 || col == n_ - 1) return Normalize(SIDE_WEIGHT_MAX, SIDE_WEIGHT_MIN);
    if (row >= 2 * n_ / 4 && col >= 2 * n_ / 4 && row <= 3 * n_ / 4 && col <= 3 * n_ / 4) return Normalize(MID_WEIGHT, WEIGHT);
    return WEIGHT;
  }

  inline void SetPlayer(int row, int col, int player) {
    ll mask = (0xFLL << (col << 2));
    int old_player = (board_[row] & mask) >> (col << 2);
    board_[row] &= ~mask;
    board_[row] |= (long long)player << (col << 2);

    counts_[old_player] -= GetWeight(row, col);
    counts_[player] += GetWeight(row, col);
  }

  inline int GetColumn(ll board_row, int col) const {
    return (board_row & (0xFLL << (col << 2))) >> (col << 2);
  }

  inline int GetPlayer(int row, int col) const {
    return GetColumn(board_[row], col);
  }

  inline void SetBoard(int startx, int starty, int count, int dx, int dy, int player) {
    while (count) {
      SetPlayer(startx, starty, player);
      startx += dx;
      starty += dy;
      --count;
    }
  }

  inline bool DoMove(int x, int y) {
    if (GetPlayer(x, y) != 0) return false;
    int dx[] = { 1, 1, 1, -1, -1, -1, 0 , 0 };
    int dy[] = { 1, -1, 0, 1, -1 , 0, 1, -1};

    for (int i = 0; i < 8; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      int c = 0;
      while (inbound(nx, ny)) {
        int npl = GetPlayer(nx, ny);
        if (npl == 0) {
          break;
        }
        if (npl == player_) {
          if (c > 0) {
            SetBoard(x, y, c, dx[i], dy[i], player_);
            return true;
          } else {
            break;
          }
        }
        nx += dx[i];
        ny += dy[i];
        c++;
      }
    }

    return false;
  }

  inline bool inbound(int x, int y) {
    return x >= 0 && x < n_ && y >= 0 && y < n_;
  }

  int player_;
  int players_;
  // 4 bits represent one cell
  ll board_[12];
  int n_;

  int empty_;
  int moves_;
  int next_move_x_;
  int next_move_y_;

};

class MultiplayerMinMax {
 public:
   MultiplayerMinMax(const int players, const int max_depth)
     : players_(players),
       max_depth_(max_depth) { }

   void FindBestMove(ReversiState *initial_state, vector<int> *move, double *result) const;

 private:
   void InternalFindBestMove(ReversiState *current_state, double alpha, double beta, int depth, vector<int> *move, double *result) const;

   const int players_;
   const int max_depth_;
};

void MultiplayerMinMax::FindBestMove(ReversiState *initial_state,
                                     vector<int> *best_move,
                                     double *best_result) const {
  InternalFindBestMove(initial_state, 0, INF, 0, best_move, best_result);
}

void MultiplayerMinMax::InternalFindBestMove(ReversiState *current_state,
                                             double alpha,
                                             double beta,
                                             int current_depth,
                                             vector<int> *best_move,
                                             double *best_result) const {
  if (current_depth == max_depth_) {
    memcpy(best_result, current_state->counts_, sizeof(current_state->counts_));
    if (MOB_WEIGHT == 0) return;
    current_state->ComputeMobility();
    for (int i = 0; i < players_; ++i) {
      best_result[i] += current_state->mobility_[i];
    }
//    for (int i = 0; i < players_; ++i) {
//      fprintf(stderr, "%lf ", best_result->Score(i));
//    }
//    fprintf(stderr, "\n");
//    current_state->PrintDebugString();
    return;
  }

  int current_player = current_state->GetPlayer();

/*  vector<pair<ReversiState, vector<int> > > next_states;
  next_states.reserve(30);
  vector<pair<int, int> > scores;
  scores.reserve(30);
  int i = 0;
  next_states.push_back(make_pair(ReversiState(*current_state), vector<int> (2, -1)));
  while (current_state->NextState(&next_states.back().first, &next_states.back().second)) {
    if (current_player == 0) {
      scores.push_back(make_pair(next_states.back().first.counts_[1], i));
    } else {
      scores.push_back(make_pair(-next_states.back().first.counts_[1], i));
    }
    next_states.push_back(make_pair(ReversiState(*current_state), vector<int> (2, -1)));
    ++i;
  }
  next_states.erase(next_states.begin() + next_states.size() - 1, next_states.end());
  if (SORT)
  sort(scores.rbegin(), scores.rend()); */

  double current_result[5];
  vector<int> move(2, -1);
  double best_result_score = -INF;
  ++calls;
//  int curr = 0;
//  while (curr < min(BRANCH, (int)scores.size())) {
  while (true) {
    ReversiState next_state(*current_state);
    if (!current_state->NextState(&next_state, &move)) {
      break;
    }
     
    vector<int> other_move;
//    InternalFindBestMove(&next_states[scores[curr].second].first, alpha, beta, current_depth + 1, &other_move, current_result);
    InternalFindBestMove(&next_state, alpha, beta, current_depth + 1, &other_move, current_result);
    ++branches;

    double current_result_score = 0;
//    for (int i = 0; i < players_; ++i) {
//      if (current_depth == 0)
//        fprintf(stderr, "%lf ", current_result[i + 1]);
/*      if (i == current_player) {
        // Add for the current player
        current_result_score += current_result[i + 1];
      } else {
        // Subtract scores of other players
        current_result_score -= current_result[i + 1];
      }*/
//    }
//    if (current_depth == 0) 
//      fprintf(stderr, "\n%d %d\n", move[0], move[1]); 
    if (current_player == 0) {
      current_result_score = current_result[1];
    } else {
      current_result_score = -current_result[1];
    }
    if (current_result_score > best_result_score) {
//      *best_move = next_states[scores[curr].second].second;
      *best_move = move;
      memcpy(best_result, current_result, sizeof(current_result));
      best_result_score = current_result_score;
      if (current_player == 0) {
        alpha = max(alpha, best_result[1]);
        if (best_result[1] > beta) break;
      } else {
        beta = min(best_result[1], beta);
        if (best_result[1] < alpha) break;
      }
    }
//    ++curr;
  }
}

class MultiplayerReversi {
  public:
    vector<int> getNextMove(vector<string> board) {
      int players = 0;
      for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
          if (board[i][j] != '.') {
            players = max(players, board[i][j] - '0');
          }
        }
      }
      MultiplayerMinMax min_max(players, DEPTH);
      ReversiState initial_state(board, 1);
      double result[5];
      VI ret;
      min_max.FindBestMove(&initial_state, &ret, result);
      swap(ret[0], ret[1]);
      return ret;
    }
  private:

};

int main(void) {
  MultiplayerReversi obj;
  char buff[500];
  vector<string> board;
  vector<int> move;

  while(true) {
    board.clear();
    branches = 0;
    calls = 0;
    int N;
    if (scanf("%d", &N) != 1) {
      break;
    }
    getchar();
    fgets(buff, sizeof(buff), stdin);
    vector<string> board = toks(buff, " \n");
#ifdef DBG
    for (int i = 0; i < board.size(); ++i) {
      fprintf(stderr, "%s\n", board[i].c_str());
    }
#endif
    move = obj.getNextMove(board);
#ifdef DBG
    fprintf(stderr, "%d %d\n", move[0], move[1]);
#endif
    printf("%d %d\n", move[0], move[1]);
    fflush(stdout);
#ifdef DBG
    fprintf(stderr, "Branching: %lld %lld %0.2lf\n", branches , calls, branches / (double)calls);
#endif
  }
  return 0;
}
