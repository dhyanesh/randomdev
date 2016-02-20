// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are given a string number containing the digits of a 
// phone number.  To help you memorize the number, you want 
// to divide it into groups of contiguous digits.  Each group 
// must contain exactly 2 or 3 digits.  There are three kinds 
// of groups:
// 
// Excellent: A group that contains only the same digits.  
// For example, 000 or 77.
// Good: A group of 3 digits, 2 of which are the same.  For 
// example, 030, 229 or 166.
// Usual: A group in which all the digits are distinct.  For 
// example, 123 or 90.
// 
// 
// 
// The quality of a group assignment is defined as 2 * 
// (number of excellent groups) + (number of good groups).  
// Divide the number into groups such that the quality is 
// maximized, and return the result as a string, where each 
// pair of consecutive groups is separated by a dash ('-').  
// If there are multiple ways to do this, return the one 
// among them that results in the lexicographically earliest 
// string.
// 
// 
// DEFINITION
// Class:PhoneNumbers
// Method:bestNumber
// Parameters:string
// Returns:string
// Method signature:string bestNumber(string number)
// 
// 
// NOTES
// -A String A comes before a String B lexicographically if A 
// is a proper prefix of B, or if A has a smaller character 
// at the first position where the strings differ. When 
// comparing the characters, refer to the following list of 
// characters in ascending order: '-', '0', '1', ..., '9'.
// 
// 
// CONSTRAINTS
// -number will contain between 2 and 50 characters, inclusive.
// -Each character in number will be a digit ('0'-'9').
// 
// 
// EXAMPLES
// 
// 0)
// "5088638"
// 
// Returns: "50-88-638"
// 
// There are three possible ways to divide this number into 
// groups: 508-86-38 (quality 0), 50-886-38 (quality 1) and 
// 50-88-638 (quality 2). The last option is the best one.
// 
// 1)
// "0123456789"
// 
// Returns: "01-23-45-67-89"
// 
// No matter how you divide this number, the quality will be 
// 0.  Choose the division that comes earliest 
// lexicographically.
// 
// 2)
// "09"
// 
// Returns: "09"
// 
// With a 2-digit phone number, there is only one choice.
// 
// 3)
// "54545454545454545454"
// 
// Returns: "54-545-454-545-454-545-454"
// 
// The best way to divide this number is to create six 3-
// digit good groups and one 2-digit usual group.  Put the 2-
// digit group at the beginning to achieve the 
// lexicographically earliest result.
// 
// 4)
// "00110001011100010111"
// 
// Returns: "00-11-00-010-11-10-00-101-11"
// 
// 
// 
// END CUT HERE
#line 96 "PhoneNumbers.cc"
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

string st;

string memo[55][55];
int best[55][55];
bool done[55][55];

int score(int sta, int en) {
  int no = en - sta;

  if (no < 2) return 0;

  if (no == 2) {
    if (st[sta] == st[sta+1]) return 2;
    return 0;
  }

  if (st[sta] == st[sta+1] && st[sta] == st[sta+2]) return 2;

  if (st[sta] == st[sta+1]) return 1;
  if (st[sta+1] == st[sta+2]) return 1;
  if (st[sta] == st[sta+2]) return 1;

  return 0;
}

int go(int pos, int last) {
  if (pos == st.size()) {
    if (pos - last < 2) return -1LL<<20;

    int sc = score(last , pos);

    best[pos][last] = sc;
    memo[pos][last] = st.substr(last, pos - last);
    return sc;
  }

  if (pos > st.size()) {
    return -1LL<<20;
  }

  if (done[pos][last]) return best[pos][last];

  done[pos][last] = true;
  best[pos][last] = -1LL<<20;

  int sc1 = -1LL<<20;
  string s1;
  if (pos - last >= 2) {
    sc1 = score(last, pos);
    sc1 += go(pos + 2, pos);

    s1 = st.substr(last, pos - last);
    if (s1.empty()) s1 = memo[pos+2][pos];
    else
      if (!memo[pos + 2][pos].empty()) s1 += "-" + memo[pos+2][pos];

    best[pos][last] = sc1;
    memo[pos][last] = s1;
  }

  if (pos - last <= 2) {
    int sc2 = go(pos + 1, last);
    string s2;
    if (!memo[pos + 1][last].empty()) s2 = memo[pos+1][last];

    if (sc1 == sc2) {
      best[pos][last] = sc1;
      if (s1 < s2) memo[pos][last] = s1;
      else memo[pos][last] = s2;
    } else if (sc1 > sc2) {
      best[pos][last] = sc1;
      memo[pos][last] = s1;
    } else {
      best[pos][last] = sc2;
      memo[pos][last] = s2;
    }
  }

  return best[pos][last];
}

    class PhoneNumbers
        { 
        public: 
        string bestNumber(string number) 
            { 
              fi(55)
                fj(55)
                memo[i][j].clear();
              memset(best, 0xff, sizeof(best));
              memset(done, 0, sizeof(done));
              st = number;
              go(0, 0);

              return memo[0][0];
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "6322"; string Arg1 = "50-88-638"; verify_case(0, Arg1, bestNumber(Arg0)); }
	void test_case_1() { string Arg0 = "23"; string Arg1 = "01-23-45-67-89"; verify_case(1, Arg1, bestNumber(Arg0)); }
	void test_case_2() { string Arg0 = "09"; string Arg1 = "09"; verify_case(2, Arg1, bestNumber(Arg0)); }
	void test_case_3() { string Arg0 = "54545454545454545454"; string Arg1 = "54-545-454-545-454-545-454"; verify_case(3, Arg1, bestNumber(Arg0)); }
	void test_case_4() { string Arg0 = "00110001011100010111"; string Arg1 = "00-11-00-010-11-10-00-101-11"; verify_case(4, Arg1, bestNumber(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PhoneNumbers ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

