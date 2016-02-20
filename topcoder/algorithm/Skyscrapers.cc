// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// The skyline of the city of Terrapin City has N buildings 
// all in a straight line; each building has a distinct 
// height between 1 and N, inclusive.  The building at index 
// i is considered visible from the left is there is no 
// building with a smaller index that is taller (formally, 
// height[j] &lt height[i] for all j &lt i).  Similarly, a 
// building is visible from the right if there is no taller 
// building with a higher index (height[j] &lt height[i] for 
// all j &gt i).  For example, if the buildings in order are 
// {1, 3, 5, 2, 4}, then three buildings are visible from the 
// left (1, 3 and 5), but only two are visible from the right 
// (4 and 5).
// 
// You will be given N, leftSide and rightSide, corresponding 
// to the total number of buildings, the buildings visible 
// from the left, and the buildings visible from the right, 
// respectively.  Return the number of permutations of the 
// buildings that are consistent with these values; as this 
// can be a large number, you should return it modulo 
// 1000000007.
// 
// 
// DEFINITION
// Class:Skyscrapers
// Method:buildingCount
// Parameters:int, int, int
// Returns:int
// Method signature:int buildingCount(int N, int leftSide, 
// int rightSide)
// 
// 
// CONSTRAINTS
// -N will be between 1 and 100, inclusive.
// -leftSide and rightSide will be between 1 and N, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// 2
// 2
// 
// Returns: 2
// 
// There are two arrangements of buildings that match these 
// requirements:  {1, 3, 2} and {2, 3, 1}.
// 
// 1)
// 3
// 2
// 1
// 
// Returns: 1
// 
// Only {2, 1, 3} fits these requirements.
// 
// 2)
// 5
// 3
// 2
// 
// Returns: 18
// 
// 
// 
// 3)
// 12
// 1
// 1
// 
// Returns: 0
// 
// With 12 buildings, it is impossible for you to only see 
// one building from each side.
// 
// 4)
// 8
// 3
// 2
// 
// Returns: 4872
// 
// 
// 
// END CUT HERE
#line 91 "Skyscrapers.cc"
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

int no;

ll memo[101][101][101];

ll go(int b, int l, int r) {
  if (b == 0) {
    if (l == 0 && r == 0) 
      return 1;
    else 
      return 0;
  }
  if (l < 0 ) return 0;
  if (r < 0 ) return 0;

  ll &ret = memo[b][l][r];
  if (ret >= 0) return ret;
  ret = 0;

  ret += go(b-1, l-1,r );
  ret %=1000000007; 
  ret += go(b-1, l,r-1);
  ret %=1000000007; 

  if (no - b - 1 > 0) {
    ret += ((no - b - 1) * (ll)go(b-1,l,r)) % 1000000007;
    ret %=1000000007; 
  }

  return ret;
}

    class Skyscrapers
        { 
        public: 
        int buildingCount(int n, int l, int r) 
            { 
              no = n;
              memset(memo, 0xff, sizeof(memo));
              return go(n-1, l-1, r-1);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; verify_case(0, Arg3, buildingCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; int Arg3 = 1; verify_case(1, Arg3, buildingCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 2; int Arg3 = 18; verify_case(2, Arg3, buildingCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 12; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; verify_case(3, Arg3, buildingCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 8; int Arg1 = 3; int Arg2 = 2; int Arg3 = 4872; verify_case(4, Arg3, buildingCount(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Skyscrapers ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

