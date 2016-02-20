// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// We have a box that consists of (sizeX x sizeY x sizeZ) = N 
// unit cubes.
// These cubes have coordinates ranging from (1,1,1) to 
// (sizeX,sizeY,sizeZ).
// 
// 
// 
// We want to number the unit cubes, using integers from 1 to 
// N. We will do this algorithmically.
// 
// 
// 
// We will call a box "1-dimensional (1D)" if at least two of 
// its dimensions are 1, "2-dimensional (2D)" if exactly one 
// of its
// dimensions is 1, and "3-dimensional (3D)" otherwise.
// 
// 
// 
// The algorithm used to number a 1-dimensional box is 
// simple: order the cubes according to the sums of
// their coordinates (in ascending order), and number them in 
// this order.
// 
// 
// 
// To number a 2-dimensional box, we follow this algorithm:
// 
// If X size is greater than 1, consider all cubes with both 
// Y and Z coordinates minimal, number them as a 1D box, and 
// throw them away.
// If we still have a 2D box, if Y size is greater than 1, 
// consider all cubes with both X and Z coordinates minimal, 
// number them as a 1D box, and throw them away.
// If we still have a 2D box, if Z size is greater than 1, 
// consider all cubes with both X and Y coordinates minimal, 
// number them as a 1D box, and throw them away.
// Recursively number the rest of the box.
// 
// 
// 
// 
// For example, a 4x5x1 box filled using this algorithm looks 
// as follows:
// 
// 
// 
// z=1
//    x:1  2  3  4
//  y:+--+--+--+--+
//   1| 1| 2| 3| 4|
//    +--+--+--+--+
//   2| 5| 9|10|11|
//    +--+--+--+--+
//   3| 6|12|15|16|
//    +--+--+--+--+
//   4| 7|13|17|19|
//    +--+--+--+--+
//   5| 8|14|18|20|
//    +--+--+--+--+
// 
// 
// 
// To number a 3-dimensional box, we follow this algorithm:
// 
// Consider all cubes with the Z coordinate minimal, number 
// them as a 2D box, and throw them away.
// If we still have a 3D box, consider all cubes with the Y 
// coordinate minimal, number them as a 2D box, and throw 
// them away.
// If we still have a 3D box, consider all cubes with the X 
// coordinate minimal, number them as a 2D box, and throw 
// them away.
// Recursively number the rest of the box.
// 
// 
// 
// 
// For example, a 4x3x3 box filled using this algorithm looks 
// as follows:
// 
// 
// 
// z=1
//    x:1  2  3  4
//  y:+--+--+--+--+
//   1| 1| 2| 3| 4|
//    +--+--+--+--+
//   2| 5| 7| 8| 9|
//    +--+--+--+--+
//   3| 6|10|11|12|
//    +--+--+--+--+
// 
// z=2
//    x:1  2  3  4
//  y:+--+--+--+--+
//   1|13|14|15|16|
//    +--+--+--+--+
//   2|21|25|26|27|
//    +--+--+--+--+
//   3|22|28|29|30|
//    +--+--+--+--+
// 
// z=3
//    x:1  2  3  4
//  y:+--+--+--+--+
//   1|17|18|19|20|
//    +--+--+--+--+
//   2|23|31|32|33|
//    +--+--+--+--+
//   3|24|34|35|36|
//    +--+--+--+--+
// 
// 
// 
// You will be given the box dimensions sizeX, sizeY, and 
// sizeZ, and the coordinates of a single cube (cubeX,cubeY,
// cubeZ). Write a method that will compute the number 
// assigned to the cube at the given coordinates,
// when using the algorithm described above.
// 
// 
// DEFINITION
// Class:BoxFilling
// Method:getNumber
// Parameters:int, int, int, int, int, int
// Returns:long long
// Method signature:long long getNumber(int sizeX, int sizeY, 
// int sizeZ, int cubeX, int cubeY, int cubeZ)
// 
// 
// NOTES
// -Note that the box described by sizeX, sizeY, and sizeZ is 
// not necessarily a 3D box.
// 
// 
// CONSTRAINTS
// -sizeX, sizeY and sizeZ will be between 1 and 109, 
// inclusive.
// -The volume of the box will not exceed 1018.
// -cubeX will be between 1 and sizeX, inclusive.
// -cubeY will be between 1 and sizeY, inclusive.
// -cubeZ will be between 1 and sizeZ, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 4
// 5
// 1
// 2
// 4
// 1
// 
// Returns: 13
// 
// This is the box from the first example in the problem 
// statement.
// 
// 1)
// 4
// 3
// 3
// 2
// 2
// 2
// 
// Returns: 25
// 
// This is the box from the second example in the problem 
// statement.
// 
// 2)
// 4
// 3
// 3
// 4
// 2
// 1
// 
// Returns: 9
// 
// Same box, different cube coordinates.
// 
// 3)
// 2
// 2
// 2
// 1
// 1
// 1
// 
// Returns: 1
// 
// 
// 
// 4)
// 43633
// 35453
// 34533
// 2344
// 32442
// 34221
// 
// Returns: 9416237809215
// 
// 
// 
// 5)
// 3
// 1
// 10
// 3
// 1
// 2
// 
// Returns: 14
// 
// 
// 
// 6)
// 4
// 2
// 4
// 3
// 2
// 3
// 
// Returns: 28
// 
// 
// 
// END CUT HERE
#line 239 "BoxFilling.cc"
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
typedef long long ll;

    class BoxFilling
        { 
        public: 
        long long getNumber(ll sx, ll sy, ll sz, ll cx, ll cy, ll cz) 
            { 
              if (sx == 1 && sy == 1) {
                return cz;
              }
              if (sz == 1 && sy == 1) {
                return cx;
              }
              if (sz == 1 && sx == 1) {
                return cy;
              }

              if (sx == 1) {
                return (cz - 1) * sy + cy;
              }
              if (sy == 1) {
                return (cz - 1) * sx + cx;
              }
              if (sz == 1) {
                return (cy - 1) * sx + cx;
              }

              ll ret = (cz - 1) * sx * sy;

              ret += (cy - 1) * sx;

              ret += cx;

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 5; int Arg2 = 1; int Arg3 = 2; int Arg4 = 4; int Arg5 = 1; long long Arg6 = 13LL; verify_case(0, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 2; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 25LL; verify_case(1, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 4; int Arg4 = 2; int Arg5 = 1; long long Arg6 = 9LL; verify_case(2, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; long long Arg6 = 1LL; verify_case(3, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 43633; int Arg1 = 35453; int Arg2 = 34533; int Arg3 = 2344; int Arg4 = 32442; int Arg5 = 34221; long long Arg6 = 9416237809215LL; verify_case(4, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 10; int Arg3 = 3; int Arg4 = 1; int Arg5 = 2; long long Arg6 = 14LL; verify_case(5, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_6() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 4; int Arg3 = 3; int Arg4 = 2; int Arg5 = 3; long long Arg6 = 28LL; verify_case(6, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BoxFilling ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

