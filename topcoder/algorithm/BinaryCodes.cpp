// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Given a finite alphabet S, a binary code over this 
// alphabet S is a 
// function that maps each element of S to some (possibly 
// empty) string over the alphabet {0,1}.
// 
// 
// 
// An example of such a code for S={a,b,c,d} is the function 
// f defined by 
// f(a)=1, f(b)=1010, f(c)=01, f(d)=10101.
// 
// 
// 
// Any binary code can be naturally extended to encode 
// strings over the alphabet S
// simply by concatenating the codes of the string's letters, 
// in order.
// For example, using the code mentioned above we can encode 
// cac as f(cac)=01101.
// 
// 
// 
// A code is called ambiguous if there are two different 
// strings over S that have the same encoding.
// Obviously, in practice we want to avoid using an ambiguous 
// code.
// 
// 
// 
// A code is called really ambiguous if there are three 
// different strings over S that have the same encoding.
// For example, the code from the above example is really 
// ambiguous: the strings ba, acc, and d are all encoded to
// 10101.
// 
// 
// 
// You will be given a vector <string> code containing the 
// strings over {0,1} used to encode letters of some alphabet 
// S.
// Your method should check whether this code is really 
// ambiguous.
// If it is really ambiguous, find a shortest string over 
// {0,1} that is an encoding of (at least) three different 
// strings over S, and return its length. 
// If the given code is not really ambiguous, return -1.
// 
// 
// DEFINITION
// Class:BinaryCodes
// Method:ambiguous
// Parameters:vector <string>
// Returns:int
// Method signature:int ambiguous(vector <string> code)
// 
// 
// NOTES
// -Your method does not need to know the actual elements of 
// S, and the size of S is obviously equal to the number of 
// elements in code.
// 
// 
// CONSTRAINTS
// -code will contain between 2 and 30 elements, inclusive.
// -Each element of code will contain between 0 and 50 
// characters, inclusive.
// -Each element of code will only contain the characters '0' 
// (zero) and '1' (one).
// 
// 
// EXAMPLES
// 
// 0)
// {"1","1010","01","10101"}
// 
// Returns: 5
// 
// This is the example from the problem statement, and the 
// string 10101 is the shortest string that can be decoded in 
// three different ways.
// 
// 1)
// {"0","1"}
// 
// Returns: -1
// 
// This code is obviously not ambiguous.
// 
// 
// 2)
// {"0","11","11","11"}
// 
// Returns: 2
// 
// This is clearly a really ambiguous code, as there are 
// three different one letter strings over
// S that are encoded to 11.
// 
// 
// 3)
// {"0000","001","01001","01010","01011"}
// 
// Returns: -1
// 
// This code is a prefix code, i.e., no code word is a prefix 
// of another code word. If a code has this
// property, it is guaranteed that it is not ambiguous, but 
// the other direction is not true.
// 
// 
// 4)
// {"1","10","00"}
// 
// Returns: -1
// 
// This is not a prefix code, but it can easily be shown that 
// this code is not ambiguous.
// 
// 
// 5)
// {"","01101001001","111101011"}
// 
// Returns: 0
// 
// Having an empty code word is a great way how to design a 
// really ambiguous code.
// 
// 
// 6)
// {"00011011","000110","11","0001","1011","00","011011"}
// 
// Returns: 8
// 
// The shortest proof that this code is really ambiguous is 
// 00011011. Note that this string can in fact be decoded in 
// four different ways.
// 
// END CUT HERE
#line 143 "BinaryCodes.cpp"
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

    class BinaryCodes
        { 
        public: 
        int ambiguous(vector <string> code) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1","1010","01","10101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, ambiguous(Arg0)); }
	void test_case_1() { string Arr0[] = {"0","1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, ambiguous(Arg0)); }
	void test_case_2() { string Arr0[] = {"0","11","11","11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, ambiguous(Arg0)); }
	void test_case_3() { string Arr0[] = {"0000","001","01001","01010","01011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, ambiguous(Arg0)); }
	void test_case_4() { string Arr0[] = {"1","10","00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, ambiguous(Arg0)); }
	void test_case_5() { string Arr0[] = {"","01101001001","111101011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(5, Arg1, ambiguous(Arg0)); }
	void test_case_6() { string Arr0[] = {"00011011","000110","11","0001","1011","00","011011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(6, Arg1, ambiguous(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BinaryCodes ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

