// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// The game of NimForK is played as follows.  There are k 
// players sitting in a circle numbered 1 through k in 
// clockwise order.  Starting with player 1, the players take 
// turns making moves in clockwise order.  In the center of 
// the circle, there is a pile that initially contains n 
// stones.
// 
// 
// When a player takes a turn, he must remove some number of 
// stones from the pile.  The number of stones he is allowed 
// to take is dependent on the size of the pile.  You are 
// given a vector <string> moves, where the i-th element (1-
// indexed) is a space separated list of the number of stones 
// that can be removed when the pile contains i stones.  For 
// example, if there are currently 3 stones in the pile, and 
// moves[3] is "1 3", then the player can remove either 1 
// stone or 3 stones from the pile.  The player who takes the 
// last stone wins.
// 
// 
// Each player uses the following strategy to determine how 
// many stones he will remove during his turn:
// 
// 
// If there is a move that ensures he will win regardless of 
// how the other players move for the rest of the game, he 
// will make that move.  If there are several such moves, he 
// will randomly choose one of them with equal probability.  
// In other words, pretend that the other players are not 
// following the strategy described here, and that it's 
// possible for them to make any valid moves during their 
// turns.  If there is a move that will guarantee him to win 
// in that scenario, he will make that move.
// 
// If there is no such move, then assuming that the other 
// players are following this same strategy,  he will make a 
// move that gives him a non-zero chance of winning.  If 
// there are several such moves, he will randomly choose one 
// of them with equal probability.
// 
// If neither of the above moves are possible, he will 
// randomly choose any valid move with equal probability.
// 
// 
// If there are no valid moves possible during a player's 
// turn, but there are still stones left in the pile, the 
// game ends and nobody wins.
// 
// 
// Return a vector <int> containing all the players who have 
// a non-zero chance of winning the game.  The vector <int> 
// must be sorted in ascending order.
// 
// 
// 
// DEFINITION
// Class:NimForK
// Method:winners
// Parameters:int, int, vector <string>
// Returns:vector <int>
// Method signature:vector <int> winners(int n, int k, vector 
// <string> moves)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 50, inclusive.
// -k will be between 2 and 20, inclusive.
// -moves will contain exactly n elements.
// -Each element of moves will have length between 0 and 50, 
// inclusive.
// -Each element of moves will contain a space separated list 
// of integers.
// -Each integer in moves[i] will be between 1 and i + 1, 
// inclusive.
// -All integers in moves[i] will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// 8
// 2
// {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3", "1 2 3", 
// "1 2 3"}
// 
// Returns: {2 }
// 
// This is a standard variation of nim where each player is 
// allowed to take 1, 2 or 3 stones. In a game for two 
// players the first player wins if and only if the number of 
// stones in the initial pile is not divisible by 4.
// 
// 1)
// 7
// 2
// {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3", "1 2 3"}
// 
// Returns: {1 }
// 
// Same as the previous example. Here 7 is not divisible by 
// 4, so the first player wins.
// 
// 2)
// 5
// 3
// {"1", "1 2", "1 2 3", "1 2 3", "1 2 3"}
// 
// Returns: {2, 3 }
// 
// When there are three players and five stones, the first 
// player cannot win. However, he decides who would win by 
// taking either 1 stone (in this case the third player would 
// win) or 2 or 3 stones (in this case the second player 
// would win).
// 
// 3)
// 6
// 3
// {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3"}
// 
// Returns: {1, 3 }
// 
// Here the first player cannot force his victory. His 
// options are: take 1 stone - in this case the second player 
// would decide whether the third player, or the first player 
// would win (see previous example); take 2 stones - in this 
// case the third player would win; take 3 stones - in this 
// case the second player would win. He chooses the first 
// option because in this case he can win with non-zero 
// probability.
// 
// 4)
// 1
// 20
// {""}
// 
// Returns: { }
// 
// A delicate case. No player can make a move, so nobody can 
// take the last stone. Therefore nobody can win.
// 
// END CUT HERE
#line 147 "NimForK.cc"
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



template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

VS toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  VS ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
    }   
  free(ch);   
  return ret;   
}   

template<class T>
vector<T> toksT(string inp,string delim)   
{   
  VS temp = toks(inp,delim);   
  vector<T> ret;   
  for(int i=0;i<temp.size();i++)   
    ret.push_back(fromString<T>(temp[i]));   
  return ret;   
}   

VVI toksvvi(vector <string> inp,string delim)   
{   
  VVI ret;   
  for(int i=0;i<inp.size();i++)   
    ret.push_back(toksT<int>(inp[i],delim));   
  return ret;   
}   

VVI mov;

int cache[22][55];
bool has[22][55];
int k;

int go(int pl, int st) {
  if (has[pl][st]) return cache[pl][st];

  int &ret = cache[pl][st];
  has[pl][st] = true;
  ret = 0;

  bool can = false;
  fi(mov[st - 1].size()) {
    int nst = st - mov[st - 1][i];
    if (nst <= 0) {
      return ret = 1<<pl;
    }

    int p = go((pl + 1) % k, nst);
    if (p == 1<<pl) {
      return ret = p;
    }

    if (p & 1<<pl) {
      if (!can) {
        ret = p;
        can = true;
      } else {
        ret |= p;
      }
    }

    if (!can) ret |= p;
  }

  return ret;
}

    class NimForK
        { 
        public: 
        vector <int> winners(int n, int K, vector <string> moves) 
            { 
              k = K;
              mov = toksvvi(moves, " ");
              memset(cache, 0, sizeof(cache));
              memset(has, 0, sizeof(has));
              int st = go(0, n);

              VI ret;
              fi(k) if ( st & (1<<i) ) ret.push_back(i + 1);
              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 8; int Arg1 = 2; string Arr2[] = {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3", "1 2 3", "1 2 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, winners(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 2; string Arr2[] = {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3", "1 2 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, winners(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; string Arr2[] = {"1", "1 2", "1 2 3", "1 2 3", "1 2 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 3 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, winners(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 3; string Arr2[] = {"1", "1 2", "1 2 3", "1 2 3", "1 2 3", "1 2 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 3 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, winners(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 20; string Arr2[] = {""}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, winners(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        NimForK ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

