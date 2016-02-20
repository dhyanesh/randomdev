// BEGIN CUT HERE
// PROBLEM STATEMENT
// Little Bonnie and her friends were dismayed to learn that 
// their parents were reading all of their private 
// communications.  They decided to invent a new language 
// that would allow them to talk freely.  What they finally 
// came up with was a language where sentences are built 
// using a special method. 
// 
// 
// All the valid words that can be used in the new language 
// are given in the vector <string> validWords.  A sentence 
// is a concatenation (with no spaces) of a sequence of valid 
// words.  Each valid word can appear 0 or more times in the 
// sentence.  What makes the language special is that each 
// word can be transformed by rearranging its letters before 
// being used.  The cost to transform a word is defined as 
// the number of character positions where the original word 
// and the transformed word differ.  For example, "abc" can 
// be transformed to "abc" with a cost of 0, to "acb", "cba" 
// or "bac" with a cost of 2, and to "bca" or "cab" with a 
// cost of 3. 
// 
// 
// Although several different sequences of valid words can 
// produce the same sentence in this language, only the 
// sequence with the least total transformation cost carries 
// the meaning of the sentence.  The advantage of the new 
// language is that the parents can no longer understand what 
// the kids are saying.  The disadvantage is that the kids 
// themselves also do not understand.  They need your help. 
// 
// 
// Given a string sentence, return the total cost of 
// transformation of the sequence of valid words which 
// carries the meaning of the sentence, or -1 if no such 
// sequence exists.
// 
// DEFINITION
// Class:SentenceDecomposition
// Method:decompose
// Parameters:string, vector <string>
// Returns:int
// Method signature:int decompose(string sentence, vector 
// <string> validWords)
// 
// 
// NOTES
// -If a word is used multiple times in a sentence, each 
// occurrence can be transformed differently.
// 
// 
// CONSTRAINTS
// -sentence will contain between 1 and 50 lowercase letters 
// ('a'-'z'), inclusive.
// -validWords will contain between 1 and 50 elements, 
// inclusive.
// -Each element of validWords will contain between 1 and 50 
// lowercase letters ('a'-'z'), inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// "neotowheret"
// {"one", "two", "three", "there"}
// 
// Returns: 8
// 
// The following transformations can be made:
// 
// "one" -> "neo" with a cost of 3 
// "two" -> "tow" with a cost of 2 
// "three" -> "heret" with a cost of 3 
// "there" -> "heret" with a cost of 5 
// 
// So the sequence {"one", "two", "three"} is the one 
// carrying the meaning of "neotowheret". Its total 
// transformation cost is 3 + 2 + 3 = 8.
// 
// 1)
// "abba"
// {"ab", "ac", "ad"}
// 
// Returns: 2
// 
// The word "ab" is used twice, and each time, it is 
// transformed differently.
// 
// 2)
// "thisismeaningless"
// {"this", "is", "meaningful"}
// 
// Returns: -1
// 
// 
// 
// 3)
// "ommwreehisymkiml"
// {"we", "were", "here", "my", "is", "mom", "here", "si", 
// "milk", "where", "si"}
// 
// Returns: 10
// 
// 
// 
// 4)
// "ogodtsneeencs"
// {"go", "good", "do", "sentences", "tense", "scen"}
// 
// Returns: 8
// 
// 
// 
// 5)
// "sepawaterords"
// {"separate","words"}
// 
// Returns: -1
// 
// You are only allowed to rearrange letters within words, 
// and not in the entire sentence.
// 
// END CUT HERE
#line 126 "SentenceDecomposition.cc"
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

VS v;
map<string,string> st;
string s;
int memo[100];

bool isvalid(int pos, int ind) {
  if (pos + v[ind].size() > s.size()) {
    return false;
  }
  string t = s.substr(pos, v[ind].size());
  sort(t.begin(), t.end());
  return st[v[ind]] == t;
}

int go(int pos) {
  if (pos > s.size()) {
    return 1<<30;
  }
  if (pos == s.size()) {
    return 0;
  }
  if (memo[pos] >= 0) return memo[pos];

  memo[pos] = 1<<30;
  int &ret = memo[pos];
  fi(v.size()) {
    if (!isvalid(pos, i)) {
      continue;
    }
    int c = 0;
    fj(v[i].size()) {
      if (s[pos+j] != v[i][j])
        c++;
    }

    ret <?= go(pos + v[i].size()) + c;
  }

  return ret;
}

    class SentenceDecomposition
        { 
        public: 
        int decompose(string sentence, vector <string> vw) 
            { 
              s = sentence;
              v = vw;
              st.clear();
              fi(v.size()) {
                string &t = st[v[i]];
                t = v[i];
                sort(t.begin(), t.end());
              }
              memset(memo, 0xff, sizeof(memo));
              int t = go(0);
              if (t == 1<<30) return -1;
              return t;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "neotowheret"; string Arr1[] = {"one", "two", "three", "there"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(0, Arg2, decompose(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "abba"; string Arr1[] = {"ab", "ac", "ad"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, decompose(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "thisismeaningless"; string Arr1[] = {"this", "is", "meaningful"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, decompose(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ommwreehisymkiml"; string Arr1[] = {"we", "were", "here", "my", "is", "mom", "here", "si", "milk", "where", "si"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(3, Arg2, decompose(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "ogodtsneeencs"; string Arr1[] = {"go", "good", "do", "sentences", "tense", "scen"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(4, Arg2, decompose(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "sepawaterords"; string Arr1[] = {"separate","words"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(5, Arg2, decompose(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SentenceDecomposition ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

