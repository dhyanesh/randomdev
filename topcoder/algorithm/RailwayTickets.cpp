// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A railway company has a special train line that goes 
// through an unshared rail, passing by several stations 
// along the way. Stations are numbered increasingly in the 
// direction the train passes them (the train is only one-
// way). Each client must schedule his trip (indicating 
// departing and arriving stations) at least a day before it 
// is made. Your task is to write a program that determines 
// the minimum number of requests that must be denied in 
// order to ensure that everybody gets a seat.
// 
// You will be given an int seats which indicates the maximum 
// number of passengers that can be inside the train at the 
// same time. You will also be given the list of requests as 
// a vector <string> travel. Each element of travel will be a 
// single space separated list of requests of the form "A-B" 
// (quotes for clarity), where A is the departing station and 
// B is the arriving station. You must decide whether each 
// request should be accepted or denied.  Accepted requests 
// will be assigned a seat number, and no two passengers 
// whose trips overlap can have the same seat.  Return the 
// minimum number of requests you must deny in order to 
// fulfill the above requirements.
// 
// 
// DEFINITION
// Class:RailwayTickets
// Method:minRejects
// Parameters:vector <string>, int
// Returns:int
// Method signature:int minRejects(vector <string> travel, 
// int seats)
// 
// 
// CONSTRAINTS
// -seats will be between 1 and 1000, inclusive.
// -travel will contain between 1 and 50 elements, inclusive.
// -Each element of travel will contain between 1 and 50 
// characters, inclusive.
// -Each element of travel will be a single space separated 
// list, with no leading or trailing spaces, of requests of 
// the form "A-B" (quotes for clarity) where A and B are 
// integers between 1 and 10000, inclusive, with no leading 
// zeroes, and A is strictly less than B.
// 
// 
// EXAMPLES
// 
// 0)
// {"1-3 3-5",
//  "2-4 4-6",
//  "1-2 2-3 3-4 4-5"}
// 2
// 
// Returns: 2
// 
// There are only 2 seats in the train, so you must surely 
// get 1-3, 2-4 or 1-2 out, because they all won't fit during 
// the travel from station 2 to station 3. Also, one of 3-5, 
// 4-6 or 4-5 has to go. Eliminating only 2-4 and 4-6 leaves 
// enough room for the rest (assigning seat 1 to 1-3 and 3-5 
// and seat 2 to 1-2, 2-3, 3-4 and 4-5).
// 
// 1)
// {"1-10000","2-10000","1-9999","2-9999","5000-5001"}
// 3
// 
// Returns: 2
// 
// Two people cannot share the same seat, so we can only 
// accommodate 3 of these requests.
// 
// 2)
// {"1-2 2-5 2-8 234-236 56-878 6-34",
//  "234-776 3242-8000 999-1000 3-14",
//  "121-122 435-3455 123-987 77-999"}
// 1000
// 
// Returns: 0
// 
// There's plenty of room for everybody.
// 
// 3)
// {"1-2 2-3 3-4 4-5 5-6 6-7 1-3 2-7 1-2 1-4"}
// 1
// 
// Returns: 4
// 
// 
// 
// END CUT HERE
#line 95 "RailwayTickets.cpp"
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

vector<pair<int,int> > vec;

VI path;

map<int, VI> memo;

VI go(int st) {
	if (memo.count(st)) return memo[st];
	VI ret;
	fi(vec.size()) {
		if (vec.first >= st) {
			VI te = go(vec.second);
			if (te.size() + 1 > ret.size()) {
				ret = te;
				ret.push_back(i);
			}
		}
	}

	return memo[st]=ret;
}

    class RailwayTickets
        { 
        public: 
        int minRejects(vector <string> travel, int seats) 
            { 
							string te;
							fi(travel.size()) {
								te += travel[i] + " ";
							}

							VI t = toksT<int>(te, "- ");

							fi(t.size()) {
								pair<int, int> a;
								a.first = t[i++];
								a.second = t[i];
								last >?= a.second;
								vec.push_back(a);
							}

							int num = 0;
							fi(seats) {
								memo.clear();
								sort(a.begin(), a.end());
								VI path = go(0);
								num += path.size();
								fi(path.size()) {
									a[path[i]].first = -1;
								}
								fi(a.size()) {
									if (a.first == -1) {
										a.erase(a.begin() + i);
										--i;
									}
								}
							}

							return a.size() - num;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1-3 3-5",
 "2-4 4-6",
 "1-2 2-3 3-4 4-5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; verify_case(0, Arg2, minRejects(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1-10000","2-10000","1-9999","2-9999","5000-5001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(1, Arg2, minRejects(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"1-2 2-5 2-8 234-236 56-878 6-34",
 "234-776 3242-8000 999-1000 3-14",
 "121-122 435-3455 123-987 77-999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 0; verify_case(2, Arg2, minRejects(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1-2 2-3 3-4 4-5 5-6 6-7 1-3 2-7 1-2 1-4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; verify_case(3, Arg2, minRejects(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        RailwayTickets ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

