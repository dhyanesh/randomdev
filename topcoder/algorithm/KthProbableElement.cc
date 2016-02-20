// BEGIN CUT HERE
// PROBLEM STATEMENT
// M integers are randomly independently chosen from the 
// interval lowerBound...upperBound, inclusive.  Return the 
// probability that the K-th smallest element of the 
// generated set is equal to N.  K=1 refers to the smallest 
// element, K=2 refers to the second smallest element, and so 
// on.
// 
// 
// DEFINITION
// Class:KthProbableElement
// Method:probability
// Parameters:int, int, int, int, int
// Returns:double
// Method signature:double probability(int M, int lowerBound, 
// int upperBound, int N, int K)
// 
// 
// NOTES
// -The returned value must have an absolute or relative 
// error less than 1e-9.
// 
// 
// CONSTRAINTS
// -M will be between 1 and 100, inclusive.
// -lowerBound will be between 1 and 1000, inclusive.
// -upperBound will be between lowerBound and 1000, inclusive.
// -N will be between lowerBound and upperBound, inclusive.
// -K will be between 1 and M, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 1
// 10
// 3
// 1
// 
// Returns: 0.1
// 
// The probability that the only chosen number will be equal 
// to 3 is 0.1.
// 
// 1)
// 3
// 1
// 2
// 2
// 2
// 
// Returns: 0.5
// 
// There are 8 ways to choose 3 numbers from the interval 1..2:
// Numbers | 2nd smallest element
//  1 1 1  |  1
//  1 1 2  |  1
//  1 2 1  |  1
//  1 2 2  |  2
//  2 1 1  |  1
//  2 1 2  |  2
//  2 2 1  |  2
//  2 2 2  |  2
// Exactly 4 of the ways have the 2nd smallest element equal 
// to 2.
// 
// 2)
// 3
// 1
// 3
// 2
// 2
// 
// Returns: 0.48148148148148145
// 
// There are 27 ways to choose 3 numbers from the interval 1..
// 3, 13 of them have the 2nd smallest element equal to 2.
// 
// 3)
// 10
// 1
// 10
// 1
// 10
// 
// Returns: 1.0000000000000003E-10
// 
// Only one of 1010 ways to choose 10 numbers from the 
// interval 1..10 has 1 as the 10th smallest element.
// 
// 4)
// 4
// 61
// 65
// 62
// 3
// 
// Returns: 0.15200000000000002
// 
// 
// 
// END CUT HERE
#line 106 "KthProbableElement.cc"
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


    class KthProbableElement
        { 
        public: 
        double probability(int M, int L, int B, int N, int K) 
            { 
              long double p = (K-1) * logl(N-L) + (M-K) * logl(B-N) - M * logl(B-L+1);


              long double ret = powl(N-L+1,K-1) / powl(B-L+1,K-1) / powl(B-L+1,M-K) / powl(B-L+1,1);
               
              if (B-N+1 > 0)
                ret *= powl(B-N+1,M-K);
              return ret;
              return expl(p);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 3; int Arg4 = 1; double Arg5 = 0.1; verify_case(0, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 2; double Arg5 = 0.5; verify_case(1, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 2; int Arg4 = 2; double Arg5 = 0.48148148148148145; verify_case(2, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 10; int Arg3 = 1; int Arg4 = 10; double Arg5 = 1.0000000000000003E-10; verify_case(3, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 4; int Arg1 = 61; int Arg2 = 65; int Arg3 = 62; int Arg4 = 3; double Arg5 = 0.15200000000000002; verify_case(4, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        KthProbableElement ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

