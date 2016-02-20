// BEGIN CUT HERE
// PROBLEM STATEMENT
// The King of Elbonia lives in a palace that is width meters 
// by length meters. Since he makes his subjects live in mud, 
// he is not very popular. He wants the palace partitioned so 
// that visitors have to walk a long way to reach him. His 
// security advisors have settled on a spiral. A visitor 
// enters the palace at the South-West corner and starts 
// walking East. Every time the visitor reaches an outer wall 
// or his own path, he turns left. The corridors in the 
// spiral are 1 meter wide. The diagram below shows an 
// example of a spiral path: the visitor moves from a (the 
// South-West corner) through the alphabet to x, the throne.
// 
// nmlkji
// oxwvuh
// pqrstg
// abcdef
// 
// The King wants to have his throne correctly placed before 
// all the partitioning is done, so he needs to know where 
// the spiral will end. Write a class SpiralRoute with a 
// method thronePosition that returns two integers, 
// indicating the coordinates of the throne. The South-West 
// corner is (0, 0), the South-East corner is (width - 1, 0) 
// and the North-East corner is (width - 1, length - 1).
// 
// 
// DEFINITION
// Class:SpiralRoute
// Method:thronePosition
// Parameters:int, int
// Returns:vector <int>
// Method signature:vector <int> thronePosition(int width, 
// int length)
// 
// 
// CONSTRAINTS
// -width and length will both be between 1 and 5000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 6
// 4
// 
// Returns: {1, 2 }
// 
// This is the example above.
// 
// 1)
// 6
// 5
// 
// Returns: {3, 2 }
// 
// 
// 
// 2)
// 1
// 11
// 
// Returns: {0, 10 }
// 
// 
// 
// 3)
// 12
// 50
// 
// Returns: {5, 6 }
// 
// 
// 
// 4)
// 5000
// 5000
// 
// Returns: {2499, 2500 }
// 
// 
// 
// END CUT HERE
#line 87 "SpiralRoute.cpp"
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

int minx,miny,maxx,maxy;

bool inb(int x, int y) {
	return x >= minx && y >= miny && x < maxx && y < maxy;
}

int dx[] = { 1, 0 , -1, 0 };
int dy[] = { 0 , 1 , 0, -1};

void update(int x, int y, int d) {
	if (d==1) {
		miny = y;
	}
	if (d == 2) {
		maxx = x + 1;
	}
	if (d == 3) 
		maxy = y + 1;
	if (d==0)
		minx = x;
}

    class SpiralRoute
        { 
        public: 
        vector <int> thronePosition(int w, int l) 
            { 
							int cx = 0;
							int cy = 0;

							int n = w * l - 1;

							minx = 0; miny = 0;
							maxx = w; maxy = l;

							int d = 0;
							while (n) {
								int nx = cx + dx[d];
								int ny = cy + dy[d];
								if (inb(nx,ny)) {
									cx = nx;
									cy = ny;
								} else {
									d  = (d + 1) % 4;
									cx += dx[d];
									cy += dy[d];
									update(cx,cy, d);
								}
								--n;
							}

							VI ret(2);
							ret[0] = cx;
							ret[1] = cy;
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 6; int Arg1 = 4; int Arr2[] = {1, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, thronePosition(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arg1 = 5; int Arr2[] = {3, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, thronePosition(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 11; int Arr2[] = {0, 10 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, thronePosition(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 12; int Arg1 = 50; int Arr2[] = {5, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, thronePosition(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5000; int Arg1 = 5000; int Arr2[] = {2499, 2500 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, thronePosition(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SpiralRoute ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

