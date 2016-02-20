// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Given a positive integer N with at least two digits, we 
// can define magic(N) as follows:
// Write N as a string of decimal digits. Now, for each two 
// consecutive digits, compute their difference
// (a non-negative number less than ten), and write it down. 
// In this way you'll obtain a new number,
// possibly with leading zeroes. Drop unnecessary leading 
// zeroes if there are any.
// 
// 
// 
// For example, magic(5913)=482, magic(1198)=081=81, and magic
// (666)=00=0.
// 
// 
// 
// For any number N the sequence: N, magic(N), magic(magic
// (N)), ... will sooner or later terminate with a single-
// digit number.
// This final value is called the magic fingerprint of N.
// 
// 
// 
// For example, for N=5913 we get the sequence: 5913, 482, 
// 46, 2. Therefore the magic fingerprint of 5913 is 2.
// 
// 
// 
// There are not too many numbers with the magic fingerprint 
// seven (7). These numbers are considered lucky.
// 
// 
// 
// Write a method that will compute the count of lucky 
// numbers between A and B, inclusive.
// 
// 
// DEFINITION
// Class:MagicFingerprint
// Method:countLuckyNumbers
// Parameters:int, int
// Returns:int
// Method signature:int countLuckyNumbers(int A, int B)
// 
// 
// CONSTRAINTS
// -B will be between 1 and 1,000,000,000, inclusive.
// -A will be between 1 and B, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 9
// 
// Returns: 1
// 
// The only single-digit lucky number is, of course, the 
// lucky number seven.
// 
// 1)
// 1
// 100
// 
// Returns: 6
// 
// There are five two-digit lucky numbers: 18, 29, 70, 81, 
// and 92.
// 
// 2)
// 1198
// 1198
// 
// Returns: 1
// 
// The number 1198 is lucky. The corresponding sequence is: 
// 1198, 81, 7.
// 
// 3)
// 1223
// 1299
// 
// Returns: 0
// 
// This range contains no lucky numbers.
// 
// 4)
// 999999930
// 1000000000
// 
// Returns: 2
// 
// The two lucky numbers in this range are 999,999,980 and 
// 999,999,992.
// 
// 5)
// 100000
// 1000000000
// 
// Returns: 159720
// 
// The largest output is obviously not much larger.
// 
// END CUT HERE
#line 110 "MagicFingerprint.cc"
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

    class MagicFingerprint
        { 
        public: 
        int countLuckyNumbers(int A, int B) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 9; int Arg2 = 1; verify_case(0, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 6; verify_case(1, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1198; int Arg1 = 1198; int Arg2 = 1; verify_case(2, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1223; int Arg1 = 1299; int Arg2 = 0; verify_case(3, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 999999930; int Arg1 = 1000000000; int Arg2 = 2; verify_case(4, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 100000; int Arg1 = 1000000000; int Arg2 = 159720; verify_case(5, Arg2, countLuckyNumbers(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MagicFingerprint ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

