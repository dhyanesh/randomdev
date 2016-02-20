// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given n distinct straight lines in the plane. The 
// i-th line is specified by two distinct lattice points (x1
// [i], y1[i]) and (x2[i], y2[i]) that lie on it. These lines 
// divide the plane into regions, and your task is to compute 
// and return the number of finite regions among them. By a 
// finite region we mean a convex polygon bounded by the 
// given lines, with no points belonging to any of the given 
// lines in its interior.
// 
// DEFINITION
// Class:PlaneDivision
// Method:howManyFiniteParts
// Parameters:vector <int>, vector <int>, vector <int>, 
// vector <int>
// Returns:int
// Method signature:int howManyFiniteParts(vector <int> x1, 
// vector <int> y1, vector <int> x2, vector <int> y2)
// 
// 
// NOTES
// -By a lattice point (x, y) we mean a point on the 
// Cartesian plane with integer coordinates x and y.
// -Two points are said to be distinct if either their x-
// coordinates or y-coordinates differ.
// 
// 
// CONSTRAINTS
// -x1, y1, x2 and y2 will contain the same number of elements.
// -x1, y1, x2 and y2 will contain between 1 and 50 elements, 
// inclusive.
// -All the elements of x1, y1, x2 and y2 will be between 
// -10000 and 10000, inclusive.
// -(x1[i], y1[i]) and (x2[i], y2[i]) will be distinct for 
// all i (i.e., every two points defining a given line will 
// be distinct).
// -All the lines defined by (x1[i], y1[i]) and (x2[i], y2
// [i]) will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// {0}
// {0}
// {1}
// {1}
// 
// Returns: 0
// 
// A single line divides the plane into two infinite regions.
// 
// 1)
// {0, 1, 2}
// {0, 1, -1}
// {1, 2, 0}
// {1, -1, 0}
// 
// Returns: 1
// 
// The three lines are the sidelines of a triangle which is 
// the only finite region in this case.
// 
// 2)
// {-10000, -9999, 10000, -9999, 0, 500, -500}
// {-9999, 10000, 9999, -10000, 0, 0, 0}
// {-10000, 9999, 10000, 9999, 0, 500, -500}
// {9999, 10000, -9999, -10000, 1, -1, -2}
// 
// Returns: 4
// 
// The only finite regions are the 4 big rectangles.
// 
// 3)
// {0, 0, 0, 0, 0, 0, 0, 0, 0}
// {0, 0, 0, 0, 0, 0, 0, 0, 0}
// {1, 1, 1, 1, 1, 1, 1, 1, 1}
// {1, 2, 3, 4, 5, 6, 7, 8, 9}
// 
// Returns: 0
// 
// All the lines pass through the origin.
// 
// 4)
// {-1, -1, -1, -1, 1, 3, -3}
// {-1, -2, 0, 0, 10000, 1, -5}
// {1, 1, 1, -1, 1, -3, 3}
// {1, 0, 2, -10000, 0, -2, 4}
// 
// Returns: 7
// 
// 1 parallelogramm and 6 triangles are the only finite 
// regions in this case.
// 
// 5)
// {-100, -100, -100, -100, -100}
// {-100, -99, -98, -97, -96}
// {100, 100, 100, 100, 100}
// {99, 100, 101, 102, 103}
// 
// Returns: 0
// 
// 5 parallel lines do not produce any finite regions.
// 
// 6)
// {-100, -100, -100, -100, -100, 1}
// {-100, -99, -98, -97, -96, -1}
// {100, 100, 100, 100, 100, -2}
// {99, 100, 101, 102, 103, 2}
// 
// Returns: 0
// 
// A configuration of 5 parallel lines and a single line 
// crossing all of them again yields no finite regions.
// 
// END CUT HERE
#line 119 "PlaneDivision.cpp"
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

    class PlaneDivision
        { 
        public: 
        int howManyFiniteParts(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(0, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, -1, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {-10000, -9999, 10000, -9999, 0, 500, -500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-9999, 10000, 9999, -10000, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-10000, 9999, 10000, 9999, 0, 500, -500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {9999, 10000, -9999, -10000, 1, -1, -2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 4; verify_case(2, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(3, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {-1, -1, -1, -1, 1, 3, -3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, -2, 0, 0, 10000, 1, -5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, -1, 1, -3, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 0, 2, -10000, 0, -2, 4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 7; verify_case(4, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {-100, -100, -100, -100, -100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100, -99, -98, -97, -96}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100, 100, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {99, 100, 101, 102, 103}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(5, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = {-100, -100, -100, -100, -100, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100, -99, -98, -97, -96, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100, 100, 100, -2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {99, 100, 101, 102, 103, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(6, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PlaneDivision ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

