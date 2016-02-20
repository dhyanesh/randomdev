// BEGIN CUT HERE
// PROBLEM STATEMENT
// A string of letters A, B, C is forbidden if there are 
// three consecutive letters from which one is A, one is B, 
// and one is C. For example, BAACAACCBAAA is forbidden, 
// while AABBCCAABB is not.
// 
// Your task is to calculate how many such strings of length 
// n are not forbidden.
// 
// 
// DEFINITION
// Class:ForbiddenStrings
// Method:countNotForbidden
// Parameters:int
// Returns:long long
// Method signature:long long countNotForbidden(int n)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 30, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// 
// Returns: 9
// 
// All 9 strings of length 2 are not forbidden.
// 
// 
// 1)
// 3
// 
// Returns: 21
// 
// There are 27 strings of length 3. Of these, 6 contain one 
// occurrence of each letter. Those 6 strings are forbidden, 
// so you should return 21.
// 
// 
// 2)
// 4
// 
// Returns: 51
// 
// 
// 
// END CUT HERE
#line 53 "ForbiddenStrings.cc"
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

ll memo[4][4][35];

bool valid(int a, int b, int c) {
  int arr[3] = {a,b,c};
  sort(arr, arr + 3);
  if (arr[0] == 1 && arr[1] == 2 && arr[2] == 3) return false;
  return true;
}

ll go(int p1, int p2, int n) {
  if (n == 0) return 1;

  ll &ret = memo[p1][p2][n];
  if (ret > 0) return ret;

  ret = 0;
  f(i, 1, 4) {
    if (valid(i,p1,p2))
      ret += go(p2, i, n - 1);
  }
  return ret;
}

    class ForbiddenStrings
        { 
        public: 
        long long countNotForbidden(int n) 
            { 
              memset(memo, 0, sizeof(memo));
              return go(0, 0, n);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; long long Arg1 = 9LL; verify_case(0, Arg1, countNotForbidden(Arg0)); }
	void test_case_1() { int Arg0 = 3; long long Arg1 = 21LL; verify_case(1, Arg1, countNotForbidden(Arg0)); }
	void test_case_2() { int Arg0 = 4; long long Arg1 = 51LL; verify_case(2, Arg1, countNotForbidden(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ForbiddenStrings ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

