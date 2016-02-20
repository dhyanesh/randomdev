// BEGIN CUT HERE
// PROBLEM STATEMENT
// The game Chomp starts with a grid 3 cells high and N cells 
// wide.
// Two players take turns selecting a remaining cell in the 
// grid, and
// chomping (removing) all the cells to the right and above 
// the selected cell
// (including the chosen one).  The player who chomps the 
// lower-leftmost
// cell loses the game.  Here is a sample of two moves in the 
// game:
// 
// 
// 3 XX                          XX                    
// 2 XXXX    => chomp(4,1) =>    XXX  => chomp(1,2) => 
// 1 XXXXX                       XXX                      XXX
//   12345                       12345                    
// 12345 
// 
// 
// Determine which player wins if each player plays
// optimally, and how many total (for both players combined) 
// turns it
// takes (the last move is the losing move).  The player who 
// will win
// when playing optimally plays to win as quickly as 
// possible, while the
// player who is destined to lose plays to make the game last 
// as long as
// possible.  If player 1 will win, return the total number 
// of moves required.  Otherwise, return the negation of the 
// number of moves required.
// 
// DEFINITION
// Class:Chomp
// Method:moves
// Parameters:int
// Returns:int
// Method signature:int moves(int N)
// 
// 
// CONSTRAINTS
// -N will be between 1 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 
// Returns: 2
// 
// The optimal game is simple:
// 
//  X      .      .
//  X  =>  .  =>  .
//  X      X      .
// 
// 
// 1)
// 2
// 
// Returns: 6
// 
// 
// 
// 2)
// 4
// 
// Returns: 8
// 
// 
// 
// END CUT HERE
#line 77 "Chomp.cc"
#include <string>   
#include <vector>   
#include <iostream>    
#include <sstream>    
#include <algorithm>   
#include <numeric>   
#include <functional>    
#include <map>    
#include <set>    
#include <cassert>   
#include <list>    
#include <deque>    
#include <iomanip>    
#include <cstring>    
#include <cmath>    
#include <cstdio>    
#include <cctype>   

using namespace std;   

#define fi(n) for(int i=0;i<(n);i++)
#define fj(n) for(int j=0;j<(n);j++)
#define f(i,a,b) for(int (i)=(a);(i)<(b);(i)++)

typedef vector <int> VI;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   

int memo[2][101][101][101];
bool done[2][101][101][101];

void update(int p, int &ret, int t) {
  if (p == 0) {
    if (t >= 0) {
      if (ret < 0) 
        ret = t + 1;
      else 
        ret <?= t + 1;
    } else {
      if (ret < 0) {
        ret >?= t - 1;
      }
    }
  } else {
    if (t <= 0) {
      if (ret > 0) 
        ret = t - 1;
      else 
        ret >?= t - 1;
    } else {
      if (ret > 0) {
        ret >?= t + 1;
      }
    }
  }
}

int go(int p, int r1, int r2, int r3) {

  if (r1 == 1 && r2 == 0 && r3 == 0) {
    if (p == 0) {
      return -1;
    } else return 1;
  }

  if (done[p][r1][r2][r3]) return memo[p][r1][r2][r3];

  int &ret = memo[p][r1][r2][r3];
  done[p][r1][r2][r3] = 1;

  if (p == 0) {
    ret = -1;
  } else {
    ret = 1;
  }

  f(i, 1, r3 + 1) {
    int t = go(1-p, r1, r2, i - 1);
    update(p, ret, t);
  }
  f(i, 1, r2 + 1) {
    int t = go(1-p, r1, i - 1, min(i - 1, r3));
    update(p, ret, t);
  }
  f(i, 2, r1 + 1) {
    int t = go(1-p, i - 1, min(i-1, r2), min(i - 1, r3));
    update(p, ret, t);
  }

  return ret;
}

    class Chomp
        { 
        public: 
        int moves(int N) 
            { 
              memset(done, 0, sizeof(done));
              return go(0, N, N, N);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; verify_case(0, Arg1, moves(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 6; verify_case(1, Arg1, moves(Arg0)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 8; verify_case(2, Arg1, moves(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Chomp ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

