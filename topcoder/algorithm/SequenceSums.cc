// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Given a number N and a length L, find the shortest list of 
// at least L consecutive non-negative integers whose sum is N.
// If the length of that list is 100 or smaller, return the 
// sequence as a vector <int> in ascending order.
// If there is no such sequence or its length is larger than 
// 100, return { }.
// 
// 
// DEFINITION
// Class:SequenceSums
// Method:sequence
// Parameters:int, int
// Returns:vector <int>
// Method signature:vector <int> sequence(int N, int L)
// 
// 
// CONSTRAINTS
// -N will be between 1 and 1000000000, inclusive.
// -L will be between 2 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 18
// 2
// 
// Returns: {5, 6, 7 }
// 
// 18 can be expressed as 5 + 6 + 7 or 3 + 4 + 5 + 6. Both of 
// these lists contain more than 2 elements, so you should 
// return the shortest among them.
// 
// 1)
// 18
// 4
// 
// Returns: {3, 4, 5, 6 }
// 
// Now the correct answer is 3 + 4 + 5 + 6 because 5 + 6 + 7 
// contains less than 4 elements.
// 
// 2)
// 18
// 5
// 
// Returns: { }
// 
// Both possible presentations of 18 contain less than 5 
// elements, so there's no answer for this case.
// 
// 3)
// 45
// 10
// 
// Returns: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
// 
// 
// 
// 4)
// 1000000000
// 2
// 
// Returns: {199999998, 199999999, 200000000, 200000001, 
// 200000002 }
// 
// 
// 
// END CUT HERE
#line 74 "SequenceSums.cc"
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

    class SequenceSums
        { 
        public: 
        vector <int> sequence(int n, int l) 
            { 
              VI ret;

              f(i, l, 101) {
                int a = 2*n - i*i + i;
                if (a<0) continue;
                if (a % (2 * i) == 0) {
                  a/=(2*i);
                  fj(i)
                    ret.push_back(a++);
                  return ret;
                }
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 18; int Arg1 = 2; int Arr2[] = {5, 6, 7 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, sequence(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 18; int Arg1 = 4; int Arr2[] = {3, 4, 5, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, sequence(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 18; int Arg1 = 5; int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, sequence(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 45; int Arg1 = 10; int Arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, sequence(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 2; int Arr2[] = {199999998, 199999999, 200000000, 200000001, 200000002 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, sequence(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SequenceSums ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

