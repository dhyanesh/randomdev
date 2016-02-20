// BEGIN CUT HERE
// PROBLEM STATEMENT
// My friend has a "bigital" clock. It displays 12-hour times 
// in the 
// form hh:mm:ss, using 6 columns of 1 watt light bulbs.
// Each column displays its value in binary, where a light is 
// off
// to indicate a 0 and is on to indicate a 1. The clock can 
// display all
// 12-hour times, from 01:00:00 to 12:59:59.
// 
// For example, 03:22:59 requires 8 lights to be on and looks 
// like this:
// 
//     0	0   0	0   0	1
//     0	0   0	0   1	0
//     0	1   1	1   0	0
//     0	1   0	0   1	1
// 
// Given tStart and tEnd, return the total number of kilowatt
// hours used by the clock in displaying all the times from 
// tStart to tEnd,
// inclusive. The start and end time are less than 12 hours 
// apart. 
// 
// 
// DEFINITION
// Class:Bigital
// Method:energy
// Parameters:string, string
// Returns:double
// Method signature:double energy(string tStart, string tEnd)
// 
// 
// NOTES
// -A kilowatt hour is the energy used when using 1000 watts 
// for an hour.
// -A return value with either an absolute or relative error 
// of less than 1.0E-9 is considered correct.
// 
// 
// CONSTRAINTS
// -tStart and tEnd will each contain exactly 8 characters.
// -tStart and tEnd will each be in the form hh:mm:ss, where 
// hh is between 01 and 12, inclusive, mm is between 00 and 
// 59, inclusive, and ss is between 00 and 59, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// "12:00:00"
// "12:00:00"
// 
// Returns: 5.555555555555555E-7
// 
// 
// 
// 
//     Two bulbs are on for just one second. This require 2 
// watt seconds
//    which (60 seconds per minute, 60 minutes per hour, 1000 
// watts per 
//    kilowatt) is .000000555555555 kilowatt hours of energy.
// 
// 
// 
// 1)
// "12:59:59"
// "01:00:00"
// 
// Returns: 3.0555555555555556E-6
// 
// 
// 
//     Here the clock is running for 2 seconds, with lots of 
// lights on for
//    the first second and only 1 on for the second second.
// 
// 
// 2)
//  "12:01:00"
// "12:00:00"
// 
// Returns: 0.08392277777777778
// 
// 
// 
//     This is almost the full 12 hours.
// 
// 
// END CUT HERE
#line 94 "Bigital.cpp"
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

bool lesss(VI a, VI b) {
	if (a[0]==b[0]) {
		if (a[1]==b[1]) {
			return a[2]<b[2];
		}
		return a[1]<b[1];
	}
	return a[0]<b[0];
}

long long coun(int t) {
	long long ret = 0;
	while (t) {
		if (t&1) ret++;
		t >>= 1;
	}

	return ret;
}

long long cou(int t) {
	return coun(t/10) + coun(t%10);
}

long long mycount(int h, int m, int s) {
	h %= 12;
	if (!h) h = 12;
	return cou(h) + cou(m) + cou(s);
}

    class Bigital
        { 
        public: 
        double energy(string tStart, string tEnd) 
            { 
							VI ts = toksT<int>(tStart, ":");
							VI te = toksT<int>(tEnd, ":");

							if (lesss(te, ts)) {
								te[0] += 12;
							}

							int hh = ts[0];
							int mm = ts[1];
							int ss = ts[2];
							long long ret = 0;
							for(; hh < te[0]; ++hh) {
								for(; mm < 60; ++mm) {
									for(; ss < 60; ++ss) {
										ret += mycount(hh, mm, ss); 
									}
									ss = 0;
								}
								mm = 0;
							}

							for(;mm < te[1]; ++mm) {
								for(; ss < 60; ++ss) {
									ret += mycount(hh,mm,ss);
								}
								ss=0;
							}

							for(; ss<= te[2]; ++ss) {
								ret += mycount(hh,mm,ss);
							}


							return ret/1000.0/60.0/60.0;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "12:00:00"; string Arg1 = "12:00:00"; double Arg2 = 5.555555555555555E-7; verify_case(0, Arg2, energy(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "12:59:59"; string Arg1 = "01:00:00"; double Arg2 = 3.0555555555555556E-6; verify_case(1, Arg2, energy(Arg0, Arg1)); }
	void test_case_2() { string Arg0 =  "12:01:00"; string Arg1 = "12:00:00"; double Arg2 = 0.08392277777777778; verify_case(2, Arg2, energy(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Bigital ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

