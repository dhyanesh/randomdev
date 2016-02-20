// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given a vector <int> weight, a set of weight 
// values. You must choose the minimum number of weight 
// values from the set such that every element in weight is 
// measurable on a balance scale with the chosen weight 
// values. Weight X is measurable with a set Y of weight 
// values if and only if you can do the following.  You place 
// one weight with value X on either the left or right side 
// of the scale.  You then place some combination of weights 
// on the scale with values from the set Y so that the left 
// and right sides have the same total value. You may use 
// each value in Y zero or more times to achieve this.
// 
// For example, consider the set of weight values { 21, 9, 6 
// }.  You can choose the set { 9, 6 }, and every element in 
// the original set will be measurable with this set.  With 
// weight 21, you can do the following.  Place the one weight 
// of 21 on the left side of the scale. Then place one weight 
// of value 9 on the left side, and 5 weights of value 6 on 
// the right side, and the scale will be balanced. With 
// weights 9 and 6, you can simply place the weight on one 
// side and a weight of equal value on the opposite side to 
// balance the scale.
// 
// Return the minimum number of chosen weight values.
// 
// DEFINITION
// Class:BalanceScale
// Method:takeWeights
// Parameters:vector <int>
// Returns:int
// Method signature:int takeWeights(vector <int> weight)
// 
// 
// CONSTRAINTS
// -weight will contain between 1 and 50 elements, inclusive.
// -All elements of weight will be distinct.
// -Each element of weight will be between 1 and 10,000,000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// { 5, 4, 1, 8 }
// 
// Returns: 1
// 
// With weight value 1 we can measure all the other elements.
// 
// 1)
// { 2, 3, 8, 9 }
// 
// Returns: 2
// 
// We choose weight values 2 and 3. Measure 8 by placing the 
// weight of 8 on the left side, and 4 weights of value 2 on 
// the right side. Measure 9 by placing the weight of 9 on 
// the left side, and 3 weights of value 3 on the right side.
// 
// 2)
// { 60, 105, 490, 42 }
// 
// Returns: 4
// 
// We can choose all weight values from the set.
// 
// 3)
// { 15, 25, 9 }
// 
// Returns: 2
// 
// 
// 
// END CUT HERE
#line 78 "BalanceScale.cpp"
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

    class BalanceScale
        { 
        public: 
        int takeWeights(vector <int> weight) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 5, 4, 1, 8 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, takeWeights(Arg0)); }
	void test_case_1() { int Arr0[] = { 2, 3, 8, 9 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, takeWeights(Arg0)); }
	void test_case_2() { int Arr0[] = { 60, 105, 490, 42 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, takeWeights(Arg0)); }
	void test_case_3() { int Arr0[] = { 15, 25, 9 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, takeWeights(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BalanceScale ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

