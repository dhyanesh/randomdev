// BEGIN CUT HERE
// PROBLEM STATEMENT
// A magic matrix is a square matrix filled with digits (0 to 
// 9) such that its row sums and column sums all have the 
// same last digit.
// John has n by n matrix.
// Its rows and columns are numbered from 0 to n-1.
// Some cells of the matrix already contain digits and some 
// are empty.
// John wants to assign a value to each empty cell to get a 
// magic matrix.
// 
// 
// You are given an int n and vector <int>s rows, columns, 
// values.
// The number values[i] is the digit in John's matrix at row 
// rows[i] and at column columns[i].
// Return the number of different matrices John can get 
// modulo 1,234,567,891.
// 
// 
// DEFINITION
// Class:TheMagicMatrix
// Method:find
// Parameters:int, vector <int>, vector <int>, vector <int>
// Returns:int
// Method signature:int find(int n, vector <int> rows, vector 
// <int> columns, vector <int> values)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 1000, inclusive.
// -rows will contain between 1 and 10 elements, inclusive.
// -rows, columns and values will all contains the same 
// number of elements.
// -Each element of rows will be between 0 and n-1, inclusive.
// -Each element of columns will be between 0 and n-1, 
// inclusive.
// -Each element of values will be between 0 and 9, inclusive.
// -All pairs (rows[i], columns[i]) will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// {0, 1}
// {1, 0}
// {4, 4}
// 
// Returns: 10
// 
// John will get a magic matrix only if he assigns equal 
// values to both empty cells. 
// 
// 
// 1)
// 2
// {0, 1}
// {1, 0}
// {4, 7}
// 
// Returns: 0
// 
// 
// 
// 2)
// 4
// {0, 0, 0, 1, 2, 2, 2, 3, 3, 3}
// {0, 1, 2, 3, 0, 1, 2, 0, 1, 2}
// {3, 5, 1, 9, 5, 1, 8, 6, 7, 1}
// 
// Returns: 2
// 
// 
// 
// 3)
// 474
// {44, 77}
// {47, 74}
// {4, 7}
// 
// Returns: 83494518
// 
// 
// 
// END CUT HERE
#line 89 "TheMagicMatrix.cc"
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

    class TheMagicMatrix
        { 
        public: 
        int find(int n, vector <int> rows, vector <int> columns, vector <int> values) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 10; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arr1[] = {0, 0, 0, 1, 2, 2, 2, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 2, 3, 0, 1, 2, 0, 1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 5, 1, 9, 5, 1, 8, 6, 7, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 474; int Arr1[] = {44, 77}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {47, 74}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 83494518; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheMagicMatrix ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

