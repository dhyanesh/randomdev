// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are given a rectangular board where each cell contains 
// either an integer between 1 and 9, inclusive, or a hole.
// 
// 
// 
// Place a token into the cell in the upper left corner of 
// the board.
// Now you can play a simple game. The game consists of 
// moves, and each move
// looks as follows:
// 
// 
// 
// Look at the number X written in the cell where your token 
// is placed.
// Choose one of the four basic directions (up, down, left, 
// or right).
// Move your token exactly X cells in the chosen direction.  
// You can jump over all intermediate holes in the path.
// 
// 
// 
// The game ends after a move that lands the token in a hole 
// or outside the board.
// Your goal is to make as many moves as possible.
// 
// 
// 
// The board is given as a vector <string> board.
// Characters '1' to '9' represent cells containing the 
// corresponding integer, and
// letters 'H' represent holes.
// The upper left corner of the
// board corresponds to the first character of the first 
// element of board.
// 
// 
// 
// Write a method that will compute the maximum number of 
// moves you can make on the
// given board. If it is possible to make an arbitrarily 
// large number of moves,
// your method should return -1.
// 
// 
// 
// DEFINITION
// Class:JumpingBoard
// Method:maxJumps
// Parameters:vector <string>
// Returns:int
// Method signature:int maxJumps(vector <string> board)
// 
// 
// CONSTRAINTS
// -board will contain between 1 and 50 elements, inclusive.
// -Each element of board will contain between 1 and 50 
// characters, inclusive.
// -All elements of board will be of the same length.
// -Each element of board will only contain characters from 
// the string "123456789H" (quotes for clarity).
// -The first character of the first element of board will 
// not be 'H'.
// 
// 
// EXAMPLES
// 
// 0)
// {"3942178",
//  "1234567",
//  "9123532"}
// 
// 
// Returns: 5
// 
// In the first move you have to move the token to the right. 
// In the second move you
// have three choices. Moves to the left and to the right 
// would bring you to cells
// with a 9 and a 7, respectively, forcing you to end the 
// game in the third move. 
// The optimal strategy is to make the second move down, the 
// third one to the right,
// and the fourth one up or to the left. In the last fifth 
// move you are forced to leave
// the board.
// 
// 
// 1)
// {"2H3HH4HHH5"}
// 
// Returns: 4
// 
// Remember that you are allowed to jump over holes.  Only 
// landing in a hole is bad.
// 
// 2)
// {"3994",
//  "9999",
//  "9999",
//  "2924"}
// 
// 
// Returns: -1
// 
// Make the first move down, and then you can jump left and 
// right as many times as you wish.
// 
// 
// 3)
// {"123456",
//  "234567",
//  "345678",
//  "456789"}
// 
// 
// Returns: 4
// 
// On this board, all moves that don't end the game lead to 
// the right or down.
// In the best solution, the first three moves are: right, 
// down, right.
// 
// 
// 4)
// {"9"}
// 
// 
// Returns: 1
// 
// There is no real choice here.  The game will always end 
// after the first move.
// 
// 5)
// {"2H9HH11",
//  "HHHHH11",
//  "9HHHH11"}
// 
// 
// Returns: 2
// 
// 
// 
// END CUT HERE
#line 149 "JumpingBoard.cpp"
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

VS b;

int done[55][55];

bool inb(int x, int y) {
	return x>=0 && y>=0 && x<b.size() && y<b[0].size();
}

int go(int x, int y) {
	if (b[x][y] == 'H') return 0;
	if (done[x][y]) return 1<<20;
	done[x][y] = 1;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1};

	int ret = 1;
	int val = b[x][y] - '0';
	fi(4) {
		if (inb(x + val * dx[i], y + val * dy[i])) {
			ret >?= go(x+ val*dx[i], y + val * dy[i]) + 1;
		}
	}
	done[x][y] = 0;

	return ret;
}

    class JumpingBoard
        { 
        public: 
        int maxJumps(vector <string> board) 
            { 
							b = board;
							memset(done,0,sizeof(done));
							int ret =  go(0, 0);
							if ( ret >= 1<<20) ret = -1;
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"3942178",
 "1234567",
 "9123532"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxJumps(Arg0)); }
	void test_case_1() { string Arr0[] = {"34H2H9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, maxJumps(Arg0)); }
	void test_case_2() { string Arr0[] = {"3994",
 "9999",
 "9999",
 "2924"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, maxJumps(Arg0)); }
	void test_case_3() { string Arr0[] = {"123456",
 "234567",
 "345678",
 "456789"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, maxJumps(Arg0)); }
	void test_case_4() { string Arr0[] = {"9"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, maxJumps(Arg0)); }
	void test_case_5() { string Arr0[] = {"2H9HH11",
 "HHHHH11",
 "9HHHH11"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(5, Arg1, maxJumps(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        JumpingBoard ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

