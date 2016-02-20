// BEGIN CUT HERE
// PROBLEM STATEMENT
// Given a set of points, choose the maximal number of them 
// that can be used to form a spiral.
// 
// A spiral is formed as follows:
// 
// 1. Start at point (0, 0).
// 2. Draw a line segment from the current point to one of 
// the given points (x, y). (x, y) is now the new current 
// point.
// 3. Repeat step 2 as many times as possible while obeying 
// the following rules:
// 
// The spiral must not intersect itself. This means that no 
// two line segments in the spiral can have any common points 
// (except the common endpoints of neighboring segments).
// Each point must not be used more than once.
// When going from each line segment to the next, you must 
// turn counterclockwise and go forward. The angle you turn 
// must be greater than or equal to 0, and strictly less than 
// 180 degrees.
// The ray that originates from the second to last point and 
// goes through the last point must not intersect any of the 
// other line segments in the spiral.
// 
// These three spirals do not satisfy the first, second and 
// third rules:
// 
// 
// 
// 
// These two do not satisfy the fourth rule:
// 
// 
// 
// You are given a vector <string> points, each element of 
// which represents a single point whose coordinates are 
// given as "X Y" (quotes for clarity). Return the maximal 
// number of points that can be used to form a single spiral.
// 
// DEFINITION
// Class:SpiralConstruction
// Method:longestSpiral
// Parameters:vector <string>
// Returns:int
// Method signature:int longestSpiral(vector <string> points)
// 
// 
// CONSTRAINTS
// -points will contain between 1 and 15 elements, inclusive.
// -Each element of points will be formatted as "X Y" (quotes 
// for clarity), where X and Y are integers with no extra 
// leading zeros.
// -Each X and Y will be between -1000 and 1000, inclusive.
// -All elements in points will be distinct.
// -There will be no "0 0" in points.
// 
// 
// EXAMPLES
// 
// 0)
// {"0 1", "1 0"}
// 
// Returns: 2
// 
// (0,0) -> (1,0) -> (0,1) is a valid spiral.
// 
// 1)
// {"1 1", "2 2", "-1 -1"}
// 
// Returns: 2
// 
// (0,0) -> (1,1) -> (2,2) is the longest valid spiral.
// Note that there is a turn by 0 degrees.
// 
// 2)
// {"0 1", "1 1", "0 2"}
// 
// Returns: 2
// 
// You can't form a valid spiral using all three points.
// 
// 3)
// {"0 1", "-1 0", "0 -1", "1 2", "2 -2", "-2 1", "1 0", "-1 
// -1", "1 3", "-3 -2"}
// 
// Returns: 10
// 
// 
// 
// END CUT HERE
#line 94 "SpiralConstruction.cpp"
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

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

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

template<class T>
vector<T> toksT(string inp,string delim)   
{   
  VS temp = toks(inp,delim);   
  vector<T> ret;   
  for(int i=0;i<temp.size();i++)   
    ret.push_back(fromString<T>(temp[i]));   
  return ret;   
}   

VVI toksvvi(vector <string> inp,string delim)   
{   
  VVI ret;   
  for(int i=0;i<inp.size();i++)   
    ret.push_back(toksT<int>(inp[i],delim));   
  return ret;   
}   


VVI pts;
int n;

int memo[17][17][1<<17];

bool ok (int cu , int ppr ,int pr , int st) {
	int a1 = pts[pr][0] - pts[ppr][0];
	int a2 = pts[pr][1] - pts[ppr][1];
	int b1 = pts[cu][0] - pts[pr][0];
	int b2 = pts[cu][1] - pts[pr][1];

	int t = a1 * b1 + b1 * b2;
	if (t > 0) return false;

	int p = a1 * b2 - a2 * b1;
	if ( p < 0 ) return false;

//	long double tp1 = sqrtl(a1*a1 + a2*a2);
//	long double tp2 = sqrtl(b1*b1 + b2*b2);

//	long double ang = t / tp1 / tp2;

	return true;
}

int go(int ppr, int pr, int st) {
	if (st == (1<<n) - 1) {
		return 0;
	}
	if (memo[ppr][pr][st] >= 0) return memo[ppr][pr][st];

	int ret = 0;
	fi(pts.size()) {
		if (st & (1<<i)) continue;

		if (ok(i ,ppr, pr ,st)) {
			ret >?= go(pr, i, st | (1<<i)) + 1;
		}
	}

	return memo[ppr][pr][st] = ret;
}

    class SpiralConstruction
        { 
        public: 
        int longestSpiral(vector <string> points) 
            { 
							pts = toksvvi(points, " ");
							VI p(2);
							p[0] = 0;
							p[1] = 0;
							pts.push_back(p);
							n = pts.size();

							memset(memo, 0xff, sizeof(memo));

							return go(n-1, n - 1, 1<<(n-1));
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 1", "1 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, longestSpiral(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 1", "2 2", "-1 -1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, longestSpiral(Arg0)); }
	void test_case_2() { string Arr0[] = {"0 1", "1 1", "0 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, longestSpiral(Arg0)); }
	void test_case_3() { string Arr0[] = {"0 1", "-1 0", "0 -1", "1 2", "2 -2", "-2 1", "1 0", "-1 -1", "1 3", "-3 -2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, longestSpiral(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SpiralConstruction ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

