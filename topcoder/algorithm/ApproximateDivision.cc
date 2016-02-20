// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Division is an expensive operation for a computer to 
// perform, compared to addition, subtraction, and even 
// multiplication.
// The exception is when dividing by powers of 2, because 
// this can be done either with a bit shift (for a fixed-
// point value) or by subtracting 1 from the exponent (for a 
// floating-point value).
// In this problem, we will approximate the quotient of two 
// numbers using only addition, multiplication, and division 
// by powers of 2.
// 
// 
// Consider the following identity:
// 
// 
// 
//      1      1      c^0     c^1     c^2
//     --- = ----- = ----- + ----- + ----- + ...
//      b     t-c     t^1     t^2     t^3
// 
// 
// If t is a power of 2, then the denominator of each term 
// will be a power of 2.
// 
// 
// Given integers a, b, and terms, approximate a/b by 
// computing the first terms terms of the identity above, and 
// multiplying the result by a.
// Select t to be the smallest power of 2 greater than or 
// equal to b.
// 
// 
// DEFINITION
// Class:ApproximateDivision
// Method:quotient
// Parameters:int, int, int
// Returns:double
// Method signature:double quotient(int a, int b, int terms)
// 
// 
// NOTES
// -Your return value must have an absolute or relative error 
// less than 1e-9.
// 
// 
// CONSTRAINTS
// -b will be between 1 and 10000, inclusive.
// -a will be between 0 and b, inclusive.
// -terms will be between 1 and 20, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// 5
// 2
// 
// Returns: 0.34375
// 
// In this case t is chosen to be 8, and therefore c is 3.  
// The first two terms are 1/8 and 3/64.
// 
// 1)
// 7
// 8
// 5
// 
// Returns: 0.875
// 
// If b is a power of two, the first term is equal to exactly 
// 1/b, and all other terms are zero.
// 
// 2)
// 1
// 3
// 10
// 
// Returns: 0.33333301544189453
// 
// 3)
// 1
// 10000
// 2
// 
// Returns: 8.481740951538086E-5
// 
// 4)
// 1
// 7
// 20
// 
// Returns: 0.14285714285714285
// 
// 5)
// 0
// 4
// 3
// 
// Returns: 0.0
// 
// 
// 
// 6)
// 50
// 50
// 1
// 
// Returns: 0.78125
// 
// 
// 
// END CUT HERE
#line 118 "ApproximateDivision.cc"
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

    class ApproximateDivision
        { 
        public: 
        double quotient(int a, int b, int terms) 
            { 
              long long t = 1;
              while (t<b) t<<=1;

              long long c = t - b;

              long double ans = 0.0;

              fi(terms) {
                ans += powl((long double)c, (long double)i) / powl((long double)t, (long double)i + 1);
              }

              return ans * a;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 5; int Arg2 = 2; double Arg3 = 0.34375; verify_case(0, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 5; double Arg3 = 0.875; verify_case(1, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 10; double Arg3 = 0.33333301544189453; verify_case(2, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 10000; int Arg2 = 2; double Arg3 = 8.481740951538086E-5; verify_case(3, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 7; int Arg2 = 20; double Arg3 = 0.14285714285714285; verify_case(4, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 0; int Arg1 = 4; int Arg2 = 3; double Arg3 = 0.0; verify_case(5, Arg3, quotient(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arg0 = 50; int Arg1 = 50; int Arg2 = 1; double Arg3 = 0.78125; verify_case(6, Arg3, quotient(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ApproximateDivision ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

