// BEGIN CUT HERE
// PROBLEM STATEMENT
// A refactorable number is defined to be a number that is 
// divisble by the number of distinct factors that it has.  
// Examples of refactorable numbers include 1 (1 factor), 12 
// (6 factors), and 9 (3 factors), but not 7 (2 factors) or 
// 16 (5 factors).
// 
// You will be given two ints, low and high.  Return the 
// number of refactorable numbers between low and high, 
// inclusive.
// 
// DEFINITION
// Class:RefactorableNumber
// Method:count
// Parameters:int, int
// Returns:int
// Method signature:int count(int low, int high)
// 
// 
// CONSTRAINTS
// -low will be between 1 and 2,000,000, inclusive.
// -high will be between low and 2,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 10
// 
// Returns: 4
// 
// There are 4 refactorable numbers between 1 and 10, namely: 
// 1, 2, 8, and 9.
// 
// 1)
// 10
// 100
// 
// Returns: 12
// 
// 
// 
// 2)
// 25
// 35
// 
// Returns: 0
// 
// 
// 
// 3)
// 123
// 4567
// 
// Returns: 315
// 
// 
// 
// END CUT HERE
#line 63 "RefactorableNumber.cpp"
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

    class RefactorableNumber
        { 
        public: 
        int count(int low, int high) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 4; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 12; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 25; int Arg1 = 35; int Arg2 = 0; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123; int Arg1 = 4567; int Arg2 = 315; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        RefactorableNumber ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

