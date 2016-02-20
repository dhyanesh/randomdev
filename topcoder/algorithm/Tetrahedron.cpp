// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given pairwise distances between four hypothetical 
// points. You need to return "YES" if there exist four 
// points in space with such distances between them, and "NO" 
// otherwise (all quotes for clarity only).
// The distances are given as a String[] d, each element of 
// which is a single-space separated list of integers. The j-
// th integer of the i-th element of d gives the distance 
// between the i-th and j-th points.
// 
// DEFINITION
// Class:Tetrahedron
// Method:exists
// Parameters:vector <string>
// Returns:string
// Method signature:string exists(vector <string> d)
// 
// 
// CONSTRAINTS
// -d will contain exactly 4 elements.
// -Each element of d will contain exactly 4 integers, 
// separated by single spaces.
// -Each integer in d will be between 0 and 10, inclusive, 
// and contain no extra leading zeroes.
// -The i-th integer of the i-th element of d will be 0.
// -The j-th integer of the i-th element of d will be equal 
// to the i-th integer of the j-th element of d.
// -The j-th integer of the i-th element of d will be between 
// 1 and 10, inclusive, when i is not equal to j.
// 
// 
// EXAMPLES
// 
// 0)
// {"0 1 1 1",
//  "1 0 1 1",
//  "1 1 0 1",
//  "1 1 1 0"}
// 
// Returns: "YES"
// 
// Just a regular tetrahedron.
// 
// 1)
// {"0 1 2 3",
//  "1 0 1 2",
//  "2 1 0 1",
//  "3 2 1 0"}
// 
// Returns: "YES"
// 
// Four points on a single line.
// 
// 2)
// {"0 1 2 4",
//  "1 0 1 2",
//  "2 1 0 1",
//  "4 2 1 0"}
// 
// Returns: "NO"
// 
// The first and last points are too far away.
// 
// 3)
// {"0 6 6 3",
//  "6 0 4 5",
//  "6 4 0 4",
//  "3 5 4 0"}
// 
// Returns: "YES"
// 
// 
// 
// 4)
// {"0 6 6 2",
//  "6 0 4 5",
//  "6 4 0 4",
//  "2 5 4 0"}
// 
// Returns: "NO"
// 
// 
// 
// END CUT HERE
#line 87 "Tetrahedron.cpp"
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

#define SQR(x) (x)*(x)

    class Tetrahedron
        { 
        public: 
        string exists(vector <string> di) 
            { 
							VVI d = toksvvi(di, " ");

							double cosa = SQR(d[0][3]) + SQR(d[1][3]) - SQR(d[0][1]) / (2.0 * d[0][3] * d[1][3]);
							double cosb = SQR(d[1][3]) + SQR(d[2][3]) - SQR(d[1][2]) / (2.0 * d[1][3] * d[2][3]);
							double cosc = SQR(d[0][3]) + SQR(d[2][3]) - SQR(d[0][2]) / (2.0 * d[0][3] * d[2][3]);

							double sqrtt = 1 + 2*cosa*cosb*cosc-SQR(cosa)-SQR(cosb)-SQR(cosc);

							if (sqrtt < 0) return "NO";

							return "YES";
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 1 1 1",
 "1 0 1 1",
 "1 1 0 1",
 "1 1 1 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(0, Arg1, exists(Arg0)); }
	void test_case_1() { string Arr0[] = {"0 1 2 3",
 "1 0 1 2",
 "2 1 0 1",
 "3 2 1 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(1, Arg1, exists(Arg0)); }
	void test_case_2() { string Arr0[] = {"0 1 2 4",
 "1 0 1 2",
 "2 1 0 1",
 "4 2 1 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(2, Arg1, exists(Arg0)); }
	void test_case_3() { string Arr0[] = {"0 6 6 3",
 "6 0 4 5",
 "6 4 0 4",
 "3 5 4 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(3, Arg1, exists(Arg0)); }
	void test_case_4() { string Arr0[] = {"0 6 6 2",
 "6 0 4 5",
 "6 4 0 4",
 "2 5 4 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(4, Arg1, exists(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Tetrahedron ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

