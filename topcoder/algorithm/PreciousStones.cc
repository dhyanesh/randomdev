// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Dr. Agnew and Dr. Austin have acquired a bag of stones, 
// each containing some amount of silver and gold.
// Dr. Agnew is only interested in the silver contained in 
// the stones, while
// Dr. Austin is only interested in the gold.
// Using their sophisticated instruments, they have measured 
// the value of the silver and gold in each stone.
// They want to divide the stones between them, cutting some 
// if necessary,
// in such a way that they each get the same value of the 
// element they are interested in,
// and that that value is as high as possible.
// 
// 
// 
// Given the value of silver and gold in each stone,
// determine the highest value that both Dr. Agnew and Dr. 
// Austin can receive of the element they want.
// Assume that each element is distributed uniformly within 
// each stone,
// so that if they cut a stone in two parts, each part will 
// have the same ratio of elements as did the whole stone.
// Between them they must take all of the stones, without 
// throwing any out.
// 
// 
// 
// The value of the precious elements in each stone will be 
// given as two vector <int>s, silver and gold,
// where silver[i] and gold[i] give the value of the silver 
// and gold, respectively, in stone i.
// 
// 
// DEFINITION
// Class:PreciousStones
// Method:value
// Parameters:vector <int>, vector <int>
// Returns:double
// Method signature:double value(vector <int> silver, vector 
// <int> gold)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative 
// or absolute value of 1e-9.
// 
// 
// CONSTRAINTS
// -silver and gold will each contain between 1 and 50 
// elements, inclusive.
// -silver and gold will contain the same number of elements.
// -Each element of silver and gold will be between 0 and 
// 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// { 10, 6 }
// { 3, 10 }
// 
// Returns: 10.0
// 
// If Dr. Agnew takes the first stone and Dr. Austin takes 
// the second, they can each get a value of 10.
// 
// 1)
// { 30 }
// { 15 }
// 
// Returns: 10.0
// 
// They cut the stone into pieces of size 1/3 and 2/3.  Dr. 
// Agnew takes the smaller piece (value = 30*1/3 = 10) and 
// Dr. Austin takes the larger piece (value = 15*2/3 = 10).
// 
// 2)
// { 0, 0 }
// { 10, 11 }
// 
// Returns: 0.0
// 
// There is no silver.  The only way for each person to get 
// an equal value is for Dr. Agnew to take both stones.
// 
// 3)
// { 3, 5, 4 }
// { 3, 5, 4 }
// 
// Returns: 6.0
// 
// There are multiple ways for each doctor to get a value of 
// 6.  One way is for both of them to take half of each stone.
// 
// 4)
// { 1, 2, 3 }
// { 2, 2, 2 }
// 
// Returns: 3.5
// 
// 
// 
// 5)
// { 11, 9, 13, 10 }
// 
// { 8, 14, 17, 21 }
// 
// Returns: 28.304347826086957
// 
// 
// 
// END CUT HERE
#line 117 "PreciousStones.cc"
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

    class PreciousStones
        { 
        public: 
        double value(vector <int> silver, vector <int> gold) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 10, 6 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 10.0; verify_case(0, Arg2, value(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = { 30 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 15 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 10.0; verify_case(1, Arg2, value(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = { 0, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 10, 11 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(2, Arg2, value(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = { 3, 5, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 5, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 6.0; verify_case(3, Arg2, value(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = { 1, 2, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.5; verify_case(4, Arg2, value(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = { 11, 9, 13, 10 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 8, 14, 17, 21 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 28.304347826086957; verify_case(5, Arg2, value(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PreciousStones ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

