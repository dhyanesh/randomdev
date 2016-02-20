// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
//        xxxxx...
//        ....xxxx
//        .x.....x
//        .xxxxxxx
// 
// Your are given a picture of a snake. Lowercase 'x' 
// characters indicate parts of the snake, and '.'
// characters represent
// empty areas. The snake consists of a sequence of 
// horizontal and vertical segments.
// Successive segments in the snake share an 'x', which is 
// considered to be in both segments.
// No two 'x's from different segments of the snake are 
// horizontally or vertically adjacent.
// 
// Given a vector <string> snake, return the length of the 
// longest segment
// in the snake.  The picture is formed using successive 
// elements of snake as successive
// rows in the picure.
// 
// 
// 
// DEFINITION
// Class:Snaky
// Method:longest
// Parameters:vector <string>
// Returns:int
// Method signature:int longest(vector <string> snake)
// 
// 
// CONSTRAINTS
// -snake contains between 1 and 50 elements, inclusive.
// -Each element of snake contains the same number of 
// characters.
// -Each element of snake contains between 1 and 50 
// characters, inclusive.
// -Each character in each element of snake is a period ('.') 
// or a lowercase 'x'.
// -If two 'x's are adjacent to each other in the picture, 
// they are in the same segment.
// -The picture shows just one connected snake, using at 
// least 2 'x's.
// 
// 
// EXAMPLES
// 
// 0)
// {"x.xxx.xxx",
//  "x.x.x.x.x",
//  "xxx.xxx.x"}
// 
// Returns: 3
// 
// 
//    This snake consists of 9 segments, each of length 3.
// 
// 
// 
// 1)
// {"xxxx..",
//  "...x..",
//  "...x..",
//  "......"}
// 
// Returns: 4
// 
//     One segment is length 4, the other is length 3.
// 
// 2)
// {"...x................",
//  "...x................",
//  "....................",
//  "...................."}
// 
// Returns: 2
// 
// 
// 
// END CUT HERE
#line 85 "Snaky.cpp"
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

    class Snaky
        { 
        public: 
        int longest(vector <string> snake) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"x.xxx.xxx",
 "x.x.x.x.x",
 "xxx.xxx.x"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, longest(Arg0)); }
	void test_case_1() { string Arr0[] = {"xxxx..",
 "...x..",
 "...x..",
 "......"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, longest(Arg0)); }
	void test_case_2() { string Arr0[] = {"...x................",
 "...x................",
 "....................",
 "...................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, longest(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Snaky ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

