// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A terrible meteorite storm has crashed into a large part 
// of your city. As a chief police officer, you are in charge 
// of closing down the perimeter of the damaged area to 
// prevent citizens from falling into a crater. Each 
// meteorite left a crater in the form of a circle. Several 
// craters can touch each other, intersect, or be inside one 
// another. You need to calculate the length of danger tape 
// needed to cover the perimeter of the union of all craters.
// 
// You will be given three vector <int>s, x, y and r where 
// the ith element of each contains the x and y coordinates 
// of the center and the length of the radius of each crater. 
// Return the length of the perimeter of the union of all 
// those circles. Note that even if an area is completely 
// surrounded by craters, its perimeter must be taken into 
// account. See example 2 for further clarification.
// 
// 
// DEFINITION
// Class:Meteorites
// Method:perimeter
// Parameters:vector <int>, vector <int>, vector <int>
// Returns:double
// Method signature:double perimeter(vector <int> x, vector 
// <int> y, vector <int> r)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative 
// or absolute value of 1e-9.
// 
// 
// CONSTRAINTS
// -x will contain between 1 and 50 elements, inclusive.
// -x, y and r will all contain the same number of elements.
// -Each element of x and y will be between -1000000 (-106) 
// and 1000000 (106), inclusive.
// -Each element of r will be between 1 and 1000000 (106), 
// inclusive.
// -No two craters will be equal (i.e., any two craters will 
// have different location and/or different size).
// 
// 
// EXAMPLES
// 
// 0)
// {0,10}
// {0,0}
// {6,7}
// 
// Returns: 63.72326520248748
// 
// 
// 
// 1)
// {-10,-10,-10,0,0,0,10,10,10}
// {-10,0,10,-10,0,10,-10,0,10}
// {7,7,7,7,7,7,7,7,7}
// 
// Returns: 135.3757009200326
// 
// 
// 
// 2)
// {-100,100,100,-100}
// {-100,-100,100,100}
// {110,110,110,110}
// 
// Returns: 2008.3301227325105
// 
// Even when the middle area is inaccesible from the outside 
// because it is surrounded by craters, its perimeter must be 
// included in the final result.
// 
// 3)
// {0,0,0,0}
// {0,0,0,0}
// {1,2,3,100000}
// 
// Returns: 628318.5307179586
// 
// Every crater is inside the big one.
// 
// END CUT HERE
#line 89 "Meteorites.cpp"
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

    class Meteorites
        { 
        public: 
        double perimeter(vector <int> x, vector <int> y, vector <int> r) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 63.72326520248748; verify_case(0, Arg3, perimeter(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {-10,-10,-10,0,0,0,10,10,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-10,0,10,-10,0,10,-10,0,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {7,7,7,7,7,7,7,7,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 135.3757009200326; verify_case(1, Arg3, perimeter(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {-100,100,100,-100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100,-100,100,100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {110,110,110,110}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 2008.3301227325105; verify_case(2, Arg3, perimeter(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,100000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 628318.5307179586; verify_case(3, Arg3, perimeter(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Meteorites ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

