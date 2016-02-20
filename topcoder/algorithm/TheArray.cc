// BEGIN CUT HERE
// PROBLEM STATEMENT
// John has an array of n integers.
// Each pair of neighboring elements differs by at most d.
// The first and the last elements of the array are equal to 
// first and last, respectively.
// 
// 
// Brus does not know John's array.
// He only knows n, d, first and last.
// He wants to compute the maximal possible element John 
// might have in his array.
// 
// 
// You are given ints n, d, first and last.
// Return the maximal possible element the array might contain.
// 
// 
// DEFINITION
// Class:TheArray
// Method:find
// Parameters:int, int, int, int
// Returns:int
// Method signature:int find(int n, int d, int first, int last)
// 
// 
// NOTES
// -The constraints given below guarantee that there will 
// always be at least one array that matches the values Brus 
// knows.
// -For the constraints given below, the correct answer will 
// always fit into an int.
// 
// 
// CONSTRAINTS
// -n will be between 2 and 1,000,000, inclusive.
// -d will be between 0 and 1000, inclusive.
// -first will be between -1000 and 1000, inclusive.
// -last will be between -1000 and 1000, inclusive.
// -|first - last| will be at most (n-1)*d.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// 5
// 2
// 4
// 
// Returns: 7
// 
// Only the second element of the array is unknown.
// Its maximal valid value is 7.
// 
// 
// 1)
// 10
// 100
// 999
// 100
// 
// Returns: 999
// 
// Due to the limitations, the first element is the largest 
// element of the array.
// 
// 2)
// 1000000
// 0
// 474
// 474
// 
// Returns: 474
// 
// All elements of the array are equal.
// 
// 3)
// 97
// 53
// -92
// 441
// 
// Returns: 2717
// 
// 
// 
// 4)
// 99
// 3
// -743
// -619
// 
// Returns: -535
// 
// 
// 
// END CUT HERE
#line 100 "TheArray.cc"
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

    class TheArray
        { 
        public: 
        int find(int n, int d, int first, int last) { 
          int ma = std::max(first, last);
          int mi = std::min(first, last);

          int mid = -1;
          int num = 0;
          fi(n - 1) {
            num = i * d + mi;
            mid = i;

            int diff = abs(num - ma);
            if (diff <= (n - i - 1) * d) {
              ;
            } else {
              mid = i - 1;
              break;
            }
          }

          cout << mid << endl;
          return mid * d + mi;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 2; int Arg3 = 4; int Arg4 = 7; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 999; int Arg3 = 100; int Arg4 = 999; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1000000; int Arg1 = 0; int Arg2 = 474; int Arg3 = 474; int Arg4 = 474; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 97; int Arg1 = 53; int Arg2 = -92; int Arg3 = 441; int Arg4 = 2717; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 99; int Arg1 = 3; int Arg2 = -743; int Arg3 = -619; int Arg4 = -535; verify_case(4, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheArray ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

