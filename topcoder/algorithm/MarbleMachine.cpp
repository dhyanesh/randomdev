// BEGIN CUT HERE
// PROBLEM STATEMENT
// You have built a moving sculpture containing several 
// devices that move marbles around on a grid.  Each device 
// occupies a single square on the grid and repeatedly 
// executes a sequence of actions.  The possible actions are:
// 
// Digits 0-9: Bring up 0-9 marbles from the central store 
// (which never runs out of marbles) and place them on the 
// square.
// N,E,S,W: Move all the marbles on the square one square 
// North, East, South, or West.  If this causes the marbles 
// to leave the grid, they will be removed and placed back in 
// the central store.
// D: Remove all the marbles from the square and drop them 
// back into the central store.
// 
// Each device has its own sequence of actions, and different 
// devices may have sequences of different lengths.  At time 
// 0, each device executes its first action, at time 1, each 
// device executes its second action, etc.  When a device 
// reaches the end of its sequence, it starts again at the 
// beginning of the sequence.
//  
// 
// During each unit of time, all actions happen 
// simultaneously and only operate on marbles on the squares 
// at the beginning of that time unit.  For example, suppose 
// there is one marble on square (0, 0) and one on square (1, 
// 0).  Now suppose the first square's action is 'E' and the 
// second square's action is 'D'.  At the end of this time 
// unit, the first square will have 0 marbles and the second 
// will have 1.  The second square drops the marble that it 
// had at the beginning of the time unit, but it does not 
// drop the marble that arrives from the first square during 
// that time unit.
//  
// You are given a vector <string> actions, the i-th element 
// of which is the action sequence for a device of type i 
// (where i is a 0-based index).  You are also given a vector 
// <string> layout, where the j-th character of the i-th 
// element is a digit representing the type of device located 
// in row i, column j of the grid.  Rows are numbered in 
// increasing order from North to South, and columns are 
// numbered in increasing order from West to East.  Return 
// the maximum number of marbles that exist on a single 
// square after t time units have passed.
// 
// DEFINITION
// Class:MarbleMachine
// Method:maxMarbles
// Parameters:vector <string>, vector <string>, int
// Returns:long long
// Method signature:long long maxMarbles(vector <string> 
// layout, vector <string> actions, int t)
// 
// 
// CONSTRAINTS
// -layout will contain between 1 and 8 elements, inclusive.
// -Each element of layout will contain between 1 and 8 
// characters, inclusive.
// -Each element of layout will contain the same number of 
// characters.
// -Each element of layout will contain only digits between 0 
// and n-1, inclusive, where n is the number of elements in 
// actions.
// -actions will contain between 1 and 10 elements, inclusive.
// -Each element of actions will contain between 1 and 6 
// characters, inclusive.
// -Each element of actions will contain only digits 
// ('0'-'9') and the characters 'N', 'E', 'S', 'W' and 'D'.
// -t will be between 1 and 100,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {
// "0101",
// "1010",
// "0101"}
// {"4","5353"}
// 5
// 
// Returns: 21
// 
// Devices of type 0 are simple; they pull up 4 marbles on 
// each turn.  Over 5 cycles, this is 20 marbles.  Devices of 
// type 1 will complete just over 1 cycle in this time - 
// pulling up a total of 5+3+5+3+5=21 marbles.  So the 
// maximum marbles at any position will be 21 (which occurs 
// at each location with a device of type 1).
// 
// 1)
// {"011112"}
// 
// {"1E","E","0"}
// 1000
// 
// Returns: 498
// 
// This structure functions as a kind of conveyor belt.  At 
// the left, the device of type 0 alternately grabs one 
// marble and pushes it East.  The devices of type 1 move the 
// marble along to the East until they reach the device of 
// type 2, which accumulates the marbles.  After 1000 cycles, 
// 500 marbles have been brought up.  2 are still on the 
// "conveyor belt", and 498 are on the square at the East 
// end.  
// 
// 2)
// {
// "01",
// "32"}
// {"1E","SSDSS","W","00000W"}
// 23
// 
// Returns: 3
// 
// This machine delivers marbles to the Southwest corner, 
// from which they are periodically dumped off the West 
// edge.  The Northeast corner also occasionally loses its 
// marbles.
// 
// END CUT HERE
#line 127 "MarbleMachine.cpp"
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

    class MarbleMachine
        { 
        public: 
        long long maxMarbles(vector <string> layout, vector <string> actions, int t) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"0101",
"1010",
"0101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4","5353"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; long long Arg3 = 21LL; verify_case(0, Arg3, maxMarbles(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"011112"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1E","E","0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; long long Arg3 = 498LL; verify_case(1, Arg3, maxMarbles(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {
"01",
"32"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1E","SSDSS","W","00000W"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 23; long long Arg3 = 3LL; verify_case(2, Arg3, maxMarbles(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MarbleMachine ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

