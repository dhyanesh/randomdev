// BEGIN CUT HERE
// PROBLEM STATEMENT
// Consider an arrangement of N points on the cartesian 
// plane. The "square count" of the points is the total 
// number of distinct squares with sides parallel to the 
// coordinate axes which can be built using 4 different 
// points as vertices.  Your task is to return the maximum 
// square count, considering all possible arrangements of N 
// points on the plane.
// 
// DEFINITION
// Class:MaximizeSquares
// Method:squareCount
// Parameters:int
// Returns:int
// Method signature:int squareCount(int N)
// 
// 
// NOTES
// -Two squares are distinct if at least one of their corners 
// is in a different location.
// 
// 
// CONSTRAINTS
// -N will be between 0 and 1000000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 4
// 
// Returns: 1
// 
// Clearly, we can only make one square out of 4 points.
// 
// 1)
// 5
// 
// Returns: 1
// 
// No matter where we place a fifth point, we can't get any 
// extra squares.
// 
// 2)
// 6
// 
// Returns: 2
// 
// We can get 2 squares by placing the points in the shape of 
// a rectangle.
// 
// 3)
// 16
// 
// Returns: 14
// 
// 
// 
// 4)
// 115
// 
// Returns: 340
// 
// 
// 
// END CUT HERE
#line 69 "MaximizeSquares.cpp"
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

    class MaximizeSquares
        { 
        public: 
        int squareCount(int N) 
            { 
							int n = sqrt(N);
							if ((n+1)*(n+1) == N) n++;

							int left = N - n*n;

							int ret = 0;
							f(i,1,n) {
								ret += i*i;
							}

							int m = min(left,n);
							left -=m;

							f(i,2,m+1) {
								ret+=(i-1);
							}

							f(i,2,left+1) {
								ret+=(i-1);
							}
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 1; verify_case(0, Arg1, squareCount(Arg0)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 1; verify_case(1, Arg1, squareCount(Arg0)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 2; verify_case(2, Arg1, squareCount(Arg0)); }
	void test_case_3() { int Arg0 = 16; int Arg1 = 14; verify_case(3, Arg1, squareCount(Arg0)); }
	void test_case_4() { int Arg0 = 115; int Arg1 = 340; verify_case(4, Arg1, squareCount(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MaximizeSquares ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

