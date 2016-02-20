// BEGIN CUT HERE
// PROBLEM STATEMENT
// There are several skyscrapers arranged in a row.  You're 
// interested in finding the one from which the maximal 
// number of other skyscrapers can be seen.  The i-th 
// skyscraper can be represented as a line segment on a plane 
// with endpoints (i, 0) and (i, heights[i]).  A skyscraper 
// can be seen from the roof of another skyscraper if a line 
// segment connecting their roofs does not intersect with or 
// touch any other skyscraper.  Return the maximal number of 
// other skyscrapers that can be seen from the roof of some 
// skyscraper.
// 
// DEFINITION
// Class:BestView
// Method:numberOfBuildings
// Parameters:vector <int>
// Returns:int
// Method signature:int numberOfBuildings(vector <int> heights)
// 
// 
// CONSTRAINTS
// -heights will contain between 1 and 50 elements, inclusive. 
// -Each element of heights will be between 1 and 
// 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {10}
// 
// Returns: 0
// 
// There's only a single skyscraper, so you can see no other 
// skyscrapers from its roof.
// 
// 
// 1)
// {5,5,5,5}
// 
// Returns: 2
// 
// From each skyscraper, you can only see its adjacent 
// neighbors.
// 
// 2)
// {1,2,7,3,2}
// 
// Returns: 4
// 
// You can see all the other skyscrapers from the central one.
// 
// 3)
// {1,5,3,2,6,3,2,6,4,2,5,7,3,1,5}
// 
// Returns: 7
// 
// You can see seven skyscrapers from the skyscraper with 
// height 7:
// 
// 
// 4)
// {1000000000,999999999,999999998,999999997,999999996,1,2,3,4,5}

// 
// Returns: 6
// 
// You can see 6 skyscrapers from the skyscraper with height 
// 999999996 - the nearest one to the left and all 5 
// skyscrapers to the right.
// 
// 5)
// {244645169,956664793,752259473,577152868,605440232,569378507,111664772,653430457,454612157,397154317}

// 
// Returns: 7
// 
// 
// 
// END CUT HERE
#line 83 "BestView.cc"
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

    class BestView
        { 
        public: 
          bool ok(VI &hts, long long st, long long en, long long mid) {
            return (hts[mid] - hts[st]) * (en - st) < (hts[en] - hts[st]) * (mid - st);
          }

        int numberOfBuildings(vector <int> hts) { 
          int max = 0;

          fi(hts.size()) {
            int c = 0;
            f(j,0,i) {
              bool f = true;
              f(k,j+1,i) {
                if (!ok(hts, j, i, k)) {
                  f = false;
                  break;
                }
              }
                  if (f) ++c;
            }
            f(j,i+1,hts.size()) {
              bool f = true;
              f(k,i+1,j) {
                if (!ok(hts, i, j, k)) {
                  f = false;
                  break;
                }
              }
                  if (f) ++c;
            }
            max = max > c ? max : c;
          }

          return max;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, numberOfBuildings(Arg0)); }
	void test_case_1() { int Arr0[] = {5,5,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, numberOfBuildings(Arg0)); }
	void test_case_2() { int Arr0[] = {1,2,7,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, numberOfBuildings(Arg0)); }
	void test_case_3() { int Arr0[] = {1,5,3,2,6,3,2,6,4,2,5,7,3,1,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, numberOfBuildings(Arg0)); }
	void test_case_4() { int Arr0[] = {1000000000,999999999,999999998,999999997,999999996,1,2,3,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(4, Arg1, numberOfBuildings(Arg0)); }
	void test_case_5() { int Arr0[] = {244645169,956664793,752259473,577152868,605440232,569378507,111664772,653430457,454612157,397154317}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(5, Arg1, numberOfBuildings(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BestView ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

