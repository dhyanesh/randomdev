// BEGIN CUT HERE
// PROBLEM STATEMENT
// Alice and Bob often play the following car racing "sim". 
// To represent the track they take a sheet of paper,
//  split it into square cells and make each cell either a 
// "road" or "obstacle". 
// Two of the "road" cells are marked as "Start" and 
// "Finish", and the goal of the game is to move your car 
// from the start to the finish as fast as possible. 
// 
// 
// In this paper game, the car is represented by a point, 
// which moves in turns. 
// At the beginning of each turn the car is located at the 
// center of some cell, and each turn moves the car to the 
// center of some other cell.
// The speed of the car is represented by a vector with 
// integer coordinates.
// Each turn consist of two parts:
// 
// Change the speed of your car, modifying the speed the car 
// had before this turn.
// Each coordinate of the speed can be increased by 1, 
// decreased by 1 or left unchanged.
// Move the car. If the car has coodinates (row, col) and its 
// speed is (vRow, vCol), then its
// new coordinates will be (row + vRow, col + vCol). 
// The car moves along the straight line between the centers 
// of the old and new cells.
// 
// 
// 
// When the path of the car touches the "Finish" cell, 
// it immediately finishes and the time it spent for the race 
// is the number of turns it took (counting the final one).
// If the path of the car intersects an obstacle before it is 
// finished, 
// then the car crashes and can not finish the race (the car 
// can touch obstacles, see examples for clarification). 
// The car can not leave the grid because it will lead to 
// disqualification.
// Please note that the car finishes immediately when it 
// touches the Finish cell,
// and the car successfully finishes even if continuing the 
// turn would move it outside the track or into an obstacle.
// 
// 
// You will be given a vector <string> track, 
// representing the track where the race occurs. Character j 
// of element i of track represents the cell at (i, j).
// '.', 'S', 'F' and 'X' characters represent free road, 
// start, finish and obstacle, respectively.
// 
// You are also given two ints, vRow and vCol, representing 
// the initial speed of the car.  Return the minimal number 
// of moves needed to finish the race.
// 
// Positive direction of vRow means increasing the row number 
// and positive direction of vCol means increasing the column 
// number (see examples 1 and 2).
// If it is not possible to get to the finish cell from the 
// start cell without crashing, return -1.
// 
// 
// 
// DEFINITION
// Class:PaperRacing
// Method:minMoves
// Parameters:vector <string>, int, int
// Returns:int
// Method signature:int minMoves(vector <string> track, int 
// vRow, int vCol)
// 
// 
// CONSTRAINTS
// -track will contain between 1 and 50 elements, inclusive.
// -Each element of track will contain between 1 and 50 
// characters, inclusive.
// -All elements of track will contain the same number of 
// characters.
// -Each element of track will contain only '.', 'X', 'S' and 
// 'F' characters.
// -track will contain exactly one 'F' and one 'S'.
// -vRow and vCol each will be between -50 and 50, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"S.................F"}
// 0
// 0
// 
// Returns: 6
// 
// Accelerate to the right as much as you can.
// 
// 1)
// {"S.................F"}
// 0
// 8
// 
// Returns: 2
// 
// You are already fast, so you need only 2 turns to finish 
// (and you don't care that continuing with this speed would 
// get you away from the track).
// 
// 2)
// {"FX",
//  "X.",
//  ".X",
//  "X.",
//  "SX"}
// 1
// 0
// 
// Returns: 8
// 
// First you need to brake, since you are moving in the wrong 
// direction. Then, you'll need to stop every second turn.
// 
// 3)
// {"S..X",
//  "X..X",
//  "XX.X",
//  "XXFX"}
// 50
// 50
// 
// Returns: 1
// 
// If you didn't touch the finish cell, the crash would be 
// unavoidable. Please note that the car reaches the finish 
// if it just touches the 'F' cell, but the car's path has to 
// go inside the obstacle for a crash.
// 
// 4)
// {"S.......X.........F"}
// 0
// 0
// 
// Returns: -1
// 
// 
// 
// END CUT HERE
#line 149 "PaperRacing.cpp"
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

    class PaperRacing
        { 
        public: 
        int minMoves(vector <string> track, int vRow, int vCol) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"S.................F"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; int Arg3 = 6; verify_case(0, Arg3, minMoves(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"S.................F"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 8; int Arg3 = 2; verify_case(1, Arg3, minMoves(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"FX",
 "X.",
 ".X",
 "X.",
 "SX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 0; int Arg3 = 8; verify_case(2, Arg3, minMoves(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"S..X",
 "X..X",
 "XX.X",
 "XXFX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 50; int Arg3 = 1; verify_case(3, Arg3, minMoves(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"S.......X.........F"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; int Arg3 = -1; verify_case(4, Arg3, minMoves(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PaperRacing ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

