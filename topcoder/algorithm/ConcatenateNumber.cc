// BEGIN CUT HERE
// PROBLEM STATEMENT
// Given a positive integer number, concatenate one or more 
// copies of number to create an integer that is divisible by 
// k.  Do not add any leading zeroes.  Return the least 
// number of copies needed, or -1 if it is impossible.
// 
// DEFINITION
// Class:ConcatenateNumber
// Method:getSmallest
// Parameters:int, int
// Returns:int
// Method signature:int getSmallest(int number, int k)
// 
// 
// CONSTRAINTS
// -number will be between 1 and 1,000,000,000, inclusive.
// -k will be between 1 and 100,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// 9
// 
// Returns: 9
// 
// At least 9 copies are needed, since 222222222 is divisible 
// by 9.
// 
// 1)
// 121
// 11
// 
// Returns: 1
// 
// 121 is divisible by 11.
// 
// 2)
// 1
// 2
// 
// Returns: -1
// 
// You can never get an even number by concatenating only 1's.
// 
// 3)
// 35
// 98765
// 
// Returns: 9876
// 
// The resulting integer could be really big.
// 
// 4)
// 1000000000
// 3
// 
// Returns: 3
// 
// 
// 
// END CUT HERE
#line 66 "ConcatenateNumber.cc"
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

    class ConcatenateNumber
        { 
        public: 
        int getSmallest(int number, int k) 
            { 
							ll no = number;

							while (no < 1LL<<32) {
								if (no % k == 0) return no;
								no = 10*no + number;
							}

							return -1;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 9; int Arg2 = 9; verify_case(0, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 121; int Arg1 = 11; int Arg2 = 1; verify_case(1, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 2; int Arg2 = -1; verify_case(2, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 35; int Arg1 = 98765; int Arg2 = 9876; verify_case(3, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 3; int Arg2 = 3; verify_case(4, Arg2, getSmallest(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ConcatenateNumber ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

