// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 	You are helping your brother with his homework 
// assignment.  His teacher gave him two distinct numbers x 
// 	and y, and asked him to use those numbers to form as many 
// different expressions as possible.  
// 	Each expression must satisfy all of the following rules:
// 
// 	
// 		The only allowed operators are '+', '-' and '*'.
// 	
// 	
// 		x and y must each appear exactly twice.  No other 
// numbers are allowed.
// 	
// 	
// 		The result of the expression must be equal to val.
// 	
// 
// 
// 
// 
// 	In other words, each expression can be written in the 
// form "a op1 b op2 c op3 d", where each of op1, op2 and op3 
// 	is '+', '-' or '*', and among the numbers a, b, c and d, 
// exactly two are equal to x and the other two are 
// 	equal to y.  Please note that the unary minus is not 
// allowed (see example 0).  Expressions are calculated from 
// 	left to right, and there is no operator precedence.  For 
// example, to calculate the result of 
// 	"2 + 2 * 3 + 3", you would first calculate 2 + 2, then 
// multiply the result by 3, and then add 3 to get 15.
// 
// 
// 
// 	Return the total number of different expressions that can 
// be formed.  Two expressions are considered 
// 	different if their string notations (as described in the 
// previous paragraph) are different.  For example, 
// 	the expressions "2 + 3 - 2 - 3", "2 - 2 + 3 - 3" and "2 - 
// 3 - 2 + 3" are all different.
// 
// 
// 
// DEFINITION
// Class:CountExpressions
// Method:calcExpressions
// Parameters:int, int, int
// Returns:int
// Method signature:int calcExpressions(int x, int y, int val)
// 
// 
// CONSTRAINTS
// -x and y will each be between -100 and 100, inclusive.
// -x and y will be different.
// -val will be between -100000000 and 100000000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 7
// 8
// 16
// 
// Returns: 9
// 
// The possible expressions are:
// 8 + 8 + 7 - 7
// 8 + 7 + 8 - 7
// 7 + 8 + 8 - 7
// 8 + 8 - 7 + 7
// 8 + 7 - 7 + 8
// 7 + 8 - 7 + 8
// 8 - 7 + 8 + 7
// 8 - 7 + 7 + 8
// 7 - 7 + 8 + 8
// 
// Please note that the unary minus is not allowed, so "-7 + 
// 7 + 8 + 8" is not a valid expression.
// 
// 1)
// 3
// 5
// 7
// 
// Returns: 5
// 
// The possible expressions are:
// 3 * 5 - 3 - 5
// 5 * 3 - 3 - 5
// 3 * 5 - 5 - 3
// 5 * 3 - 5 - 3
// 5 - 3 * 5 - 3
// 
// 2)
// 99
// 100
// 98010000
// 
// Returns: 6
// 
// 3)
// -99
// 42
// -1764
// 
// Returns: 2
// 
// -99 - (-99) - 42 * 42
// -99 - 42 - (-99) * 42
// 
// 
// 4)
// 100
// -100
// -100000000
// 
// Returns: 0
// 
// There are no valid expressions.
// 
// 5)
// 1
// 2
// 5
// 
// Returns: 17
// 
// 
// 
// END CUT HERE
#line 135 "CountExpressions.cc"
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

    class CountExpressions
        { 
        public: 
          int com(int a, int o, int b){
            switch (o) {
              case 0:
                return a+b;
              case 1:
                return a-b;
              case 2:
                return a*b;

            }
          }
          int num[2];
          int comp(int a,int o1, int b, int o2, int c, int o3, int d) {
            int ret = com(num[a],o1,num[b]);
            ret = com(ret,o2,num[c]);
            ret = com(ret,o3,num[d]);
            return ret;
          }
        int calcExpressions(int x, int y, int val) 
            { 
              int k,l,m,n,o;
              int co[2] = {0};
              int ret = 0;
              num[0] = x;
              num[1] = y;
              fi(2) {
                ++co[i];
                fj(3)
                  f(k,0,2) {
                    ++co[k];
                   f(l,0,3)
                     f(m,0,2) {
                       if (co[m] >= 2) continue;
                       ++co[m];
                       f(n,0,3) {
                         f(o,0,2) {
                           if (co[o] >= 2) continue;

                           if (comp(i,j,k,l,m,n,o) == val) ++ret;
                         }
                       }
                       --co[m];
                     }
                    --co[k];
                  }
                --co[i];
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 16; int Arg3 = 9; verify_case(0, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 7; int Arg3 = 5; verify_case(1, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 99; int Arg1 = 100; int Arg2 = 98010000; int Arg3 = 6; verify_case(2, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = -99; int Arg1 = 42; int Arg2 = -1764; int Arg3 = 2; verify_case(3, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = -100; int Arg2 = -100000000; int Arg3 = 0; verify_case(4, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 2; int Arg2 = 5; int Arg3 = 17; verify_case(5, Arg3, calcExpressions(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CountExpressions ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

