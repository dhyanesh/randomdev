// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// In a Las Vegas casino, a new type of six-sided die is 
// being introduced. These dice may have any positive 
// integers written its sides, but no two sides of the same 
// die can contain the same number. For each die, the casino 
// owner wants the mean value of the numbers written on its 
// sides to not exceed M.
// 
// 
// 
// Compute the total number of allowed dice. Two dice are 
// considered different if one can't be obtained from the 
// other using rotations. Since the resulting number may be 
// quite large, return it modulo 1000000007.
// 
// 
// DEFINITION
// Class:CustomDice
// Method:countDice
// Parameters:int
// Returns:int
// Method signature:int countDice(int M)
// 
// 
// CONSTRAINTS
// -M will be between 1 and 1000000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// 
// Returns: 0
// 
// The die with the smallest possible mean is {1,2,3,4,5,6}.  
// Its mean is 3.5, which is greater than M=3.
// 
// 1)
// 4
// 
// Returns: 210
// 
// There are 30 different dice with numbers {1,2,3,4,5,6} on 
// their sides, they each have a mean of 3.5.
// There are 30 different dice with numbers {1,2,3,4,5,7} on 
// their sides, they each have a mean of 22/6=3.(6).
// There are 60 different dice with {1,2,3,4,5,8} or 
// {1,2,3,4,6,7} on their sides, they each have a mean of 
// 23/6=3.8(3).
// There are 90 different dice with {1,2,3,4,5,9}, 
// {1,2,3,4,6,8} or {1,2,3,5,6,7} on their sides, they each 
// have a mean of 24/6=4.
// 
// 2)
// 10
// 
// Returns: 863010
// 
// 
// 
// 3)
// 50
// 
// Returns: 375588112
// 
// 
// 
// END CUT HERE
#line 73 "CustomDice.cc"
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
#define MOD 1000000007

typedef vector <int> VI;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   
typedef long long ll;

map<pair<int,int>, ll > memo[6];

int sum[] = { 0, 0, 1, 3, 6 , 10, 15, 21 };

ll go(int pos, int count, int less) {
  if (pos == 0) {
    if (count < less) return 1;
    return 0;
  }

  pair<int,int> t(count,less);

  if (memo[pos].count(t) > 0) return memo[pos][t];

  int cu = count;
  int pr = pos;

  if (count >= less) {
    cu = less - 1;
    pr = pos + (count - cu);
  }

  ll &ret = memo[pos][t];
  ret = 0;
  while (pos * cu > pr + sum[pos]) {
    ret = (ret + go(pos - 1, pr, cu)) % MOD;
    ++pr;
    --cu;
  }

  return ret;
}

    class CustomDice
        { 
        public: 
        int countDice(int M) 
            { 
              int ma = 6 * M - 15;
              if (ma < 6) return 0;

              fi(6)
              memo[i].clear();

              ll ret = 0;
              for(int i = 6; i <= ma; ++i) {
                ret = (ret + go(5, i, i + 1)) % MOD;
              }
              return (ret * 30) % MOD;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 0; verify_case(0, Arg1, countDice(Arg0)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 210; verify_case(1, Arg1, countDice(Arg0)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 863010; verify_case(2, Arg1, countDice(Arg0)); }
	void test_case_3() { int Arg0 = 50; int Arg1 = 375588112; verify_case(3, Arg1, countDice(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CustomDice ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

