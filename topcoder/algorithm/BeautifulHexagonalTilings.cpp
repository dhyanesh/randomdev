// BEGIN CUT HERE
// PROBLEM STATEMENT
// Consider a hexagonal grid with 6 sides, with the side 
// lengths given by the int[] s (in the clockwise order), as 
// shown in the following picture:
// 
// Count the number of ways to color each cell with one of 
// two colors, black or white, such that every non-border 
// black cell has exactly a black neighbors, and every non-
// border white cell has exactly b white neighbors (a cell is 
// called non-border if and only if it has exactly 6 
// neighbors in the grid).
// 
// DEFINITION
// Class:BeautifulHexagonalTilings
// Method:howMany
// Parameters:vector <int>, int, int
// Returns:int
// Method signature:int howMany(vector <int> s, int a, int b)
// 
// 
// CONSTRAINTS
// -s will contain exactly 6 elements.
// -Each element of s will be between 2 and 6, inclusive.
// -a and b will each be between 0 and 6, inclusive.
// -s will define a valid hexagonal grid.
// -The answer will always fit into an int.
// 
// 
// EXAMPLES
// 
// 0)
// {2,2,2,2,2,2}
// 6
// 6
// 
// Returns: 2
// 
// Either all white or all black.
// 
// 1)
// {6,6,6,6,6,6}
// 6
// 6
// 
// Returns: 2
// 
// The field is bigger, but still all white or all black.
// 
// 2)
// {2,2,2,2,2,2}
// 2
// 2
// 
// Returns: 30
// 
// 
// 
// 3)
// {4,4,3,5,3,4}
// 4
// 1
// 
// Returns: 213
// 
// The grid from the picture.
// 
// END CUT HERE
#line 70 "BeautifulHexagonalTilings.cpp"
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

    class BeautifulHexagonalTilings
        { 
        public: 
        int howMany(vector <int> s, int a, int b) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,2,2,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 6; int Arg3 = 2; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {6,6,6,6,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 6; int Arg3 = 2; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,2,2,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 30; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {4,4,3,5,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 1; int Arg3 = 213; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BeautifulHexagonalTilings ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

