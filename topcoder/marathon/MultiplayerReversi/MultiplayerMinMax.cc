#include "MultiplayerMinMax.h"

#include <cstdio>
#include <vector>

State::State() { }

State::~State() { }

Result::Result(int players)
  : scores_(players, 0.0) { }

Result::~Result() { }

void MultiplayerMinMax::FindBestMove(State *initial_state,
                                     vector<int> *best_move,
                                     Result *best_result) const {
  InternalFindBestMove(initial_state, 0, best_move, best_result);
}

void MultiplayerMinMax::InternalFindBestMove(State *current_state,
                                             int current_depth,
                                             vector<int> *best_move,
                                             Result *best_result) const {
  if (current_depth == max_depth_) {
    current_state->GetScore(best_result);
//    for (int i = 0; i < players_; ++i) {
//      fprintf(stderr, "%lf ", best_result->Score(i));
//    }
//    fprintf(stderr, "\n");
//    current_state->PrintDebugString();
    return;
  }

  Result current_result(players_);
  vector<int> move(2, -1);
  int current_player = current_state->GetPlayer();
  double best_result_score = -1.0E100;
  while (true) {
    State *next_state = current_state->NextState(&move);
    if (next_state == NULL) {
      break;
    }
    vector<int> other_move;
    InternalFindBestMove(next_state, current_depth + 1, &other_move, &current_result);
    delete next_state;

    double current_result_score = 0.0;
    for (int i = 0; i < players_; ++i) {
//      if (current_depth == 0)
//        fprintf(stderr, "%lf ", current_result.Score(i));
      if (i == current_player) {
        // Add for the current player
        current_result_score += current_result.Score(i);
      } else {
        // Subtract scores of other players
        current_result_score -= current_result.Score(i);
      }
    }
//    if (current_depth == 0) 
//      fprintf(stderr, "\n%d %d\n", move[0], move[1]);
    if (current_result_score > best_result_score) {
      *best_move = move;
      *best_result = current_result;
      best_result_score = current_result_score;
    }

    current_result.Clear();
  }
}
