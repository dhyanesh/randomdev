// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You will be given a vector <int> a and two ints lower and 
// upper.  Return the number of integers between lower and 
// upper, inclusive, that are multiples of all members of a.
// 
// 
// DEFINITION
// Class:CommonMultiples
// Method:countCommMult
// Parameters:vector <int>, int, int
// Returns:int
// Method signature:int countCommMult(vector <int> a, int 
// lower, int upper)
// 
// 
// CONSTRAINTS
// -a will contain between 1 and 50 elements, inclusive.
// -Each element of a will be between 1 and 100, inclusive.
// -upper will be between 1 and 2000000000 (2*109), inclusive.
// -lower will be between 1 and upper, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1,2,3}
// 5
// 15
// 
// Returns: 2
// 
// The only numbers between 5 and 15 that are multiples of 1, 
// 2 and 3 are 6 and 12.
// 
// 1)
// {1,2,4,8,16,32,64}
// 128
// 128
// 
// Returns: 1
// 
// 128 is a multiple of all smaller powers of 2.
// 
// 2)
// {2,3,5,7,11,13,17,19,23,29,31,37,41,43,49}
// 1
// 2000000000
// 
// Returns: 0
// 
// 
// 
// 3)
// {1,1,1}
// 1
// 2000000000
// 
// Returns: 2000000000
// 
// 
// 
// END CUT HERE
#line 66 "CommonMultiples.cpp"
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

long long gcd(long long a,long long b) {
	if (a<b) return gcd(b,a);
	if (a%b==0) return b;
	return gcd(b, a%b);
}

long long lcm(long long a,long long b) {
	return a/gcd(a,b)*b;
}

long long get(long long no, long long lim) {
	return lim / no;
}

    class CommonMultiples
        { 
        public: 
        int countCommMult(vector <int> a, int lower, int upper) 
            { 
							long long lc = 1;
							fi(a.size()) {
								if (lc > upper) return 0;
								lc = lcm(lc, a[i]);
							}

							return get(lc, upper) - get(lc, lower - 1);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 15; int Arg3 = 2; verify_case(0, Arg3, countCommMult(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,2,4,8,16,32,64}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 128; int Arg2 = 128; int Arg3 = 1; verify_case(1, Arg3, countCommMult(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,49}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2000000000; int Arg3 = 0; verify_case(2, Arg3, countCommMult(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2000000000; int Arg3 = 2000000000; verify_case(3, Arg3, countCommMult(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CommonMultiples ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

