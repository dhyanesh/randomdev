// BEGIN CUT HERE
// PROBLEM STATEMENT
// A big box contains marbles of one or more colors. You're 
// given a vector <int> colors, each element of which denotes 
// the number of marbles there are of a particular color. You 
// draw n marbles randomly from the box, leaving each marble 
// outside the box after taking it. Return the probability 
// that all marbles drawn will be the same color.
// 
// DEFINITION
// Class:DrawingMarbles
// Method:sameColor
// Parameters:vector <int>, int
// Returns:double
// Method signature:double sameColor(vector <int> colors, int 
// n)
// 
// 
// NOTES
// -Every time we draw a marble, all marbles in the box are 
// equally likely to be chosen.
// -A return value with either an absolute or relative error 
// of less than 1.0E-9 is considered correct.
// 
// 
// CONSTRAINTS
// -colors will contain between 1 and 50 elements, inclusive.
// -Each element of colors will be between 1 and 50, inclusive.
// -n will be between 1 and the sum of all elements of 
// colors, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// { 13 }
// 8
// 
// Returns: 1.0
// 
// All the marbles are the same color, so obviously all drawn 
// marbles will be the same color too.
// 
// 1)
// { 5, 7 }
// 1
// 
// Returns: 1.0
// 
// 
// 
// 2)
// { 5, 6, 7 }
// 2
// 
// Returns: 0.3006535947712418
// 
// The probability that the first drawn marble will be of the 
// color 0 is 5 / 18 (there are 5 marbles of color 0 out of 
// 18). If the first drawn marble is of the color 0, then the 
// probability that the second drawn marble will be of the 
// color 0 is 4 / 17 (there are 4 marbles of color 0 left out 
// of 17). So the probability that both drawn marbles will be 
// of the color 0 is (5 / 18) * (4 / 17) = 0.0653594771... . 
// Similarly, the probability that both drawn marbles will be 
// of the color 1 is (6 / 18) * (5 / 17) = 0.0980392156..., 
// and that both drawn marbles will be of the color 2 is (7 / 
// 18) * (6 / 17) = 0.1372549019... . The answer is the sum 
// of these 3 probabilities.
// 
// 3)
// { 12, 2, 34, 13, 17 }
// 4
// 
// Returns: 0.035028830818304504
// 
// 
// 
// END CUT HERE
#line 81 "DrawingMarbles.cpp"
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

double memo[2505][2505];
bool done[2505][2505];

double ncr(int n, int r) {
	if (done[n][r]) {
		return memo[n][r];
	}
	if (r == 0) {
		return memo[n][r] = 1;
	}
	if (n < r) {
		return memo[n][r] = 0;
	}
	return memo[n][r] = ncr(n-1,r-1) + ncr(n-1,r);
}

    class DrawingMarbles
        { 
        public: 
        double sameColor(vector <int> colors, int n) 
            { 
							int t = 0;
							fi(colors.size())
								t += colors[i];

							memset(done, 0, sizeof(done));

							long double ret = 0.0;
							fi(colors.size()) {
								if (colors[i] < n) {
									continue;
								}
								ret += ncr(colors[i], n) / ncr(t, n);
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 13 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; double Arg2 = 1.0; verify_case(0, Arg2, sameColor(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = { 5, 7 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 1.0; verify_case(1, Arg2, sameColor(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = { 5, 6, 7 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 0.3006535947712418; verify_case(2, Arg2, sameColor(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = { 12, 2, 34, 13, 17 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 0.035028830818304504; verify_case(3, Arg2, sameColor(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        DrawingMarbles ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

