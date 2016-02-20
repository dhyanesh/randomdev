// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A polyline is a sequence of line segments such that each 
// segment starts at the point where the previous segment 
// ended.
// 
// 
// 
// If two polylines have a common point, we say that they 
// belong to the same picture.
// The common point does not have to be an endpoint of a line 
// segment.
// 
// 
// 
// Your method will be given a vector <string> polylines. 
// Concatenate the elements of polylines to get a space-
// separated list of polyline descriptions.
// Each polyline description consists of one or more point 
// descriptions, separated by single dashes ('-'). Each point 
// is described by its two non-negative integer coordinates,
// separated by a comma (',').
// 
// 
// 
// Return the number of pictures in the union of all the 
// given polylines.
// 
// 
// DEFINITION
// Class:PolylineUnion
// Method:countComponents
// Parameters:vector <string>
// Returns:int
// Method signature:int countComponents(vector <string> 
// polylines)
// 
// 
// NOTES
// -The point sequence that defines a polyline may contain 
// the same point more than once, and even consecutive points 
// are allowed to be equal.
// -A polyline may be just a single point.
// 
// 
// CONSTRAINTS
// -polylines will have the format described in the problem 
// statement.
// -polylines will contain between 1 and 50 elements, 
// inclusive.
// -Each of the elements in polylines will contain between 0 
// and 50 characters, inclusive.
// -Each coordinate of each point specified in polylines will 
// be between 0 and 10000, inclusive.
// -The point coordinates in polylines will not contain 
// unnecessary leading zeros.
// 
// 
// EXAMPLES
// 
// 0)
// {"0,0-10,10 0,10-10,0"}
// 
// Returns: 1
// 
// Two intersecting line segments form a single picture.
// 
// 
// 1)
// {"0,0-10,5 5,0-15,5-10,10-5,5"}
// 
// Returns: 2
// 
// Two non-intersecting polylines.
// 
// 
// 2)
// {"1","3,0-5,5 4,0-4,20"}
// 
// Returns: 2
// 
// Note that you first have to concatenate the elements of 
// polylines and only then parse the resulting string.
// 
// 3)
// {"10,0-10,1-9,2-9,3-8,4 ","8,2-9,2-10,3 ","12,2-11,2-9,1"}
// 
// Returns: 1
// 
// Together, these three polylines form a single picture. 
// From a graph theoretical point of view, this picture can 
// be seen as a tree with 11 vertices. (Ten of them are the 
// given points and one is the intersection of 10,1-9,2 and 
// 11,2-9,1.)
// 
// 
// 4)
// {"0,0-10,0-0,0 20,0-8,0-20,0"}
// 
// Returns: 1
// 
// The union of these two polylines is the line segment 0,0-
// 20,0.
// 
// 5)
// {"1,1 2,2 3,3 4,4 3,3-4,4"}
// 
// Returns: 3
// 
// A single point is a special case of a polyline.
// 
// 6)
// {"10,10-20,10 20,10-15,18 15,18-10,10"}
// 
// Returns: 1
// 
// A triangle.
// 
// 7)
// {"1,1 1,1"}
// 
// Returns: 1
// 
// 
// 
// END CUT HERE
#line 129 "PolylineUnion.cpp"
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

struct point {
	int x,y;
};

long double slope(const point &a, const point &b, bool *vert) {
	if (b.y == a.y) {
		*vert = true;
		return 0.0;
	}
	*vert = false;
	return (b.x - a.x) / (long double) (b.y - a.y);
}

long double cof(const point &a, long double m) {
	return -m * a.x + a.y;
}

