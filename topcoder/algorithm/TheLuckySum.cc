// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// John thinks 4 and 7 are lucky digits, and all other digits 
// are not lucky.  A lucky number is a number that contains 
// only lucky digits in decimal notation.
// 
// 
// 
// Some numbers can be represented as a sum of only lucky 
// numbers.  Given an int n, return a vector <int> whose 
// elements sum to exactly n.  Each element of the vector 
// <int> must be a lucky number.  If there are multiple 
// solutions, only consider those that contain the minimum 
// possible number of elements, and return the one among 
// those that comes earliest lexicographically.  A vector 
// <int> a1 comes before a vector <int> a2 lexicographically 
// if a1 contains a smaller number at the first position 
// where they differ.  If n cannot be represented as a sum of 
// lucky numbers, return an empty vector <int> instead.
// 
// 
// 
// DEFINITION
// Class:TheLuckySum
// Method:sum
// Parameters:int
// Returns:vector <int>
// Method signature:vector <int> sum(int n)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 11
// 
// Returns: {4, 7 }
// 
// It is simple: 11 = 4 + 7.
// 
// 1)
// 12
// 
// Returns: {4, 4, 4 }
// 
// Now we need three summands to get 12.
// 
// 2)
// 13
// 
// Returns: { }
// 
// And now we can not get 13 at all.
// 
// 3)
// 100
// 
// Returns: {4, 4, 4, 44, 44 }
// 
// END CUT HERE
#line 66 "TheLuckySum.cc"
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

VI best;
vector<long long> st;

    class TheLuckySum
        { 
        public: 
        vector <int> sum(int n) 
            { 
              best.clear();
              st.clear();

              priority_queue<long long, vector<long long>, greater<long long> > all;
              all.push(4);
              all.push(7);

              while (true) {
                long long p = all.top();
                all.pop();
                if (p > 1000000000) break;

                st.push_back(p);
                all.push(p*10 + 4);
                all.push(p*10 + 7);
              }

              priority_queue<long long, vector<long long>, greater<long long> > sums;

            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 11; int Arr1[] = {4, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, sum(Arg0)); }
	void test_case_1() { int Arg0 = 12; int Arr1[] = {4, 4, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, sum(Arg0)); }
	void test_case_2() { int Arg0 = 13; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, sum(Arg0)); }
	void test_case_3() { int Arg0 = 100; int Arr1[] = {4, 4, 4, 44, 44 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, sum(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheLuckySum ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

