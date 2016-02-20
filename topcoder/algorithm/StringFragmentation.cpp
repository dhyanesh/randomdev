// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given a string containing a list of words 
// separated by single spaces, with no leading or trailing 
// spaces. You have a panel on which you would like to write 
// these words, in order, possibly over multiple lines. The 
// words must go from left to right within each line, and the 
// lines must go from top to bottom. Each line must contain 
// only complete words, and each pair of adjacent words in a 
// line must be separated by a single space. There must be no 
// leading or trailing spaces.
// 
// You must write the words in a font size greater than 7. In 
// a font of size N, the height of each letter is 2*N pixels, 
// and the width of each character (letters and spaces) is 
// N+2 pixels. There is no space between adjacent characters 
// and adjacent lines.
// 
// You are given a string text containing the words you must 
// write. The dimensions of the panel in pixels are given in 
// the ints width and height. You are not allowed to rotate 
// the panel. Return the largest integer font size strictly 
// greater than 7 that you can use to write the words on the 
// panel, or -1 if it is impossible.
// 
// DEFINITION
// Class:StringFragmentation
// Method:largestFontSize
// Parameters:string, int, int
// Returns:int
// Method signature:int largestFontSize(string text, int 
// width, int height)
// 
// 
// NOTES
// -If you start a new line between two words, then the space 
// that separated them in the input doesn't get written to 
// the panel.
// 
// 
// CONSTRAINTS
// -text will contain between 1 and 50 characters, inclusive.
// -Each character in text will be an uppercase letter 
// ('A'-'Z') or a space (' ').
// -text must be a list of words separated by single spaces, 
// with no leading or trailing spaces, where each word is one 
// or more uppercase letters.
// -width and height will be between 1 and 10000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// "ONE TWO THREE FOUR FIVE"
// 150
// 40
// 
// Returns: 9
// 
// With a font size of 9, we can write "ONE TWO THREE" on the 
// first line and "FOUR FIVE" on the second line.
// The width of the first line is 13 characters * (9+2) 
// pixels = 143 pixels.
// The width of the second line is 9 characters * (9+2) 
// pixels = 99 pixels.
// The total height is 2 lines * (2*9) pixels = 36 pixels.
// The total size is therefore 143 x 36 pixels, which fits 
// inside the 150 x 40 pixel panel.
// If you used a font size of 10, it would be 156 x 40 
// pixels, which would not fit.
// 
// 1)
// "ONE TWO THREE FOUR FIVE"
// 150
// 60
// 
// Returns: 10
// 
// Now we can write it in a font size of 10 by separating the 
// text into three lines: "ONE TWO", "THREE", "FOUR FIVE".
// 
// 2)
// "ONE TWO THREE FOUR FIVE"
// 150
// 10000
// 
// Returns: 28
// 
// If you write each word on a separate line, you can use a 
// font size of 28. The widest line would be "THREE", which 
// is 150 pixels wide.
// 
// 3)
// "ONE TWO THREE FOUR FIVE"
// 10000
// 10000
// 
// Returns: 1250
// 
// 
// 
// 4)
// "ONE TWO THREE FOUR FIVE"
// 50
// 50
// 
// Returns: -1
// 
// 
// 
// 5)
// "A"
// 9
// 14
// 
// Returns: -1
// 
// Note that font size must be strictly greater than 7.
// 
// END CUT HERE
#line 122 "StringFragmentation.cpp"
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

VS toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  VS ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
    }   
  free(ch);   
  return ret;   
}   

VS words;

bool can(int f, int w, int h) {
	int l = h / (2 * f);
	int c = w / (f + 2);

	fi(words.size()) {
		c -= words[i].size();
		if (l <= 0) return false;
		if (c < 0) {
			c = w / (f + 2);
			--l;
			--i;
			continue;
		}
		--c;
	}

	return true;
}


    class StringFragmentation
        { 
        public: 
        int largestFontSize(string text, int w, int h) 
            { 
							words = toks(text, " ");
							int ret = -1;
							f(i,8,h/2+1) {
								if (!can(i, w, h)) {
									return ret;
								}
								ret = i;
							}
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ONE TWO THREE FOUR FIVE"; int Arg1 = 150; int Arg2 = 40; int Arg3 = 9; verify_case(0, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "ONE TWO THREE FOUR FIVE"; int Arg1 = 150; int Arg2 = 60; int Arg3 = 10; verify_case(1, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "ONE TWO THREE FOUR FIVE"; int Arg1 = 150; int Arg2 = 10000; int Arg3 = 28; verify_case(2, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "ONE TWO THREE FOUR FIVE"; int Arg1 = 10000; int Arg2 = 10000; int Arg3 = 1250; verify_case(3, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "ONE TWO THREE FOUR FIVE"; int Arg1 = 50; int Arg2 = 50; int Arg3 = -1; verify_case(4, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "A"; int Arg1 = 9; int Arg2 = 14; int Arg3 = -1; verify_case(5, Arg3, largestFontSize(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        StringFragmentation ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

