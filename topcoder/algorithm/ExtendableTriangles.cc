// BEGIN CUT HERE
// PROBLEM STATEMENT
// Consider a rectangular grid of points on a plane with N 
// rows and M columns. Each of the points is colored in one 
// of three possible colors: red, green or blue. If we take 
// any three distinct points (even those lying on the same 
// straight line) and join them by line segments, we'll 
// obtain a triangle (possibly degenerate). Such a triangle 
// is called beautiful if all its vertices have distinct 
// colors.
// A beautiful triangle A is called extendable if there 
// exists a beautiful triangle B such that A and B have two 
// common vertices and the area of B is strictly greater than 
// the area of A. Note that the area of a degenerate triangle 
// is equal to 0.
// You will be given a string grid, containing exactly N 
// elements, representing rows of the grid, from top to 
// bottom. Each element of grid will contain exactly M 
// characters, representing colors of points in the 
// corresponding row, from left to right ('R' for red, 'G' 
// for green and 'B' for blue). Return the number of distinct 
// beautiful extendable triangles that can be formed from 
// points on the given grid. Two triangles are considered 
// distinct if their sets of vertices are distinct.
// 
// DEFINITION
// Class:ExtendableTriangles
// Method:getCount
// Parameters:vector <string>
// Returns:int
// Method signature:int getCount(vector <string> grid)
// 
// 
// CONSTRAINTS
// -grid will contain between 1 and 50 elements, inclusive.
// -Each element of grid will contain between 1 and 50 
// characters, inclusive.
// -All elements of grid will contain the same number of 
// characters.
// -Each element of grid will contain only characters 'R', 
// 'G' and 'B'.
// 
// 
// EXAMPLES
// 
// 0)
// {"RGB"}
// 
// Returns: 0
// 
// There's only one degenerate triangle and it's not 
// extendable.
// 
// 1)
// {"RGB",
//  "RGB"}
// 
// Returns: 6
// 
// There are 8 beautiful triangles and 6 of them are 
// extendable. These triangles are listed below ('X' means 
// triangle vertex):
// 
// XXX  ...  XX.  ..X  .XX  X..
// ...  XXX  ..X  XX.  X..  .XX
// 
// 
// 2)
// {"RRRRRRRR",
//  "GGGGBBBB",
//  "RRRRRRRR"}
// 
// Returns: 240
// 
// There are 256 beatiful triangles. The 16 of them which 
// contain the leftmost green and the rightmost blue points 
// are not extendable. Therefore the answer is 256 - 16 = 240.
// 
// 3)
// {"RBRBRBRB",
//  "BRBRBRBR",
//  "RBRBRBRB",
//  "BRBRBRBR",
//  "RRRRRRRR",
//  "BBBBBBBB",
//  "RRRRBBBB",
//  "BBBBRRRR"}
// 
// Returns: 0
// 
// There are no beautiful triangles because there are no 
// green points.
// 
// 4)
// {"RGB",
//  "RBG",
//  "GRB",
//  "GBR",
//  "BRG",
//  "BGR"}
// 
// Returns: 208
// 
// 
// 
// END CUT HERE
#line 108 "ExtendableTriangles.cc"
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

    class ExtendableTriangles
        { 
        public: 
        int getCount(vector <string> grid) 
            { 
              
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"RGB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { string Arr0[] = {"RGB",
 "RGB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { string Arr0[] = {"RRRRRRRR",
 "GGGGBBBB",
 "RRRRRRRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 240; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { string Arr0[] = {"RBRBRBRB",
 "BRBRBRBR",
 "RBRBRBRB",
 "BRBRBRBR",
 "RRRRRRRR",
 "BBBBBBBB",
 "RRRRBBBB",
 "BBBBRRRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { string Arr0[] = {"RGB",
 "RBG",
 "GRB",
 "GBR",
 "BRG",
 "BGR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 208; verify_case(4, Arg1, getCount(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ExtendableTriangles ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

