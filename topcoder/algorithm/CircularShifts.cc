// BEGIN CUT HERE
// PROBLEM STATEMENT
// You have two lists of numbers, X and Y, each containing 
// exactly N elements.  You can optionally apply any number 
// of circular shifts to each list.  A circular shift means 
// removing the last element from a list and re-inserting it 
// before the first element.  For example, {1, 2, 3} would 
// become {3, 1, 2}, and {3, 1, 2} would become {2, 3, 1}.  
// After you apply any circular shifts, the final score is 
// calculated as:
// 
// X[0]*Y[0] + X[1]*Y[1] + ... + X[N-1]*Y[N-1]
// 
// You are given ints Z0, A, B and M. Generate a list Z of 
// length 2*N, using the following recursive definition:
// 
// Z[0] = Z0 MOD M 
// Z[i] = (Z[i-1]*A+B) MOD M (note that Z[i-1]*A+B may 
// overflow a 32-bit integer) 
// 
// Then, generate lists X and Y, each of length N, using the 
// following definitions:
// 
// X[i] = Z[i] MOD 100 
// Y[i] = Z[i+N] MOD 100 
// 
// Return the maximal final score you can achieve.
// 
// 
// 
// 
// DEFINITION
// Class:CircularShifts
// Method:maxScore
// Parameters:int, int, int, int, int
// Returns:int
// Method signature:int maxScore(int N, int Z0, int A, int B, 
// int M)
// 
// 
// NOTES
// -In the statement, "A MOD B" represents the remainder of 
// integer division of A by B. For example, 14 MOD 5 = 4 and 
// 20 MOD 4 = 0.
// -The author's solution does not depend on any properties 
// of the pseudorandom generator. It would solve any input of 
// allowed size within the given limits.
// 
// 
// CONSTRAINTS
// -N will be between 1 and 60,000, inclusive. 
// -Z0, A and B will each be between 0 and 1,000,000,000, 
// inclusive. 
// -M will be between 1 and 1,000,000,000, inclusive. 
// 
// 
// EXAMPLES
// 
// 0)
// 5
// 1
// 1
// 0
// 13
// 
// Returns: 5
// 
// Both lists contain only ones, so no matter how many shifts 
// you perform, the score will always be 5.
// 
// 1)
// 4
// 1
// 1
// 1
// 20
// 
// Returns: 70
// 
// The lists are {1, 2, 3, 4} and {5, 6, 7, 8}.  The maximal 
// score is achieved by not making any shifts.
// 
// 2)
// 10
// 23
// 11
// 51
// 4322
// 
// Returns: 28886
// 
// The lists are (23, 4, 95, 20, 17, 94, 63, 44, 13, 96) and 
// (87, 54, 13, 18, 61, 24, 17, 94, 53, 2).
// 
// 3)
// 1000
// 3252
// 3458736
// 233421
// 111111111
// 
// Returns: 2585408
// 
// 
// 
// 4)
// 141
// 96478
// 24834
// 74860
// 92112
// 
// Returns: 419992
// 
// END CUT HERE
#line 117 "CircularShifts.cc"
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

    class CircularShifts
        { 
        public: 
        int maxScore(int N, long long Z0, long long A, long long B, int M) { 
          VI x(N),y(N);

          VI z(2*N);
          z[0 ] = Z0 % M;
          f(i,1,2*N) {
            z[i] = (z[i-1]*A+B)%M
          }
          fi(N){ 
            x[i] = z[i] % 100;
            y[i] = z[i + N] % 100;
          }

          
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; int Arg4 = 13; int Arg5 = 5; verify_case(0, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 20; int Arg5 = 70; verify_case(1, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 23; int Arg2 = 11; int Arg3 = 51; int Arg4 = 4322; int Arg5 = 28886; verify_case(2, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 3252; int Arg2 = 3458736; int Arg3 = 233421; int Arg4 = 111111111; int Arg5 = 2585408; verify_case(3, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 141; int Arg1 = 96478; int Arg2 = 24834; int Arg3 = 74860; int Arg4 = 92112; int Arg5 = 419992; verify_case(4, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CircularShifts ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

