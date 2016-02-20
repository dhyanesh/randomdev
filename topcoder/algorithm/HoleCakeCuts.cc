// BEGIN CUT HERE
// PROBLEM STATEMENT
// Little Bonnie has been given a special cake as a reward 
// for her good performance in her Math class.  When viewed 
// from above, the cake is a square, with an empty square 
// hole inside.  Both squares are centered at (0, 0) and 
// their sides are parallel to the x- and y-axes.
// 
// 
// Bonnie is going to cut the cake using several horizontal 
// and vertical cuts.  These cuts are given in the vector 
// <int>s horizontalCuts and verticalCuts.  The i-th 
// horizontal cut is a line parallel to the x-axis which goes 
// through the point (0, horizontalCuts[i]).  Likewise, the i-
// th vertical cut is a line parallel to the y-axis which 
// goes through the point (verticalCuts[i], 0).  All cuts 
// have infinite lengths.
// 
// 
// You are given an int cakeLength, half of the side length 
// of the outer square, and an int holeLength, half of the 
// side length of the inner square hole. Note that both of 
// these numbers are halves of the sides of the corresponding 
// squares. Return the number of pieces of cake that will 
// exist after all the cuts are performed.
// 
// DEFINITION
// Class:HoleCakeCuts
// Method:cutTheCake
// Parameters:int, int, vector <int>, vector <int>
// Returns:int
// Method signature:int cutTheCake(int cakeLength, int 
// holeLength, vector <int> horizontalCuts, vector <int> 
// verticalCuts)
// 
// 
// NOTES
// -A piece is a region of the cake with non-zero area.
// 
// 
// CONSTRAINTS
// -cakeLength will be between 2 and 100, inclusive.
// -holeLength will be between 1 and (cakeLength-1), inclusive.
// -horizontalCuts and verticalCuts will each contain between 
// 0 and 50 elements, inclusive.
// -Each element of horizontalCuts and verticalCuts will be 
// between (-cakeLength+1) and (cakeLength-1), inclusive.
// -Elements of horizontalCuts will be distinct.
// -Elements of verticalCuts will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// 5
// 3
// {1, -4}
// {1}
// 
// Returns: 6
// 
// The cake has the side length of 10, and the side of the 
// hole is 6. Two horizontal and one vertical cuts divide the 
// cake into 6 pieces. Those pieces are colored differently 
// in the following picture:
// 
// 
// 
// 1)
// 10
// 5
// {}
// {-2, 2}
// 
// Returns: 4
// 
// There may be no horizontal cuts.
// 
// 2)
// 10
// 5
// {1}
// {-5, 5}
// 
// Returns: 6
// 
// 
// 
// 3)
// 50
// 5
// {40, -40}
// {20, 0, -20}
// 
// Returns: 12
// 
// 
// 
// END CUT HERE
#line 101 "HoleCakeCuts.cc"
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

    class HoleCakeCuts
        { 
        public: 
        int cutTheCake(int cl, int hl, vector <int> hc, vector <int> vc) 
            { 
              sort(hc.begin(), hc.end());
              sort(vc.begin(), vc.end());

              if (vc.size() == 0 && hc.size() == 0) return 1;
              if (vc.size() == 0) {
                swap(vc, hc);
              }

              int in = 0;
              int top = 0;
              int bot = 0;
              fi(hc.size()) {
                if (hc[i] <= hl && hc[i] >= -hl) ++in;
                else if (hc[i] > hl) ++bot;
                else if (hc[i] < -hl) ++top;
              }

              int ret = 0;
              int pc = -cl;
              fi(vc.size()) {
                if (vc[i] <= hl && vc[i] >= -hl) {
                  if (pc <= hl && pc >= -hl) {
                    ret += hc.size() - in + 2;
                  } else {
                    ret += hc.size() + 1;
                  }
                } else {
                  ret += hc.size() + 1;
                }
                pc = vc[i];
              }

              ret += hc.size() + 1;

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 3; int Arr2[] = {1, -4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; verify_case(0, Arg4, cutTheCake(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 5; int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-2, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 4; verify_case(1, Arg4, cutTheCake(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 5; int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-5, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; verify_case(2, Arg4, cutTheCake(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 50; int Arg1 = 5; int Arr2[] = {40, -40}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20, 0, -20}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 12; verify_case(3, Arg4, cutTheCake(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        HoleCakeCuts ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