bool on(long double x, long double y, point a, point b) {
	int lowx,highx,lowy,highy;

	lowx = min(a.x,b.x);
	lowy = min(a.y,b.y);
	highx = max(a.x,b.x);
	highy = max(a.y,b.y);

	if (x < lowx && !(fabsl(lowx-x) < 1.0e-9)) {
		return false;
	}
	if (x > highx && !(fabsl(highx-x) < 1.0e-9)) {
		return false;
	}
	if (y < lowy && !(fabsl(lowy-y) < 1.0e-9)) {
		return false;
	}
	if (y > highy && !(fabsl(highy-y) < 1.0e-9)) {
		return false;
	}

	return true;
}

bool inter(const vector<point> &a, const vector<point> &b){
	if (a.size() == 1 || b.size() == 1) {
		const vector<point> *single;
		const vector<point> *other;
		if (a.size() == 1) {
			single = &a;
			other = &b;
		} else {
			single = &b;
			other = &a;
		}
		fi(other->size()) {
			if ((*other)[i].x == (*single)[0].x
			     && (*other)[i].y == (*single)[0].y) {
				return true;
			}
		}
		return false;
	}

	f(i, 1, a.size()) {
		bool vert1;
		long double m1 = slope(a[i-1],a[i], &vert1);
		long double c1 = cof(a[i-1],m1);
		f(j,1,b.size()) {
			bool vert2;
			long double m2 = slope(b[i-1],b[i], &vert2);
			long double c2 = cof(b[i-1],m2);

			if (vert1 && vert2) {
				if (a[i].x == b[i].x) return true;
				continue;
			}
			long double x;
			long double y;
			if (vert1) {
				x = a[i].x;
				y = m2 * x + c2;
			} else if (vert2) {
				x = b[i].x;
				y = m1 * x + c1;
			} else {
				if (fabsl(m1-m2) < 1.0e-9) {
					continue;
				}

				x = (c2 - c1)  / (m1 - m2);
				y = m1 * x + c1;
			}

			if (on(x,y,a[i-1],a[i]) && on(x,y,b[i-1],b[i])) {
				return true;
			}
		}
	}
	return false;
}

    class PolylineUnion
        { 
        public: 
        int countComponents(vector <string> polylines) 
            { 
							string all;
							fi(polylines.size()) {
								all += polylines[i];
							}

							VS te = toks(all, " ");
							vector<vector<point> > lines;

							fi(te.size()) {
								VS t = toks(te[i], "-");
								vector<point> po;
								fj(t.size()) {
									point p;
									sscanf(t[j].c_str(), "%d,%d", &p.x,&p.y);
									po.push_back(p);
								}
								lines.push_back(po);
							}

							vector<int> left(lines.size(), 1);

							fi(lines.size()) {
								f(j,i+1,lines.size()) {
									if (inter(lines[i], lines[j])) {
										if (left[j] == 0) left[i] = 0;
										left[j] = 0;
									}
								}
							}

							int ret = 0;
							fi(left.size()) if (left[i]) ret++;
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0,0-10,10 0,10-10,0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, countComponents(Arg0)); }
	void test_case_1() { string Arr0[] = {"0,0-10,5 5,0-15,5-10,10-5,5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, countComponents(Arg0)); }
	void test_case_2() { string Arr0[] = {"1","3,0-5,5 4,0-4,20"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countComponents(Arg0)); }
	void test_case_3() { string Arr0[] = {"10,0-10,1-9,2-9,3-8,4 ","8,2-9,2-10,3 ","12,2-11,2-9,1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, countComponents(Arg0)); }
	void test_case_4() { string Arr0[] = {"0,0-10,0-0,0 20,0-8,0-20,0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, countComponents(Arg0)); }
	void test_case_5() { string Arr0[] = {"1,1 2,2 3,3 4,4 3,3-4,4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(5, Arg1, countComponents(Arg0)); }
	void test_case_6() { string Arr0[] = {"10,10-20,10 20,10-15,18 15,18-10,10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(6, Arg1, countComponents(Arg0)); }
	void test_case_7() { string Arr0[] = {"1,1 1,1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(7, Arg1, countComponents(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PolylineUnion ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

