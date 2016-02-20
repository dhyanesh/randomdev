// BEGIN CUT HERE
// PROBLEM STATEMENT
// Unjumpers is a puzzle played on a board consisting of 100 
// squares in a straight line.  Pawns are placed in a certain 
// pattern on the board, and your goal is to see which other 
// patterns can be created starting from that position. There 
// are 3 legal moves in Unjumpers:
// 
// Jump: A pawn jumps over an adjacent pawn and lands in the 
// square immediately beyond the jumped pawn (in the same 
// direction).  The jumped pawn is removed from the board.  
// To perform this move, there must be an adjacent pawn to 
// jump, and the square in which the pawn lands must be 
// unoccupied.
// Unjump: A pawn jumps over an adjacent empty space and 
// lands in the square immediately beyond that space (in the 
// same direction).  A new pawn appears in the square that 
// was jumped (between the starting and ending squares).  To 
// perform this move, both the middle and ending squares must 
// be unoccupied.
// Superjump: A pawn moves 3 squares in one direction.  To do 
// this move, the target square must be empty.  The two 
// jumped squares may or may not have pawns - and they are 
// not affected by the move.
// 
// Only one pawn can move at a time, and pawns may never move 
// off of the board.
// 
// You are given a string start containing the initial layout 
// of the board.  Each character of the string describes one 
// square, with the first character describing the leftmost 
// square.  In the string, '.' represents an empty space 
// while '*' represents a pawn.  You are also given a vector 
// <string> targets, each element of which is a target layout 
// formatted in the same way.  The board is always 100 
// squares wide.  The strings given will specify up to 50 of 
// the first (leftmost) squares of the layout.  You must 
// assume that the remaining squares are all empty, both when 
// considering the the start position and when considering 
// the various target positions.
// 
// For each target layout, evaluate whether that layout is 
// reachable using any number of legal moves starting at the 
// initial layout each time.  Return the number of target 
// layouts that can be reached.
// 
// DEFINITION
// Class:Unjumpers
// Method:reachableTargets
// Parameters:string, vector <string>
// Returns:int
// Method signature:int reachableTargets(string start, vector 
// <string> targets)
// 
// 
// CONSTRAINTS
// -start will contain between 1 and 50 characters, inclusive.
// -start will contain only '*' and '.' characters.
// -targets will contain between 1 and 50 elements, inclusive.
// -Each element of targets will contain between 1 and 50 
// characters, inclusive.
// -Each element of targets will contain only '*' and '.' 
// characters.
// 
// 
// EXAMPLES
// 
// 0)
// "**."
// {
// "..*",
// "*.**",
// ".*.*"}
// 
// 
// Returns: 3
// 
// Each of the 3 target layouts can be reached in one move - 
// the first is one jump, the second is one unjump, and the 
// third is one superjump.
// 
// 1)
// "..***"
// {
// "..****..*",
// "..***....",
// "..****"}
// 
// Returns: 2
// 
// The first layout is reachable with a little ingenuity.  
// The second layout doesn't require any moves (it's the same 
// position, just with some extra blank spaces shown).  The 
// third is unreachable.
// 
// 2)
// "*..*"
// {
// "*..*......",
// "*.....*...",
// "...*.....*",
// "...*..*...",
// "*........*",
// "*...***..*"}
// 
// Returns: 6
// 
// All of these layouts can be reached.
// 
// 3)
// "...***" 
// {
// "***...",
// "..****",
// "**....**",
// ".*.*.*"}
// 
// Returns: 3
// 
// Only the second layout shown is unreachable.
// 
// END CUT HERE
#line 124 "Unjumpers.cpp"
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
#include <queue>    
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
typedef unsigned long long ull;
typedef vector <ull> VL;   
typedef vector <VL> VVL;   

inline bool bit(VL t, int i) {
	if (i <= 60) return t[0] & (1ULL<<i);

	return t[1] & (1ULL<<(i-60));
}

inline void setbit(VL &t, int i) {
	if (i <= 60) t[0] |= (1ULL<<i);

	t[1] |= (1ULL<<(i-60));
}

inline void clearbit(VL &t, int i) {
	if (i <= 60) t[0] &= ~(1ULL<<i);

	t[1] &= ~(1ULL<<(i-60));
}


    class Unjumpers
        { 
        public: 
        int reachableTargets(string start, vector <string> targets) 
            { 
							VL st(2,0);
							fi(start.size()) if (start[i] == '*') st[0] |= (1ULL<i);


							VL t(2, 0);

							VVL tar(targets.size(), t);
							fi(targets.size())
								fj(targets[i].size())
								 if (targets[i][j]=='*') tar[i][0] |= (1ULL<j);

							queue<VL> bfs;
							bfs.push(st);
							set<VL> done;
							done.insert(st);
							while (!bfs.empty()) {
								VL &top = bfs.front();

								VL nt(2);
								fi(98) {
									if (bit(top, i+2)) continue;

									nt = top;
									clearbit(nt, i);
									setbit(nt, i + 2);
									if (bit(top, i + 1)) {
										clearbit(nt, i + 1);
									} else {
										setbit(nt, i + 1);
									}

									if (done.find(nt) == done.end()) {bfs.push(nt);
										done.insert(nt); }
								}

								f(i,2,100) {
									if (bit(top, i-2)) continue;

									nt = top;
									clearbit(nt, i);
									setbit(nt, i - 2);
									if (bit(top, i - 1)) {
										clearbit(nt, i - 1);
									} else {
										setbit(nt, i - 1);
									}

									if (done.find(nt) == done.end()) {bfs.push(nt);
										done.insert(nt); }
								}

								fi(97) {
									if (bit(top, i+3)) continue;

									nt = top;
									clearbit(nt, i);
									setbit(nt, i + 3);
									if (done.find(nt) == done.end())  {bfs.push(nt);
										done.insert(nt); }
								}

								f(i,3,100) {
									if (bit(top, i-3)) continue;

									nt = top;
									clearbit(nt, i);
									setbit(nt, i - 3);
									if (done.find(nt) == done.end()) {bfs.push(nt);
										done.insert(nt); }
								}

								bfs.pop();
							}

							int ret = 0;
							fi(tar.size()) if (done.find(tar[i]) != done.end()) ret++;
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "**."; string Arr1[] = {
"..*",
"*.**",
".*.*"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, reachableTargets(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "..***"; string Arr1[] = {
"..****..*",
"..***....",
"..****"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, reachableTargets(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "*..*"; string Arr1[] = {
"*..*......",
"*.....*...",
"...*.....*",
"...*..*...",
"*........*",
"*...***..*"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, reachableTargets(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "...***" ; string Arr1[] = {
"***...",
"..****",
"**....**",
".*.*.*"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, reachableTargets(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Unjumpers ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

