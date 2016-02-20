// BEGIN CUT HERE
// PROBLEM STATEMENT
// A plane fractal grows in the following way.  At time 0, 
// the fractal is a single white square.  During each unit of 
// time, each square in the fractal is divided into an NxN 
// grid of equal subsquares.  If the square was white, then 
// the center KxK subsquares will become black (N and K will 
// have the same parity).
// 
// For example, if N = 3 and K = 1, then at time 1, there are 
// 3x3 squares, the middle square is black and the rest are 
// white.  At time 2, there are 9x9 squares, 17 are black and 
// the rest are white.
// 
// 
// 
// Return a vector <string> representing the content of the 
// fractal at time s between rows r1 and r2, inclusive, and 
// columns c1 and c2, inclusive (all indices are 0-based).  
// White squares should be represented by '0' (zero) and 
// black squares should be represented by '1'.
// 
// DEFINITION
// Class:PlaneFractal
// Method:getPattern
// Parameters:int, int, int, int, int, int, int
// Returns:vector <string>
// Method signature:vector <string> getPattern(int s, int N, 
// int K, int r1, int r2, int c1, int c2)
// 
// 
// CONSTRAINTS
// -s will be between 0 and 10, inclusive.
// -N will be between 3 and 8, inclusive.
// -K will be between 1 and N-2, inclusive.
// -N and K will have the same parity, i.e., N-K will be 
// divisible by 2.
// -r1, r2, c1 and c2 will each be between 0 and N^s-1, 
// inclusive.
// -r2 will be between r1 and r1+49, inclusive.
// -c2 will be between c1 and c1+49, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 5
// 3
// 0
// 4
// 0
// 4
// 
// Returns: {"00000", "01110", "01110", "01110", "00000" }
// 
// At time 1, there are 5x5 squares, the middle 3x3 of them 
// are black.
// 
// 1)
// 2
// 3
// 1
// 0
// 8
// 0
// 8
// 
// Returns: {"000000000", "010010010", "000000000", 
// "000111000", "010111010", "000111000", "000000000", 
// "010010010", "000000000" }
// 
// The example from the problem statement.
// 
// 2)
// 3
// 3
// 1
// 4
// 11
// 5
// 10
// 
// Returns: {"101001", "100000", "000000", "001001", 
// "000000", "000011", "001011", "000011" }
// 
// At time 3, the fractal looks like this (the area that 
// needs to be returned is shown in red):
// 
// 
// 
// 3)
// 2
// 8
// 4
// 56
// 61
// 33
// 56
// 
// Returns: {"000000000000000000000000", 
// "000000000000000000000000", "011110000111100001111000", 
// "011110000111100001111000", "011110000111100001111000", 
// "011110000111100001111000" }
// 
// 
// 
// END CUT HERE
#line 110 "PlaneFractal.cc"
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

    class PlaneFractal
        { 
        public: 

        bool white(int i,int j, int N, int K, int s) {
          if (s == 0) return true;
          ll si = 1;
          f(k,0,s) si *= N;

          int li = i - i % N;
          int lj = j - j % N;

          int p = (N-K) /  2;

          if (i >= li + p && i < li + p + K &&
              j >= lj + p && j < lj + p + K) {
            return false;
          }

          return white(li/N, lj/N, N, K, s-1);
        }

        vector <string> getPattern(int s, int N, int K, int r1, int r2, int c1, int c2) { 
          VS ret;
          f(i,r1,r2 + 1) {
            string t(c2-c1+1, ' ');
            f(j,c1,c2 + 1) {
              if (white(i,j,N,K,s)) {
                t[j-c1] = '0';
              } else {
                t[j-c1] = '1';
              }
            }
            ret.push_back(t);
          }

          return ret;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 3; int Arg3 = 0; int Arg4 = 4; int Arg5 = 0; int Arg6 = 4; string Arr7[] = {"00000", "01110", "01110", "01110", "00000" }; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(0, Arg7, getPattern(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 1; int Arg3 = 0; int Arg4 = 8; int Arg5 = 0; int Arg6 = 8; string Arr7[] = {"000000000", "010010010", "000000000", "000111000", "010111010", "000111000", "000000000", "010010010", "000000000" }; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(1, Arg7, getPattern(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 1; int Arg3 = 4; int Arg4 = 11; int Arg5 = 5; int Arg6 = 10; string Arr7[] = {"101001", "100000", "000000", "001001", "000000", "000011", "001011", "000011" }; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(2, Arg7, getPattern(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 8; int Arg2 = 4; int Arg3 = 56; int Arg4 = 61; int Arg5 = 33; int Arg6 = 56; string Arr7[] = {"000000000000000000000000", "000000000000000000000000", "011110000111100001111000", "011110000111100001111000", "011110000111100001111000", "011110000111100001111000" }; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(3, Arg7, getPattern(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PlaneFractal ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

