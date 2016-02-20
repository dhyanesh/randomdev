// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 	There is a rectangular table divided into r rows and c 
// columns, for a total of r * c fields.  
// 	The rows are numbered 1 to r, from bottom to top, and the 
// columns are numbered 1 to c, from left to right.  
// 	All coordinates in this problem will be given as (row, 
// column).
// 
// 
// 
// 	You are given vector <int>s fieldrow and fieldcol 
// containing a list of special fields in the 
// 	table, where (fieldrow[i], fieldcol[i]) are the 
// coordinates of the i-th field.  For each number n, 
// 	where 0 <= n <= the number of elements in fieldrow, you 
// must count the number of different paths from field (1, 1) 
// 	to field (r, c) that contain exactly n special fields.  
// These paths are called paths of length n.
// 
// 
// 
// 	There are two rules you must follow.  First, you are only 
// allowed to make moves that are straight up or to the 
// right.  
// 	In other words, from each field (row, column), you can 
// only move to field (row+1, column) or field (row, 
// column+1).  
// 	Second, in each path, all the special fields must appear 
// in the same order that they appear in the input.  
// 	In other words, if the path contains field a = (fieldrow
// [idxa], fieldcol[idxa]) and 
// 	field b = (fieldrow[idxb], fieldcol[idxb]), and a appears 
// before b in the path, then idxa must be less than idxb.
// 
// 
// 
// 	Return a vector <int> containing exactly k+1 elements, 
// where k is the number of elements in fieldrow.  
// 	The i-th element (0-indexed) must be the number of 
// different paths of length i modulo 1000007.
// 
// 
// 
// DEFINITION
// Class:CountPaths
// Method:difPaths
// Parameters:int, int, vector <int>, vector <int>
// Returns:vector <int>
// Method signature:vector <int> difPaths(int r, int c, 
// vector <int> fieldrow, vector <int> fieldcol)
// 
// 
// CONSTRAINTS
// -r and c will each be between 1 and 50, inclusive.
// -fieldrow will contain between 0 and 50 elements, inclusive.
// -fieldcol and fieldrow will contain same number of elements.
// -Each element of fieldrow will be between 1 and r, 
// inclusive.
// -Each element of fieldcol will be between 1 and c, 
// inclusive.
// -For all i and j, where i < j, the pairs (fieldrow[i], 
// fieldcol[i]) and (fieldrow[j], fieldcol[j]) will be 
// different.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// 3
// {2, 3}
// {2, 2}
// 
// Returns: {1, 3, 2 }
// 
// Path of length 0:
// (1, 1) -> (1, 2) -> (1, 3) -> (2, 3) -> (3, 3)
// 
// Paths of length 1:
// (1, 1) -> (2, 1) -> (2, 2) -> (2, 3) -> (3, 3)
// (1, 1) -> (1, 2) -> (2, 2) -> (2, 3) -> (3, 3)
// (1, 1) -> (2, 1) -> (3, 1) -> (3, 2) -> (3, 3)
// 
// Paths of length 2:
// (1, 1) -> (2, 1) -> (2, 2) -> (3, 2) -> (3, 3)
// (1, 1) -> (1, 2) -> (2, 2) -> (3, 2) -> (3, 3)
// 
// 
// 1)
// 6
// 4
// {5, 3}
// {3, 2}
// 
// Returns: {14, 24, 0 }
// 
// 2)
// 5
// 5
// {1, 2, 3}
// {3, 4, 5}
// 
// Returns: {42, 14, 10, 4 }
// 
// 3)
// 35
// 37
// {3, 28, 28, 27, 27, 5, 15, 23, 21, 3, 8, 25, 34, 31, 33, 
// 35, 13, 34}
// {12, 34, 3, 9, 34, 3, 18, 17, 26, 5, 23, 14, 20, 7, 3, 20, 
// 19, 23}
// 
// Returns: {830519, 709835, 755976, 219563, 868547, 0, 0, 0, 
// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
// 
// 4)
// 50
// 50
// {50, 1}
// {50, 1}
// 
// Returns: {0, 0, 0 }
// 
// There is no path that passes through (50, 50) before (1, 1).
// 
// END CUT HERE
#line 130 "CountPaths.cc"
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

          int memo[55][55][55][55];
    class CountPaths
        { 
        public: 
          VI fr;
          VI fc;
          int r,c;


          int go(int x, int y, int p, int left) {
            if (x > r || y > c) return 0;

            if (p >= fr.size() && left !=0 ) return 0;
            int &ret = memo[x][y][p][left];

            if (ret >= 0) {
              return ret;
            }

            f(i,0,p) {
              if (x == fr[i] && y == fc[i]){
                return ret = 0;
              }
            }
            f(i,p,fr.size()) {
              if (x == fr[i] && y == fc[i]){
                p = i + 1;
                --left;
                break;
              }
            }


            if (x == r && y == c) {
              if (left == 0)
                return 1;
              return 0;
            }


            ret = go(x + 1, y, p, left);
            ret += go(x , y + 1, p, left);
            ret %= 1000007;

            return ret;
          }

        vector <int> difPaths(int R, int C, vector <int> fieldrow, vector <int> fieldcol) 
            { 
              fr = fieldrow;
              fc = fieldcol;
              r = R;
              c = C;

              memset(memo, 0xff, sizeof(memo));

              VI ret(fr.size() + 1);
              fi(ret.size()) {
                ret[i] = go(1, 1, 0, i);
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arr2[] = {2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 3, 2 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, difPaths(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 6; int Arg1 = 4; int Arr2[] = {5, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {14, 24, 0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, difPaths(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 4, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {42, 14, 10, 4 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, difPaths(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 35; int Arg1 = 37; int Arr2[] = {3, 28, 28, 27, 27, 5, 15, 23, 21, 3, 8, 25, 34, 31, 33, 35, 13, 34}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {12, 34, 3, 9, 34, 3, 18, 17, 26, 5, 23, 14, 20, 7, 3, 20, 19, 23}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {830519, 709835, 755976, 219563, 868547, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(3, Arg4, difPaths(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 50; int Arg1 = 50; int Arr2[] = {50, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {50, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0, 0, 0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(4, Arg4, difPaths(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CountPaths ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

