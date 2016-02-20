// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// There is a bus stop near your home.  The daily bus routes 
// are given in the vector <string> buses, each element of 
// which is formatted "START INTERVAL COUNT" (quotes for 
// clarity).  Each element describes a single route 
// consisting of COUNT buses.  The first bus on the route 
// comes at time START, and the interval between each pair of 
// consecutive buses is INTERVAL. In other words, the buses 
// on that route come at times START, START + INTERVAL, ..., 
// START + (COUNT - 1) * INTERVAL.
// 
// 
// You arrive at the bus stop at time arrivalTime. Return the 
// amount of time you must wait before the next bus (from any 
// of the given routes) comes to your stop. If there's a bus 
// at the stop at the exact moment you arrive, return 0. If 
// no buses come for the rest of the day, return -1.
// 
// 
// DEFINITION
// Class:BusAwaiting
// Method:waitingTime
// Parameters:vector <string>, int
// Returns:int
// Method signature:int waitingTime(vector <string> buses, 
// int arrivalTime)
// 
// 
// CONSTRAINTS
// -buses will contain between 1 and 50 elements, inclusive.
// -Each element of buses will be formatted "START INTERVAL 
// COUNT" (quotes for clarity), where START, INTERVAL and 
// COUNT are integers with no leading zeros.
// -Each START will be between 1 and 1,000,000, inclusive.
// -Each INTERVAL will be between 1 and 10,000, inclusive.
// -Each COUNT will be between 1 and 100, inclusive.
// -arrivalTime will be between 1 and 1,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"150 50 10"}
// 285
// 
// Returns: 15
// 
// There is only one bus route.  The buses come at times 150, 
// 200, 250, ..., 600.  You arrive at time 285 and you're 
// able to catch a bus at time 300.
// 
// 1)
// {"123456 10000 1"}
// 123456
// 
// Returns: 0
// 
// You are lucky to catch the one and only bus at the exact 
// moment it arrives.
// 
// 
// 2)
// {"270758 196 67",
//  "904526 8930 66",
//  "121164 3160 56"}
// 1
// 
// Returns: 121163
// 
// You arrive very early, but all the buses start quite late.
// 
// 
// 3)
// {"718571 2557 74",
//  "480573 9706 54",
//  "16511 6660 90"}
// 1000000
// 
// Returns: -1
// 
// By the time you arrive, all the buses have already passed.
// 
// 4)
// {"407917 8774 24",
//  "331425 4386 58",
//  "502205 9420 32",
//  "591461 1548 79",
//  "504695 8047 53"}
// 395439
// 
// Returns: 1776
// 
// 
// 
// END CUT HERE
#line 99 "BusAwaiting.cc"
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

typedef long long ll;

    class BusAwaiting
        { 
        public: 
        int waitingTime(vector <string> buses, int at) 
            { 
              VVI b = toksvvi(buses, " ");

              ll ans = 1LL<<45;

              fi(b.size()) {
                ll bt = b[i][0];
                fj(b[i][2]) {
                  ll bti = bt + j * b[i][1];
                  if (bti >= at) {
                    ans <?= (bti-at);
                    break;
                  }
                }
              }

              if (ans == 1LL<<45) return -1;

              return ans;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"150 50 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 285; int Arg2 = 15; verify_case(0, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"123456 10000 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 123456; int Arg2 = 0; verify_case(1, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"270758 196 67",
 "904526 8930 66",
 "121164 3160 56"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 121163; verify_case(2, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"718571 2557 74",
 "480573 9706 54",
 "16511 6660 90"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000; int Arg2 = -1; verify_case(3, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"407917 8774 24",
 "331425 4386 58",
 "502205 9420 32",
 "591461 1548 79",
 "504695 8047 53"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 395439; int Arg2 = 1776; verify_case(4, Arg2, waitingTime(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BusAwaiting ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

