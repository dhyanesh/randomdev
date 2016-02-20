// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are given three integers: a, b and c.  Convert each of 
// them into their binary representations with no leading 
// zeroes.  Let x be the number of binary digits in the 
// longest of the three.  Add leading zeroes to the others 
// until all of them have exactly x digits.
// 
// 
// Transform a, b and c into a', b' and c', such that 
// a'+b'=c', by optionally reordering the digits within each 
// number.  Leading zeroes are allowed.  If there are several 
// ways to do this, use the one that minimizes c'.
// 
// 
// For example, let a = 7, b = 6 and c = 9.  In binary 
// notation, a = 111, b = 110 and c = 1001.  We add leading 
// zeroes to a and b so that all of them have exactly four 
// digits: a = 0111, b = 0110, c = 1001.  Now, if we reorder 
// the digits within each number to get a' = 0111, b' = 0011 
// and c' = 1010, we satisfy a' + b' = c' (7 + 3 = 10).  
// There is another way to do this as well (7 + 5 = 12), but 
// this is the way that minimizes c'.
// 
// 
// You are given ints a, b and c. Return the minimal possible 
// value of c'. If there is no solution, return -1.
// 
// 
// DEFINITION
// Class:BinarySum
// Method:rearrange
// Parameters:int, int, int
// Returns:int
// Method signature:int rearrange(int a, int b, int c)
// 
// 
// CONSTRAINTS
// -a, b and c will each be between 1 and 2^30, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 7
// 6
// 9
// 
// Returns: 10
// 
// The example from the problem statement.
// 
// 1)
// 1
// 1
// 2
// 
// Returns: 2
// 
// 
// 
// 2)
// 1
// 1
// 4
// 
// Returns: 2
// 
// Leading zeroes are allowed.
// 
// 3)
// 3
// 3
// 9
// 
// Returns: 6
// 
// 
// 
// 4)
// 1
// 1
// 1
// 
// Returns: -1
// 
// 
// 
// 5)
// 32517565
// 204650420
// 4096
// 
// Returns: -1
// 
// END CUT HERE
#line 99 "BinarySum.cc"
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

void co(int no, int &o, int &z) {
  o = 0;
  z = 0;
  while (no) {
    if (no&1) ++o; else ++z;
    no >>= 1;
  }
}

ll n;

ll memo[35][35][35][3][35];

ll go(int oa, int ob, int oc, int c, int d) {
  if (oa < 0 || ob < 0 || oc < 0) return -1;
  if (d >= n) {
    if (oa + ob + oc + c == 0) return 0;
    return -1;
  }

  ll &ret = memo[oa][ob][oc][c][d];
  if (ret >= -1) return ret;
  ret = 1LL<<40;
  fi(4) {
    int noa = oa;
    int va = 0;
    int nob = ob;
    int vb = 0;
    if (i & 1) {
      --noa;
      va = 1;
    }
    if (i & 2) {
      --nob;
      vb = 1;
    }

    int res = va + vb + c;
    int ca = res / 2;
    res %= 2;

    int noc = oc;
    if (res) --noc;

    ll t = go(noa, nob, noc, ca, d + 1);
    if (t == -1) continue;

    t <<= 1;
    t |= res;

    ret <?= t;
  }

  if (ret == 1LL<<40) ret = -1;

  return ret;
}

    class BinarySum
        { 
        public: 
        int rearrange(int a, int b, int c) 
            { 
              int ca,cb,cc,oa,ob,oc;

              memset(memo, 0xfe, sizeof(memo));

              co(a, oa, ca);
              ca+=oa;
              co(b, ob, cb);
              cb+=ob;
              co(c, oc, cc);
              cc+=oc;

              n = 0;
              n = ca > cb ? ca : cb;
              n = n > cc ? n : cc;

              return go(oa, ob, oc, 0, 0);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arg1 = 6; int Arg2 = 9; int Arg3 = 10; verify_case(0, Arg3, rearrange(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; verify_case(1, Arg3, rearrange(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(2, Arg3, rearrange(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 9; int Arg3 = 6; verify_case(3, Arg3, rearrange(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = -1; verify_case(4, Arg3, rearrange(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 32517565; int Arg1 = 204650420; int Arg2 = 4096; int Arg3 = -1; verify_case(5, Arg3, rearrange(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BinarySum ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

