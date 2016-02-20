// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// John thinks 4 and 7 are lucky digits, and all other digits 
// are not lucky.  A lucky number is a number that contains 
// only lucky digits in decimal notation.
// 
// 
// 
// You are given ints a and b.  Return the number of lucky 
// numbers between a and b, inclusive.
// 
// 
// 
// DEFINITION
// Class:TheLuckyNumbers
// Method:count
// Parameters:int, int
// Returns:int
// Method signature:int count(int a, int b)
// 
// 
// CONSTRAINTS
// -a will be between 1 and 1,000,000,000, inclusive.
// -b will be between a and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 10
// 
// Returns: 2
// 
// There are only two lucky numbers among the first ten 
// positive integers.
// 
// 1)
// 11
// 20
// 
// Returns: 0
// 
// But there are none among the next ten.
// 
// 2)
// 74
// 77
// 
// Returns: 2
// 
// These two numbers are lucky. There are no additional lucky 
// numbers between them.
// 
// 
// 3)
// 1000000
// 5000000
// 
// Returns: 64
// 
// 
// 
// END CUT HERE
#line 67 "TheLuckyNumbers.cc"
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
#include <queue>    
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

    class TheLuckyNumbers
        { 
        public: 
        int count(int a, int b) 
            { 
              priority_queue<long long, vector<long long>, greater<long long> > all;
              all.push(4);
              all.push(7);
              vector<long long> st;

              while (true) {
                long long p = all.top();
                all.pop();
                if (p > 1000000000) break;

                st.push_back(p);
                all.push(p*10 + 4);
                all.push(p*10 + 7);
              }
              cout << st.size();

              int s = 0;
              int e = 0;
              for( ; s < st.size(); ++s) {
                if (st[s] >= a) break;
              }
              int ret = 0;
              for(e = s; e < st.size(); ++e) {
                if (st[s] >= a && st[e] <= b) ret++; else break;
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 2; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 11; int Arg1 = 20; int Arg2 = 0; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 74; int Arg1 = 77; int Arg2 = 2; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1000000; int Arg1 = 5000000; int Arg2 = 64; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheLuckyNumbers ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

