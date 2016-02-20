// BEGIN CUT HERE
// PROBLEM STATEMENT
// A juice company is running a promotion where each juice 
// bottle they sell contains a code that you can redeem for a 
// prize.  There are n different codes, each corresponding to 
// a different type of prize.  The codes are evenly 
// distributed, so the probability of winning a certain type 
// of prize is 1/n for each bottle.  The codes are written 
// underneath the bottle caps, so you can't read them until 
// you buy the bottles.  Your goal is to collect k different 
// types of prizes.  Return the expected number of bottles 
// you must buy to achieve this goal.
// 
// DEFINITION
// Class:CollectingBonuses
// Method:expectedBuy
// Parameters:string, string
// Returns:double
// Method signature:double expectedBuy(string n, string k)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative 
// or absolute value of 1E-9.
// 
// 
// CONSTRAINTS
// -n and k will contain digits ('0' - '9') only.
// -n and k will represent positive integers without leading 
// zeros.
// -n will represent an integer between 1 and 10^18, inclusive.
// -k will represent an integer between 1 and the integer n 
// represents, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// "1"
// "1"
// 
// Returns: 1.0
// 
// With only 1 type of prizes you just need to buy 1 bottle.
// 
// 1)
// "2"
// "1"
// 
// Returns: 1.0
// 
// Now there are 2 types of prizes, but any one will satisfy 
// you, so you again need only 1 bottle.
// 
// 2)
// "2"
// "2"
// 
// Returns: 3.0
// 
// First you buy 1 bottle and collect some type of prizes. 
// After this, you need to collect another type of prizes. 
// Only half of bottles contains it, so in average you must 
// buy 2 more bottles to achieve your goal.
// 
// 3)
// "4"
// "3"
// 
// Returns: 4.333333333333333
// 
// 
// 
// END CUT HERE
#line 76 "CollectingBonuses.cc"
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

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

    class CollectingBonuses
        { 
        public: 
        double expectedBuy(string n, string k) 
            { 
              long double a,b;
              a = fromString<long double>(n);
              b = fromString<long double>(k);


              long double ans = logl(a) + 0.5 * (1.0/a) -
                1.0 / 12 * ( 1.0 / (a * a)) +
                1.0/120 * (1.0 / (a*a*a*a));

              b = a - b;
              if (b > 0.0)
                ans -= logl(b) + 0.5 * (1.0/b) -
                1.0 / 12 * ( 1.0 / (b * b)) +
                1.0/120 * (1.0 / (b*b*b*b));

              return a * ans;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "1"; string Arg1 = "1"; double Arg2 = 1.0; verify_case(0, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "2"; string Arg1 = "1"; double Arg2 = 1.0; verify_case(1, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "2"; string Arg1 = "2"; double Arg2 = 3.0; verify_case(2, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "4"; string Arg1 = "3"; double Arg2 = 4.333333333333333; verify_case(3, Arg2, expectedBuy(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CollectingBonuses ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

