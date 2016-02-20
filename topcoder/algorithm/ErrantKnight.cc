// BEGIN CUT HERE
// PROBLEM STATEMENT
// The game of Errant Knights is played on an infinite 
// chessboard using two knights, white and black. The players 
// alternate turns and the white player starts the game. Each 
// player makes a normal chess knight's move with his knight, 
// but there is a restriction that each move must make the 
// Euclidean distance between the two knights smaller. A 
// player can make more than one move in a single turn, but 
// then each move must go in the same direction.
// 
// For example, if the black knight is at coordinates (0, 0) 
// and the white knight is at (9, 5), then the white knight 
// can move to (7, 4), (5, 3), (3, 2), (1, 1), (-1, 0). 
// Further moving in this direction is not allowed because 
// (-3, -1) is further from (0, 0) than (-1, 0). Of course, 
// the white knight could also start his turn by moving in 
// one of several other directions, and then possibly making 
// more moves in that direction.
// 
// The game ends when one of the knights wins by capturing 
// the other one (by moving to its position), or when it is 
// impossible to make another move (because the knights are 
// orthogonally next to each other and each move would 
// increase the distance). In the second case, the player who 
// should make the next move loses.
// 
// Several games of Errant Knight will be played.  The 
// starting position of the white knight in the i-th game is 
// (x[i], y[i]).  The black knight will start each game at 
// (0, 0).  Both players play optimally.  Return a String 
// where the i-th character is 'B' if the black knight wins 
// the i-th game or 'W' if the white knight wins.
// 
// 
// DEFINITION
// Class:ErrantKnight
// Method:whoWins
// Parameters:vector <int>, vector <int>
// Returns:string
// Method signature:string whoWins(vector <int> x, vector 
// <int> y)
// 
// 
// NOTES
// -A chess knight can move in 8 directions. From (0, 0), a 
// knight could move to (2, 1), (2, -1), (1, 2), (-1, 2), (1, 
// -2), (-1, -2), (-2, 1), (-2, -1).
// 
// 
// CONSTRAINTS
// -x and y will contain between 1 and 50 elements, inclusive.
// -x and y will contain the same number of elements.
// -Each element of x will be between -4000 and 4000, 
// inclusive.
// -Each element of y will be between -4000 and 4000, 
// inclusive.
// -For each i, x[i] and y[i] cannot both be equal to 0.
// 
// 
// EXAMPLES
// 
// 0)
// {1,1,2,2,9,3}
// {0,1,0,1,5,3}
// 
// Returns: "BWWWWB"
// 
// In the first game, there is no possible move for White 
// from (1,0), so Black wins.
// In the second game, White moves from (1,1) to (0,-1). 
// Black has no legal move from there, so White wins.
// In the third game, White moves from (2,0) to (0,1). Again, 
// Black has no legal move, and White wins.
// In the fourth game, White moves from (2,1) to (0,0), and 
// captures the Black knight. White wins.
// In the fifth game, White makes five moves from the same 
// direction, moving from (9,5) to (-1,0). White wins.
// In the sixth game, White can make a sequence of moves 
// which lead to one of the following squares: (2,1), (1,-1), 
// (1,2), (-1,1), (4,1), (1,4). After each of these moves 
// Black can win.
// 
// 
// 1)
// {1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,7}

// {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,6,6,7}

// 
// Returns: 
// "BWBBBBBWWWWWWWWWWWWWWWWBWWWWWWWBWWWWWWWBWWWWWWWWWB"
// 
// 
// 
// 2)
// {-10}
// {0}
// 
// Returns: "B"
// 
// Note that x[i] and y[i] can be negative.
// 
// 
// END CUT HERE
#line 107 "ErrantKnight.cc"
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
typedef long long ll;

map<pair<int, pair<int, int> >, bool> memo;

ll getdist(int x, int y) {
  return x * x + y * y;
}

bool go(int pl, int x, int y) {
  pair<int, pair<int,int> > te(pl, make_pair(x,y));
  if (memo.count(te) > 0) return memo[te];

  if (x == 0 && y == 0) {
    if (pl == 1) return memo[te]=false;
    return memo[te]=true;
  }

  int dx[] = { 2,2,1,-1,1,-1,-2,-2 };
  int dy[] = { 1,-1,2,2,-2,-2,1,-1};

  fi(8) {
    int c = 1;
    ll dist = getdist(x,y);
    while (true) {
      int nx = x + c * pl * dx[i];
      int ny = y + c * pl * dy[i];
      ll nd = getdist(nx, ny);
      if (nd > dist) break;
      bool re = go(-pl, nx, ny);
      if (pl == 1 && re) return memo[te]=true;
      if (pl == -1 && !re) return memo[te]=false;
      dist = nd;
      ++c;
    }
  }

  if (pl == 1) return memo[te]=false;
  if (pl == -1) return memo[te]=true;
}

    class ErrantKnight
        { 
        public: 
        string whoWins(vector <int> x, vector <int> y) 
            { 
              string ret;
              fi(x.size()) {
                if (go(1, x[i], y[i])) ret += 'W';
                else ret += 'B';
              }
              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1,2,2,9,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0,1,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "BWWWWB"; verify_case(0, Arg2, whoWins(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,6,6,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "BWBBBBBWWWWWWWWWWWWWWWWBWWWWWWWBWWWWWWWBWWWWWWWWWB"; verify_case(1, Arg2, whoWins(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "B"; verify_case(2, Arg2, whoWins(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ErrantKnight ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

