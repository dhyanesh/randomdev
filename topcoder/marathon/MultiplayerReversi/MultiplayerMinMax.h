#ifndef MultiplayerMinMax_header
#define MultiplayerMinMax_header

#include <vector>

using namespace std;

class Result {
 public:
  explicit Result(int players);

  ~Result();

  void Clear() {
    for (vector<double>::iterator itr = scores_.begin();
        itr != scores_.end();
        ++itr) {
      *itr = 0.0;
    }
  }

  void AddScore(int player, double score) {
    scores_[player] += score;
  }

  double Score(int player) const {
    return scores_[player];
  }

 private:
  vector<double> scores_;
};

class State {
 public:
  State();
  virtual ~State();
  virtual State *NextState(vector<int> *move) = 0;
  virtual void GetScore(Result *result) const = 0;
  virtual int GetPlayer() const = 0;
  virtual void PrintDebugString() const = 0;
};

class MultiplayerMinMax {
 public:
   MultiplayerMinMax(const int players, const int max_depth)
     : players_(players),
       max_depth_(max_depth) { }

   void FindBestMove(State *initial_state, vector<int> *move, Result *result) const;

 private:
   void InternalFindBestMove(State *current_state, int depth, vector<int> *move, Result *result) const;

   const int players_;
   const int max_depth_;
};
#endif
