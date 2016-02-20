// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 	Suppose there is a triangle of digits like the following:
// 
// 74932
// 1325
// 457
// 92
// 1
// 
// 	Each digit, with the exception of those in the top row, 
// is equal to the last digit of the sum of 
// 	its upper and upper-right neighboring digits.
// 
// 
// 	You will be given a vector <string> questionMarkTriangle 
// containing a triangle where 
// 	only one digit in each row is known and all others are 
// represented by '?'s 
// 	(see example 0 for clarification).
// 	Each element of questionMarkTriangle represents a row of 
// the triangle, and the rows are given 
// 	from top to bottom. Each element contains exactly one 
// digit ('0'-'9') and 
// 	the remaining characters are all '?'s. Restore the 
// triangle and return it as a 
// 	vector <string> without '?'s.
// 
// 
// 
// DEFINITION
// Class:RevealTriangle
// Method:calcTriangle
// Parameters:vector <string>
// Returns:vector <string>
// Method signature:vector <string> calcTriangle(vector 
// <string> questionMarkTriangle)
// 
// 
// CONSTRAINTS
// -questionMarkTriangle will contain between 1 and 50 
// elements, inclusive.
// -Element i (0 indexed) of questionMarkTriangle will 
// contain exactly n-i characters, where n is the number of 
// elements in questionMarkTriangle.
// -Each element of questionMarkTriangle will contain exactly 
// one digit ('0'-'9') and all others characters will be '?'s.
// 
// 
// EXAMPLES
// 
// 0)
// {"4??", 
//  "?2", 
//  "1"}
// 
// Returns: {"457", "92", "1" }
// 
// Let's substitute '?'s with unknown variables:
// 
// 4ab 
// c2 
// 1
// 
// 
// Having done that, we start solving for the variables from 
// the bottom to the top. First, we know that the last digit 
// of (c + 2) is 1. Therefore, c must be 9:
// 
// 
// 4ab 
// 92 
// 1
// 
// Now we know that the last digit of (4 + a) is 9, which 
// means a is 5:
// 
// 45b 
// 92 
// 1
// 
// 
// And, finally, the last digit of (5 + b) is 2, so b is 7.
// 
// 1)
// {"1"}
// 
// Returns: {"1" }
// 
// 2)
// {"???2", "??2", "?2", "2"}
// 
// Returns: {"0002", "002", "02", "2" }
// 
// 3)
// {"??5?", "??9", "?4", "6"}
// 
// Returns: {"7054", "759", "24", "6" }
// 
// END CUT HERE
#line 103 "RevealTriangle.cc"
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

    class RevealTriangle
        { 
        public: 
        vector <string> calcTriangle(vector <string> qmt) 
            { 
              int n = qmt.size();

              for (int i = n - 2; i >= 0; --i) {
                int p = 0;
                fj(qmt[i].size()) {
                  if (qmt[i][j] != '?') {
                    p = j;
                    break;
                  }
                }

                for(int j = p - 1; j >= 0; --j) {
                  int t = qmt[i + 1][j] - '0' - qmt[i][j+1] + '0';
                  if (t < 0) t += 10;
                  qmt[i][j] = t + '0';
                }

                f(j,p,qmt[i].size() - 1) {
                  int t = qmt[i + 1][j] - '0' - qmt[i][j] + '0';
                  if (t < 0) t += 10;
                  qmt[i][j + 1] = t + '0';
                }
              }

              return qmt;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"4??", 
 "?2", 
 "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"457", "92", "1" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, calcTriangle(Arg0)); }
	void test_case_1() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, calcTriangle(Arg0)); }
	void test_case_2() { string Arr0[] = {"???2", "??2", "?2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0002", "002", "02", "2" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, calcTriangle(Arg0)); }
	void test_case_3() { string Arr0[] = {"??5?", "??9", "?4", "6"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"7054", "759", "24", "6" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, calcTriangle(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        RevealTriangle ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

