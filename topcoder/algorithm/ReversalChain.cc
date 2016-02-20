// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Given a string, the reversal operation r(i, j) reverses 
// the substring of the string from the i-th character to the 
// j-th character (0-indexed, inclusive).  A reversal chain 
// is a sequence of reversals where the range of each 
// reversal is included in the range of the previous 
// reversal.  Formally, the sequence r(i1, j1), r(i2, j2), 
// ..., r(im, jm) is a reversal chain if i1 <= i2 <= ... <= 
// im, and j1 >= j2 >= ... >= jm.
// 
// 
// You are given a string init which contains only '0' (zero) 
// and '1' (one) characters.  You want to transform this 
// string into the string goal using a reversal chain. Return 
// the minimum possible length of a reversal chain that 
// transforms init into goal. Return -1 if it is impossible.
// 
// 
// DEFINITION
// Class:ReversalChain
// Method:minReversal
// Parameters:string, string
// Returns:int
// Method signature:int minReversal(string init, string goal)
// 
// 
// CONSTRAINTS
// -init will contain between 1 and 50 characters, inclusive.
// -init and goal will contain the same number of characters.
// -Each character of init and goal will be '0' (zero) or '1' 
// (one).
// 
// 
// EXAMPLES
// 
// 0)
// "1100"
// "0110"
// 
// Returns: 1
// 
// r(0, 2) transforms "1100" into "0110".
// 
// 1)
// "111000"
// "101010"
// 
// Returns: 2
// 
// r(1, 4) and r(2, 3) transforms "111000" into "101010".
// 
// 2)
// "0"
// "1"
// 
// Returns: -1
// 
// It is impposible to transform "0" into "1" by a reversal 
// chain.
// 
// 3)
// "10101"
// "10101"
// 
// Returns: 0
// 
// You do not have to do anything.
// 
// 4)
// "111000111000"
// "001100110011"
// 
// Returns: 4
// 
// 
// 
// END CUT HERE
#line 81 "ReversalChain.cc"
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

    class ReversalChain
        { 
        public: 
        int minReversal(string init, string goal) 
            { 
              int n = init.size();
              int ci = 0;
              int cj = n - 1;

              int ret = 0;
              while (true) {
                while (ci < cj && init[ci] == goal[ci]) {
                  ++ci;
                }
                while (ci < cj && init[cj] == goal[cj]) {
                  --cj;
                }
                if (ci >= cj) break;
                reverse(init.begin() + ci, init.begin() + cj + 1);
                ++ret;
              }

              if (init != goal) return -1;

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "01110"; string Arg1 = "11001"; int Arg2 = 1; verify_case(0, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "111000"; string Arg1 = "101010"; int Arg2 = 2; verify_case(1, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "0"; string Arg1 = "1"; int Arg2 = -1; verify_case(2, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "10101"; string Arg1 = "10101"; int Arg2 = 0; verify_case(3, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "111000111000"; string Arg1 = "001100110011"; int Arg2 = 4; verify_case(4, Arg2, minReversal(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ReversalChain ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

