// BEGIN CUT HERE
// PROBLEM STATEMENT
// Look at the following pseudo-code, which computes the n-th 
// Fibonacci number:
// 
// int fibonacci(int n)
// 	begin
// 	if n equals 0
// 		begin
// 		print(0)
// 		return 0
// 		end
// 	if n equals 1
// 		begin
// 		print(1)
// 		return 1
// 		end
// 	return fibonacci(n - 1) + fibonacci(n - 2)
// 	end
// 
// 
// For example, if one calls fibonacci(3), then the following 
// will happen:
// 
// fibonacci(3) calls fibonacci(2) and fibonacci(1) (the 
// first call).
// fibonacci(2) calls fibonacci(1) (the second call) and 
// fibonacci(0).
// The second call of fibonacci(1) prints 1 and returns 1.
// fibonacci(0) prints 0 and returns 0.
// fibonacci(2) gets the results of fibonacci(1) and fibonacci
// (0) and returns 1.
// The first call of fibonacci(1) prints 1 and returns 1.
// fibonacci(3) gets the results of fibonacci(2) and fibonacci
// (1) and returns 2.
// 
// In total, '1' will be printed twice and '0' will be 
// printed once.
// 
// 
// We want to know how many times '0' and '1' will be printed 
// for a given n. You are to return a vector <int> which 
// contains exactly two elements. The first and second 
// elements of the return value must be equal to the number 
// of times '0' and '1', respectively, will be printed during 
// a fibonacci(n) call.
// 
// 
// DEFINITION
// Class:NumberofFiboCalls
// Method:fiboCallsMade
// Parameters:int
// Returns:vector <int>
// Method signature:vector <int> fiboCallsMade(int n)
// 
// 
// CONSTRAINTS
// -n will be between 0 and 40, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 0
// 
// Returns: {1, 0 }
// 
// If I call the Fibonacci function with n = 0, it just calls 
// the 1st base case. Hence, the result is {1,0}.
// 
// 1)
// 3
// 
// Returns: {1, 2 }
// 
// The test case given in the problem statement.
// 
// 2)
// 6
// 
// Returns: {5, 8 }
// 
// 3)
// 22
// 
// Returns: {10946, 17711 }
// 
// END CUT HERE
#line 90 "NumberofFiboCalls.cpp"
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

    class NumberofFiboCalls
        { 
        public: 
        vector <int> fiboCallsMade(int n) 
            { 
							int z[50];
							int o[50];

							z[0] = 1;
							z[1] = 0;
							o[0] = 0;
							o[1] = 1;

							f(i,2,n+1) {
								z[i] = z[i-1] + z[i-2];
								o[i] = o[i-1] + o[i-2];
							}

							VI ret(2);
							ret[0]= z[n];
							ret[1]= o[n];

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 0; int Arr1[] = {1, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, fiboCallsMade(Arg0)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, fiboCallsMade(Arg0)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {5, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, fiboCallsMade(Arg0)); }
	void test_case_3() { int Arg0 = 40; int Arr1[] = {10946, 17711 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, fiboCallsMade(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        NumberofFiboCalls ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

