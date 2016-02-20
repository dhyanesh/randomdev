// BEGIN CUT HERE
// PROBLEM STATEMENT
// A non-negative integer n is said to be a sum of two 
// perfect powers if there exist two non-negative integers a 
// and b such that am + bk = n for some positive integers m 
// and k, both greater than 1. Given two non-negative 
// integers lowerBound and upperBound, return the number of 
// integers between lowerBound and upperBound, inclusive, 
// that are sums of two perfect powers.
// 
// DEFINITION
// Class:SumsOfPerfectPowers
// Method:howMany
// Parameters:int, int
// Returns:int
// Method signature:int howMany(int lowerBound, int upperBound)
// 
// 
// CONSTRAINTS
// -lowerBound will be between 0 and 5000000, inclusive.
// -upperBound will be between lowerBound and 5000000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 0
// 1
// 
// Returns: 2
// 
// 0 and 1 are both sums of two perfect powers since 0 = 0 + 
// 0 and 1 = 12 + 02.
// 
// 1)
// 5
// 6
// 
// Returns: 1
// 
// 5 is a sum of two perfect powers since 5 = 22 + 12 while 6 
// is not.
// 
// 2)
// 25
// 30
// 
// Returns: 5
// 
// Only 30 is not a sum of two perfect powers.
// 
// 3)
// 103
// 103
// 
// Returns: 0
// 
// There may be no desired integers in the range.
// 
// 4)
// 1
// 100000
// 
// Returns: 33604
// 
// 
// 
// END CUT HERE
#line 71 "SumsOfPerfectPowers.cpp"
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

    class SumsOfPerfectPowers
        { 
        public: 
					int get(int no) {
						set<int> pow;
						for (int i = 0; i * i <= no; ++i) {
							if (pow.find(i) != pow.end()) {
								continue;
							}
							for(int j = 0; ;j++) {
								if (pow
							}
						}
					}
        int howMany(int lb, int ub) 
            { 
             return get(ub) - get(lb-1);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 6; int Arg2 = 1; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 25; int Arg1 = 30; int Arg2 = 5; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 103; int Arg1 = 103; int Arg2 = 0; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 100000; int Arg2 = 33604; verify_case(4, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SumsOfPerfectPowers ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

