// BEGIN CUT HERE
// PROBLEM STATEMENT
// John has two strings s and t of equal length.
// He can choose a set of positions (possibly empty) and 
// erase characters at these positions in both s and t.
// Then he writes down the concatenation of what remained of 
// the strings: first the letters we kept from s, in their 
// original order, then the letters we kept from t, again in 
// their original order.
// 
// 
// Return the lexicographically largest string John can get 
// at the end.
// 
// 
// DEFINITION
// Class:TheLargestString
// Method:find
// Parameters:string, string
// Returns:string
// Method signature:string find(string s, string t)
// 
// 
// NOTES
// -String A is lexicographically smaller than string B if 
// either A is a proper prefix of B, or if there is an 
// integer i such that the first i characters of A match the 
// first i characters of B, and character i+1 of A is smaller 
// than character i+1 of B.
// 
// 
// CONSTRAINTS
// -s will contain between 1 and 47 characters, inclusive.
// -s and t will contain the same number of characters.
// -s will contain only lowercase English characters ('a'-'z').
// -t will contain only lowercase English characters ('a'-'z').
// 
// 
// EXAMPLES
// 
// 0)
// "ab"
// "zy"
// 
// Returns: "by"
// 
// There are four options here:
// 
// Do not erase anything. The resulting string would be "abzy".
// Erase both first characters. The resulting string would be 
// "by".
// Erase both last characters. The resulting string would be 
// "az".
// Erase all characters. The resulting string would be empty.
// 
// Among all possible results "by" is the lexicographically 
// largest one.
// 
// 
// 1)
// "abacaba"
// "zzzaaaa"
// 
// Returns: "cbaaaa"
// 
// 
// 
// 2)
// "x"
// "x"
// 
// Returns: "xx"
// 
// 
// 
// 3)
// "abbabbabbababaaaabbababab"
// "bababbaabbbababbbbababaab"
// 
// Returns: "bbbbbbbbbbbbbbbbbbaaab"
// 
// 
// 
// END CUT HERE
#line 86 "TheLargestString.cc"
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

    class TheLargestString
        { 
        public:

          void get(string &s, string &t, int &start) {
            int mi = start;
            for (int i = start; i < s.size(); ++i) {
              if (s[i] > s[mi]) {
                mi = i;
              }
            }
            s.erase(s.begin() + start, s.begin() + mi);
            t.erase(t.begin() + start, t.begin() + mi);
            start = mi + 1 - (mi - start);
          }

        string find(string s, string t) {
          int start = 0;
          while (start < s.size()) {
            get(s, t, start);
          }
          fi(t.size() - 1) {
            if (t[i] < t[i + 1] && s[i] == s[i + 1]) {
              string ts = s;
              string tt = t;
              ts.erase(ts.begin() + i);
              tt.erase(tt.begin() + i);
              if (s + t < ts + tt) {
                s = ts;
                t = tt;
                --i;
              }
            }
          }
          return s + t;
        }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ab"; string Arg1 = "zy"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "abacaba"; string Arg1 = "zzzaaaa"; string Arg2 = "cbaaaa"; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "x"; string Arg1 = "x"; string Arg2 = "xx"; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "abbabbabbababaaaabbababab"; string Arg1 = "bababbaabbbababbbbababaab"; string Arg2 = "bbbbbbbbbbbbbbbbbbaaab"; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheLargestString ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

