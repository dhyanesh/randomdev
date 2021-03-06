// BEGIN CUT HERE
// PROBLEM STATEMENT
// Frog Jim is fond of jumping.
// Moreover, all his jumps have the same length X.
// Currently, he is standing at the point 0 on the real axis.
// He needs to jump along the axis until he gets to point D 
// or beyond it.
// 
// There are several pits between points 0 and D. 
// For each valid i, there is a pit strictly between L[i] and 
// R[i].
// This means that Jim cannot step onto any point that is 
// strictly between points L[i] and R[i].
// (He is allowed to step onto the points L[i] and R[i]: as 
// all pits are disjoint, the endpoints of each pit are 
// always safe.)
// 
// Find the minimum length of jump X such that if Jim 
// performs only jumps of length X, he can avoid every pit 
// and get to point D or any point beyond it. Note that this 
// length can be non-integer.
// 
// DEFINITION
// Class:TheFrog
// Method:getMinimum
// Parameters:int, vector <int>, vector <int>
// Returns:double
// Method signature:double getMinimum(int D, vector <int> L, 
// vector <int> R)
// 
// 
// NOTES
// -The returned value must have an absolute or relative 
// error less than 1e-9.
// 
// 
// CONSTRAINTS
// -D will be between 1 and 30,000, inclusive.
// -L will contain between 1 and 50 elements, inclusive.
// -Each element of L will be between 0 and D-1, inclusive.
// -R will contain the same number of elements as L.
// -The i-th element of R will be between L[i]+1 and D, 
// inclusive.
// -The intervals given by (L[i], R[i]) will not intersect.
// 
// 
// EXAMPLES
// 
// 0)
// 16
// {2}
// {7}
// 
// Returns: 7.0
// 
// Moving by jumps of length 7, Jim goes from point 0 to 
// point 7, then to point 14 and then to point 21, which is 
// beyond 16. If Jim chose a shorter jump, he would end up in 
// the pit.
// 
// 1)
// 25
// {11, 3}
// {21, 7}
// 
// Returns: 10.5
// 
// There are two pits. One of them is between points 11 and 
// 21 and the other between points 3 and 7. By fixing jump 
// length at 10.5, Jim successfully avoids them.
// 
// 2)
// 100
// {0}
// {100}
// 
// Returns: 100.0
// 
// Jim has no other choice but to jump right to point 100.
// 
// 3)
// 100
// {0, 50}
// {50, 100}
// 
// Returns: 50.0
// 
// In this case, point 50 is a suitable place to land, so Jim 
// can choose X = 50.
// 
// 4)
// 30000
// {17, 25281, 5775, 2825, 14040}
// {55, 26000, 5791, 3150, 14092}
// 
// Returns: 787.8787878787879
// 
// 
// 
// END CUT HERE
#line 102 "TheFrog.cc"
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

    class TheFrog
        { 
        public: 
          bool isOK(long double min, vector<pair<int, int> > pits, int ind) {
            long double m = pits[ind].second;
            long double curr = min;
            while (curr < m) {
              fi (ind + 1) {
                if (curr > pits[i].first && curr < pits[i].second) {
                  return false;
                }
              }
              curr += min;
            }
            return true;
          }

        double getMinimum(int D, vector <int> L, vector <int> R) { 
          vector<pair<int, int> > pits;
          fi (L.size()) {
            pits.push_back(make_pair(L[i], R[i]));
          }
          sort(pits.begin(), pits.end());

          long double min = 0.0;
          fi (pits.size()) {
            min = std::max(min, (long double)pits[i].second - pits[i].first);
          }

          long double curr = min;
          while (curr < D) {
            fi (pits.size()) {
              if (curr > pits[i].first && curr < pits[i].second) {
                long double new_min = pits[i].second;
                int fac = new_min / min;

                for (int f = fac; f >= 1; f--) {
                  long double try_min = new_min / f;
                  if (isOK(try_min, pits, i)) {
                    min = try_min;
                    break;
                  }
                }
                curr = 0;
                break;
              }
            }
            curr += min;
          }

          return min;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 16; int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 7.0; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 25; int Arr1[] = {11, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {21, 7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 10.5; verify_case(1, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 100; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 100.0; verify_case(2, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 100; int Arr1[] = {0, 50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 50.0; verify_case(3, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 30000; int Arr1[] = {17, 25281, 5775, 2825, 14040}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {55, 26000, 5791, 3150, 14092}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 787.8787878787879; verify_case(4, Arg3, getMinimum(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheFrog ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

