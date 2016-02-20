// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// CSS property names are typically all lowercase and written 
// in dash-separated notation, which means that each pair of 
// adjacent words is separated by a single dash.  For 
// example, "z-index", "padding-left", and "border-collapse" 
// are typical names.  However, if you use JavaScript to set 
// CSS style properties, you need to use camel notation, 
// where each word except the first starts with an uppercase 
// letter, and adjacent words are not separated. All other 
// letters are lowercase. For example, "z-index" would become 
// "zIndex" in camel notation.
// 
// 
// You are given a String cssPropertyName containing a 
// property name written in dash-separated notation.  Convert 
// cssPropertyName to camel notation and return the result.
// 
// 
// 
// DEFINITION
// Class:CssPropertyConverter
// Method:getCamelized
// Parameters:string
// Returns:string
// Method signature:string getCamelized(string cssPropertyName)
// 
// 
// CONSTRAINTS
// -cssPropertyName will contain between 1 and 50 characters, 
// inclusive.
// -cssPropertyName will contain only lowercase letters 
// ('a'-'z') and dashes ('-').
// -Each dash in cssPropertyName will be surrounded by two 
// letters.
// 
// 
// EXAMPLES
// 
// 0)
// "z-index"
// 
// Returns: "zIndex"
// 
// 
// 
// 1)
// "border-collapse"
// 
// Returns: "borderCollapse"
// 
// 
// 
// 2)
// "top-border-width"
// 
// Returns: "topBorderWidth"
// 
// 
// 
// END CUT HERE
#line 64 "CssPropertyConverter.cpp"
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

    class CssPropertyConverter
        { 
        public: 
        string getCamelized(string cssPropertyName) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "z-index"; string Arg1 = "zIndex"; verify_case(0, Arg1, getCamelized(Arg0)); }
	void test_case_1() { string Arg0 = "border-collapse"; string Arg1 = "borderCollapse"; verify_case(1, Arg1, getCamelized(Arg0)); }
	void test_case_2() { string Arg0 = "top-border-width"; string Arg1 = "topBorderWidth"; verify_case(2, Arg1, getCamelized(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CssPropertyConverter ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

