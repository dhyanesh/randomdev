// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A skyline is the outline formed by a group of buildings 
// against the sky. A certain city has a beautiful skyline 
// that's visible to everybody as they approach it by car.  
// You have bought the rights to place an advertisement over 
// it, and you would like to do so while preserving the shape 
// of the city.  The skyline is formed by n buildings, all 
// with a width of 1 and each with a different height.  You 
// will place your ad on a rectangle of maximum area that is 
// fully contained within the interior of the skyline.
// 
// To keep the input small, it will be codified in the 
// following way.  You will be given a vector <int> h.  Use 
// the following pseudo-code on h to generate an array R.  
// The xth building has height R[x], which means its lower 
// left corner is at (x, 0) and its upper right corner is at 
// (x+1, R[x]).  The total width of the skyline is n.  All 
// array indices are 0-based:
// 
// input array: h
// output array: R (of size n)
// j := 0
// m := size of h
// for i := 0 to n-1
// 	R[i] := h[j]
// 	s := (j+1)%m
// 	h[j] := ( ( h[j] ^ h[s] ) + 13 ) % 835454957
// 	j := s
// 
// This code, along with the constraints, ensures that the 
// height of each building is between 0 and 835454956, 
// inclusive.  In the above code, % is the modulo operator 
// and ^ is the bitwise XOR binary operator.  See the notes 
// section for information on performing XOR in your 
// language.  Return the area of the rectangle on which you 
// will place your ad.
// 
// 
// DEFINITION
// Class:BuildingAdvertise
// Method:getMaxArea
// Parameters:vector <int>, int
// Returns:long long
// Method signature:long long getMaxArea(vector <int> h, int n)
// 
// 
// NOTES
// -The input is only coded for convenience.  The intended 
// solution does not rely on the way it is generated.
// -If x and y are ints, (x^y) represents the bitwise XOR 
// operation on them in C++, Java, C# and Python. In VB.Net 
// (x BitXor y) does it.
// -Note that the first elements of the input are exactly the 
// corresponding elements of h.
// 
// 
// CONSTRAINTS
// -h will contain between 1 and 50 elements, inclusive.
// -Each element of h will be between 0 and 835454956, 
// inclusive.
// -n will be between the number of elements in h and 100000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {3,6,5,6,2,4}
// 6
// 
// Returns: 15
// 
// 
// This is how the outline looks. The grayed area shows the 
// optimal way to place the advertisement.
// 
// 1)
// {5,0,7,0,2,6,2}
// 7
// 
// Returns: 7
// 
// Using building 2 entirely is the best choice.
// 
// 2)
// {1048589,2097165}
// 100000
// 
// Returns: 104858900000
// 
// The resulting array is: {1048589, 2097165, 3145741, 
// 1048589, 2097165, 3145741,..., 1048589, 2097165, 3145741, 
// 1048589}.
// 
// 3)
// {1,7,2,5,3,1}
// 6
// 
// Returns: 8
// 
// 
// 
// END CUT HERE
#line 107 "BuildingAdvertise.cpp"
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

int r[100005];
int t;
int arr[1005];

bool okay(int st, int en) {
	int val = r[st];
	int min = 1<<30;

	int sta = -1;
	int i;
	for(i=st;i<=en;++i) {
		min <?= r[i];
		if (i%t == 0 && i!=0) {
			sta = i;
			break;
		}
	}
	if (sta == -1) {
		return val<=min;
	}
	sta /= t;
	int end = en/t;
	for(i=sta;i<=end;++i)
		min<?=arr[i];


	for(i=end*t; i<=en;++i)
		min<?=r[i];

	return val<=min;
}

    class BuildingAdvertise
        { 
        public: 
        long long getMaxArea(vector <int> h, int n) 
            { 
            
// input array: h
// output array: R (of size n)
// j := 0
// m := size of h
// for i := 0 to n-1
// 	R[i] := h[j]
// 	s := (j+1)%m
// 	h[j] := ( ( h[j] ^ h[s] ) + 13 ) % 835454957
// 	j := s
// 

							int j = 0;
							int m = h.size();
							fi(n) {
								r[i] = h[j];
								int s = (j+1) %m;
								h[j]= ((h[j] ^h[s]) + 13) % 835454957;
								j = s;
							}

							 t = sqrt(n) + 1;


							memset(arr,0x7f,sizeof(arr));
							int min = 1<<30;
							j = 0;
							fi(n) {
								if (i%t==0 && i!=0) {
									arr[j++] =min;
									min = 1<<30;
								}
								min <?= r[i];
							}
							arr[j++] = min;
							int len = j;

							long long best = 0;
							fi(n) {
								int low = i;
								int high = n - 1;

								int ans1 = low;
								while (low < high) {
									 int mid = (low+high)/2;

									if (okay(i, mid)) {
										low = mid + 1;
										ans1 = mid;
									} else {
										high = mid - 1;
										ans1 = high;
									}
								}
								low = 0;
								high = i;
								int ans2 = low;
								while (low < high) {
									 int mid = (low+high)/2;

									if (okay(i, mid)) {
										high = mid - 1;
										ans2 = mid;
									} else {
										low = mid + 1;
										ans2 = high;
									}
								}

								best >?= (ans1 - ans2 + 1) * (long long)r[i];
							}

							return best;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,6,5,6,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; long long Arg2 = 15LL; verify_case(0, Arg2, getMaxArea(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {5,0,7,0,2,6,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; long long Arg2 = 7LL; verify_case(1, Arg2, getMaxArea(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1048589,2097165}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100000; long long Arg2 = 104858900000LL; verify_case(2, Arg2, getMaxArea(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,7,2,5,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; long long Arg2 = 8LL; verify_case(3, Arg2, getMaxArea(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BuildingAdvertise ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

