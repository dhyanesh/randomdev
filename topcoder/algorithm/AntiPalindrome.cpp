// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A string p is called anti-palindrome if p[i] doesn't equal 
// to p[n - i - 1] for each 0 <= i < (n-1)/2, where n is the 
// length of p. It means that each character (except the 
// middle in the case of a string of odd length) must be 
// different from its symmetric character. For example, "c", 
// "cpp", "java" are anti-palindrome, but "test", "pp" and 
// "weather" are not.
// 
// 
// You are given a string s. Rearrange its letters in such a 
// way that the resulting string is anti-palindrome. If there 
// are several solutions, return the one that comes earliest 
// alphabetically. If it is impossible to do it, return the 
// empty string.
// 
// 
// 
// DEFINITION
// Class:AntiPalindrome
// Method:rearrange
// Parameters:string
// Returns:string
// Method signature:string rearrange(string s)
// 
// 
// CONSTRAINTS
// -s will contain between 1 and 50 characters, inclusive.
// -s will contain only lowercase letters ('a'-'z').
// 
// 
// EXAMPLES
// 
// 0)
// "test"
// 
// Returns: "estt"
// 
// 
// 
// 1)
// "aabbcc"
// 
// Returns: "aabcbc"
// 
// 
// 
// 2)
// "reflectionnoitcelfer"
// 
// Returns: "cceeeeffiillnnoorrtt"
// 
// 
// 
// 3)
// "hello"
// 
// Returns: "ehllo"
// 
// 
// 
// 4)
// "www"
// 
// Returns: ""
// 
// 
// 
// END CUT HERE
#line 73 "AntiPalindrome.cpp"
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

    class AntiPalindrome
        { 
        public: 
        string rearrange(string s) 
            { 
							sort(s.begin(), s.end());

							int n = s.size();

							fi(n/2) {
								if (s[i] == s[n - i - 1]) {
									int st = n - i;
									bool f = false;
									for (; st<n; ++st) {
										if (s[st] != s[n-i-1]) {
											swap(s[st], s[n-i-1]);
											i = -1;
											f = true;
											break;
										}
									}
									if (!f) return "";
								}
							}

							return s;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "test"; string Arg1 = "estt"; verify_case(0, Arg1, rearrange(Arg0)); }
	void test_case_1() { string Arg0 = "aabbcc"; string Arg1 = "aabcbc"; verify_case(1, Arg1, rearrange(Arg0)); }
	void test_case_2() { string Arg0 = "reflectionnoitcelfer"; string Arg1 = "cceeeeffiillnnoorrtt"; verify_case(2, Arg1, rearrange(Arg0)); }
	void test_case_3() { string Arg0 = "hello"; string Arg1 = "ehllo"; verify_case(3, Arg1, rearrange(Arg0)); }
	void test_case_4() { string Arg0 = "www"; string Arg1 = ""; verify_case(4, Arg1, rearrange(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        AntiPalindrome ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

