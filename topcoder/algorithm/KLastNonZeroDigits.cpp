// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are given an int N.  The factorial of N is defined as 
// N*(N-1)*(N-2)*...*1.  Compute the factorial of N and 
// remove all of its rightmost zero digits.  If the result is 
// more than K digits long, return the last K digits as a 
// string.  Otherwise, return the entire result as a string.  
// 
// 
// DEFINITION
// Class:KLastNonZeroDigits
// Method:getKDigits
// Parameters:int, int
// Returns:string
// Method signature:string getKDigits(int N, int K)
// 
// 
// CONSTRAINTS
// -N will be between 1 and 20, inclusive.
// -K will be between 1 and 9, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 10
// 3
// 
// Returns: "288"
// 
// You would first compute the factorial of 10, which is 
// 10*9*8*7*6*5*4*3*2*1=3628800. You would then remove all 
// rightmost zeros to get 36288. Finally, you would return 
// the last 3 digits as a string: "288".
// 
// 1)
// 6
// 1
// 
// Returns: "2"
// 
// The factorial of 6 is 720.
// 
// 2)
// 6
// 3
// 
// Returns: "72"
// 
// 
// 
// 3)
// 7
// 2
// 
// Returns: "04"
// 
// The factorial of 7 is 5040. We remove the last zero to get 
// "504". The last 2 digits of "504" are "04".
// 
// 4)
// 20
// 9
// 
// Returns: "200817664"
// 
// 
// 
// 5)
// 1
// 1
// 
// Returns: "1"
// 
// 
// 
// END CUT HERE
#line 80 "KLastNonZeroDigits.cpp"
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

void mul(int *buf, int *len, int n ) {
	int c = 0;

	fi(*len){ 
		int t = (buf[i] * n + c);
		buf[i] = t % 10;
		c = t / 10;
	}

		while (c) {
			buf[*len] = c % 10;
			c /= 10;
			*len = *len + 1;
		}
}

    class KLastNonZeroDigits
        { 
        public: 
        string getKDigits(int N, int K) 
            { 
							int ans[1000];

							memset(ans, 0, sizeof(ans));
							ans[0] = 1;
							int len = 1;

							int c = 0;
							f(i,1,N+1) {
								mul(ans, &len, i);
							}

							int st = 0;
							fi(len) {
								if (ans[i] != 0) break;
								st++;
							}

							int lim = min(st + K, len);
							reverse(ans + st, ans + lim);
							string ret;

							f(i,st,lim) ret += ans[i] + '0';

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 3; string Arg2 = "288"; verify_case(0, Arg2, getKDigits(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arg1 = 1; string Arg2 = "2"; verify_case(1, Arg2, getKDigits(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 3; string Arg2 = "72"; verify_case(2, Arg2, getKDigits(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 2; string Arg2 = "04"; verify_case(3, Arg2, getKDigits(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 20; int Arg1 = 9; string Arg2 = "200817664"; verify_case(4, Arg2, getKDigits(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 1; string Arg2 = "1"; verify_case(5, Arg2, getKDigits(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        KLastNonZeroDigits ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

