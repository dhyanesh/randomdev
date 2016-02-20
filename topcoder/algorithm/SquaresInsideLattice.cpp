// BEGIN CUT HERE
// PROBLEM STATEMENT
// We define a rectangular lattice as the set of all points 
// with integer coordinates (x,y) such that 0 <= x <= width 
// and 0 <= y <= height.  A square is inside this lattice if 
// and only if all its vertices belong to the lattice.  Two 
// squares are different if there exists at least one point 
// which a vertex of the first square but not a vertex of the 
// second square.  The edges of a square are not required to 
// be parallel to the axes.
// 
// Return the number of different squares inside the lattice.
// 
// DEFINITION
// Class:SquaresInsideLattice
// Method:howMany
// Parameters:int, int
// Returns:long long
// Method signature:long long howMany(int width, int height)
// 
// 
// CONSTRAINTS
// -width and height will each be between 1 and 10^5, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 1
// 
// Returns: 1
// 
// There is only one square.
// 
// 1)
// 2
// 3
// 
// Returns: 10
// 
// There are 6 squares with area 1, 2 squares with area 4, 
// and 2 squares with area 2 (their sides are not parallel to 
// the axes).
// 
// 2)
// 3
// 3
// 
// Returns: 20
// 
// 3)
// 27
// 19
// 
// Returns: 23940
// 
// END CUT HERE
#line 61 "SquaresInsideLattice.cpp"
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


    class SquaresInsideLattice
        { 
        public: 
        long long howMany(ll wo, ll ho) 
            { 
							ll w = wo, h = ho;
							ll m = min(w,h);
							ll ret = w*h;
							w--;
							h--;
							f(i,2,m+1) {
								ret +=  w * h * i;
								w--;
								h--;
							}
							
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; long long Arg2 = 1LL; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; long long Arg2 = 10LL; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 20LL; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 27; int Arg1 = 19; long long Arg2 = 23940LL; verify_case(3, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SquaresInsideLattice ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

