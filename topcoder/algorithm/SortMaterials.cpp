// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Your shipping company has just delivered some materials to 
// you, and you'd like to find out how many of these 
// materials are useful. All materials are packed into 
// cubical boxes. The information about each box will be 
// given to you in a vector <string> data, with the i-th 
// element representing the i-th box. Each element of data 
// will be formatted as "EDGE QUALITY COLOR" (quotes for 
// clarity), where EDGE and QUALITY are positive integers 
// representing the length of an edge of the box and the 
// quality of the material (higher is better), respectively. 
// COLOR will be a sequence of lowercase letters representing 
// the color of the material.
// 
// 
// 
// A vector <string> requirements will represent the 
// specifications for your project. Each element of 
// requirements will follow one of the following templates 
// (all quotes for clarity only):
// 
// "EDGE=X" (where X is a positive integer), which means that 
// you can use only materials from boxes with edge length 
// equal to X.
// "QUALITY=X" (where X is a positive integer), which means 
// that you can use only materials with the quality greater 
// than or equal to X.
// "COLOR=s" (where s is a sequence of lowercase letters), 
// which means that you can use only materials of color s.
// 
// 
// Given all this information, you are to return the total 
// volume of the materials you can use.
// 
// 
// DEFINITION
// Class:SortMaterials
// Method:totalVolume
// Parameters:vector <string>, vector <string>
// Returns:int
// Method signature:int totalVolume(vector <string> data, 
// vector <string> requirements)
// 
// 
// NOTES
// -The volume of a box with edge length of X is equal to 
// X*X*X.
// 
// 
// CONSTRAINTS
// -data will contain between 1 and 50 elements, inclusive.
// -Each element of data will contain between 5 and 50 
// characters, inclusive.
// -Each element of data will be formatted as "EDGE QUALITY 
// COLOR" (quotes for clarity), where EDGE and QUALITY are 
// integers between 1 and 99, inclusive, with no leading 
// zeroes, and COLOR is a non-empty sequence of lowercase 
// letters ('a'-'z').
// -requirements will contain between 0 and 50 elements, 
// inclusive.
// -Each element of requirements will contain between 6 and 
// 50 characters, inclusive.
// -Each element of requirements will be formatted as 
// "EDGE=X" (where X is an integer  between 1 and 99, 
// inclusive, with no leading zeroes), "QUALITY=X" (where X 
// is an integer between 1 and 99, inclusive, with no leading 
// zeroes), or "COLOR=s" (where s is a non-empty sequence of 
// lowercase letters ('a'-'z').  All quotes for clarity only.
// 
// 
// EXAMPLES
// 
// 0)
// {"1 20 red", "2 30 blue", "10 1 green"}
// {}
// 
// Returns: 1009
// 
// With no special requirements, you can use all the 
// materials you get. The sum of the volumes is 1*1*1 + 2*2*2 
// + 10*10*10 = 1009.
// 
// 1)
// {"1 20 red", "2 30 blue", "10 1 green"}
// {"QUALITY=20"}
// 
// Returns: 9
// 
// Now you must choose materials with QUALITY of at least 20, 
// so you can not use the third box.
// 
// 2)
// {"1 20 red", "2 30 blue", "10 1 green", "5 5 red", "5 6 
// red"}
// {"COLOR=red", "EDGE=5"}
// 
// Returns: 250
// 
// 
// 
// 3)
// {"1 20 red", "2 30 blue", "10 1 green", "5 5 red", "5 6 
// red"}
// {"EDGE=1", "EDGE=5"}
// 
// Returns: 0
// 
// Obviously, no box can have an edge length of 1 and 5 
// simultaneously.
// 
// END CUT HERE
#line 115 "SortMaterials.cpp"
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


    class SortMaterials
        { 
        public: 
        int totalVolume(vector <string> data, vector <string> req) 
            { 
							int e = -1;
							string c;
							int q = -1;

							fi(req.size()) {
								VS te = toks(req[i], "=");
								if (te[0]=="QUALITY") {
									q >?= fromString<int>(te[1]);
								} else if (te[0]=="EDGE") {
									if (e != -1) return 0;
									e  = fromString<int>(te[1]);
								} else if (te[0]=="COLOR") {
									if (!c.empty()) return 0;
									c = te[1];
								}
							}

							int ret = 0;
							fi(data.size()) {
								VS te = toks(data[i], " ");
								int a = fromString<int>(te[0]);
								int b = fromString<int>(te[1]);

								bool ok = true;
								if (e != -1 && a != e) ok = false;
								if (!c.empty() && te[2] != c) ok=false;
								if (b<q) ok= false;

									if (ok) {
										ret+=a*a*a;
										}
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 20 red", "2 30 blue", "10 1 green"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1009; verify_case(0, Arg2, totalVolume(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1 20 red", "2 30 blue", "10 1 green"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"QUALITY=20"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(1, Arg2, totalVolume(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"1 20 red", "2 30 blue", "10 1 green", "5 5 red", "5 6 red"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"COLOR=red", "EDGE=5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 250; verify_case(2, Arg2, totalVolume(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1 20 red", "2 30 blue", "10 1 green", "5 5 red", "5 6 red"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"EDGE=1", "EDGE=5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, totalVolume(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SortMaterials ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

