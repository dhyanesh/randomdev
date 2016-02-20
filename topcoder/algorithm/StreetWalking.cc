// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are walking home from school through the city.  The 
// city is infinite in size, with vertical streets located at 
// every integer X value and horizontal streets located at 
// every Y value.  You are currently located at (0,0) and are 
// trying to get to your home, located at (X, Y).  You have 
// two methods of travel available to you:  you can walk 
// along the street to proceed to a horizontally or 
// vertically adjacent intersection (which takes walkTime 
// seconds), or you can sneak across the block diagonally to 
// the opposite corner (taking sneakTime seconds).  You can 
// walk or sneak in any of the eight directions shown in the 
// image (see example 2).
// 
// 
// 
// 
// 
// Return the least amount of time that it will take you to 
// return home.  See the examples for clarification.
// 
// 
// DEFINITION
// Class:StreetWalking
// Method:minTime
// Parameters:int, int, int, int
// Returns:long long
// Method signature:long long minTime(int X, int Y, int 
// walkTime, int sneakTime)
// 
// 
// CONSTRAINTS
// -X will be between 0 and 1,000,000,000, inclusive.
// -Y will be between 0 and 1,000,000,000, inclusive.
// -walkTime will be between 1 and 10000, inclusive.
// -sneakTime will be between 1 and 10000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 4
// 2
// 3
// 10
// 
// Returns: 18
// 
// The fastest way to your home is to not sneak at all.
// 
// 1)
// 4
// 2
// 3
// 5
// 
// Returns: 16
// 
// In this case, it is faster to sneak across twice, 
// following the path (0,0)->(1,0)->(2,1)->(3,1)->(4,2).  
// This takes 10 seconds for the sneaking, and 6 seconds for 
// the walking.
// 
// 2)
// 2
// 0
// 12
// 10
// 
// Returns: 20
// 
// One possible path is (0,0)->(1,1)->(2,0).
// 
// 3)
// 25
// 18
// 7
// 11
// 
// Returns: 247
// 
// 
// 
// 4)
// 24
// 16
// 12
// 10
// 
// Returns: 240
// 
// 
// 
// 5)
// 10000000
// 50000000
// 800
// 901
// 
// Returns: 41010000000
// 
// 
// 
// 6)
// 135
// 122
// 43
// 29
// 
// Returns: 3929
// 
// 
// 
// END CUT HERE
#line 118 "StreetWalking.cc"
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

    class StreetWalking
        { 
        public: 
        long long minTime(int X, int Y, int wt, int st) 
            { 
              if (2*wt < st) {
                return (X + Y) * (long long)wt;
              }

              int min = X < Y ?X:Y;
              int max = X > Y ?X:Y;

              ll ret = min * (long long) st;

              if (st < wt) {
                ret += (max - min) / 2 * (long long )2 * st;
                ret += (max - min) % 2 * (long long ) wt;
              } else {
                ret += (max - min) * (long long )wt;
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 3; int Arg3 = 10; long long Arg4 = 18LL; verify_case(0, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 3; int Arg3 = 5; long long Arg4 = 16LL; verify_case(1, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 12; int Arg3 = 10; long long Arg4 = 20LL; verify_case(2, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 25; int Arg1 = 18; int Arg2 = 7; int Arg3 = 11; long long Arg4 = 247LL; verify_case(3, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 24; int Arg1 = 16; int Arg2 = 12; int Arg3 = 10; long long Arg4 = 240LL; verify_case(4, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 10000000; int Arg1 = 50000000; int Arg2 = 800; int Arg3 = 901; long long Arg4 = 41010000000LL; verify_case(5, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arg0 = 135; int Arg1 = 122; int Arg2 = 43; int Arg3 = 29; long long Arg4 = 3929LL; verify_case(6, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        StreetWalking ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

