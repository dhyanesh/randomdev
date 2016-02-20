// BEGIN CUT HERE
// PROBLEM STATEMENT
// Return the smallest positive integer that has exactly k 
// divisors. If this number is greater than 1018, return -1 
// instead.
// 
// DEFINITION
// Class:NumberOfDivisors
// Method:smallestNumber
// Parameters:int
// Returns:long long
// Method signature:long long smallestNumber(int k)
// 
// 
// CONSTRAINTS
// -k will be between 1 and 50000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 
// Returns: 1
// 
// 
// 
// 1)
// 2
// 
// Returns: 2
// 
// 
// 
// 2)
// 6
// 
// Returns: 12
// 
// The 6 divisors of 12 are: 1, 2, 3, 4, 6, 12.
// 
// END CUT HERE
#line 44 "NumberOfDivisors.cpp"
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

int div(ll no) {
	int ret = 0;
	ll s = sqrt(no);
	if ((s+1) * (s+1) == no) {
		s++;
	}
	f(i,1,s+1) {
		if (no%i == 0) ret+=2;
	}
	ret -= (s *s == no);
	return ret;
}

    class NumberOfDivisors
        { 
        public: 
        long long smallestNumber(int k) 
            { 
							ll n = 1;
							while (1) {
								if (div(n) == k)  {
									cout << n << endl;
									break;
								}
								++n;
							}

							return n;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 12; long long Arg1 = 1LL; verify_case(0, Arg1, smallestNumber(Arg0)); }
	void test_case_1() { int Arg0 = 14; long long Arg1 = 2LL; verify_case(1, Arg1, smallestNumber(Arg0)); }
	void test_case_2() { int Arg0 = 16; long long Arg1 = 12LL; verify_case(2, Arg1, smallestNumber(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        NumberOfDivisors ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

