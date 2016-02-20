// BEGIN CUT HERE
// PROBLEM STATEMENT
// In Chemistry, there's a different meaning to the word 
// 'solution' than in programming. When we mix x liters of 
// some substance with (100-x) liters of water, we get 100 
// liters of x-% solution of that substance.
// You are given several bottles containing solutions of the 
// same substance. The i-th bottle contains amount[i] liters 
// of percent[i]-% solution. Return the maximal number of 
// liters of need-% solution we can get by pouring together 
// some of these bottles (possibly partially, see example 0).
// 
// DEFINITION
// Class:MixingLiquids
// Method:howMuch
// Parameters:vector <int>, vector <int>, int
// Returns:double
// Method signature:double howMuch(vector <int> percent, 
// vector <int> amount, int need)
// 
// 
// NOTES
// -The returned value must have an absolute or relative 
// error less than 1e-9.
// 
// 
// CONSTRAINTS
// -percent will contain between 1 and 50 elements, inclusive.
// -Each element of percent will be between 0 and 100, 
// inclusive.
// -amount will contain the same number of elements as percent.
// -Each element of amount will be between 1 and 1000, 
// inclusive.
// -need will be between 0 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {0, 100}
// {20, 30}
// 50
// 
// Returns: 40.0
// 
// We have 20 liters of water and 30 liters of pure 
// substance. We need a 50% solution, so we combine all the 
// water with 20 liters of substance.
// 
// 1)
// {0, 100}
// {20, 30}
// 60
// 
// Returns: 50.0
// 
// We can use everything we have.
// 
// 2)
// {90, 70, 80}
// {10, 10, 10}
// 50
// 
// Returns: 0.0
// 
// All our bottles contain too much substance.
// 
// 3)
// {30, 80, 60}
// {40, 10, 15}
// 57
// 
// Returns: 35.18518518518519
// 
// 
// 
// 4)
// {50,50,50}
// {395,971,964}
// 50
// 
// Returns: 2330.0
// 
// END CUT HERE
#line 86 "MixingLiquids.cpp"
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

struct abc {
	abc(int per, long double a) : p(per), amt(a) { }
	int p;
	long double amt;
};

bool cmp(const abc &a, const abc &b) {
	return a.p < b.p;
}

    class MixingLiquids
        { 
        public: 
        double howMuch(vector <int> percent, vector <int> amount, int need) 
            { 
							vector<abc> am;
							fi(amount.size()) {
								am.push_back(abc(percent[i], amount[i]));
							}

							sort(am.begin(), am.end(), cmp);

							long double ret = 0;
							fi(am.size()) {
								if (am[i].p == need) {
									ret += am[i].amt;
									am.erase(am.begin() + i);
									--i;
								}
							}
							abc tmp(need, 0);
							vector<abc>::iterator itr = lower_bound(am.begin(),
									am.end(), tmp, cmp);
							if (itr == am.end()) {
								return ret;
							}

							if (itr == am.begin() && itr->p != need) {
								return ret;
							}

							int pos = itr - am.begin();

							int lo = pos - 1;
							int hi = pos;

							while (lo >= 0 && hi < am.size()) {
								long double frac = (need - am[lo].p) / (long double)(am[hi].p - need);

								if (frac * am[lo].amt > am[hi].amt) {
									ret += am[hi].amt / frac + am[hi].amt; 
									am[lo].amt -= am[hi].amt / frac;
									am[hi].amt = 0;
									hi++;
								} else {
									ret += am[lo].amt + frac * am[lo].amt;
									am[hi].amt -= frac * am[lo].amt;
									am[lo].amt = 0;
									lo--;
								}
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; double Arg3 = 40.0; verify_case(0, Arg3, howMuch(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 60; double Arg3 = 50.0; verify_case(1, Arg3, howMuch(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {20, 40, 90}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 10, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 30; double Arg3 = 0.0; verify_case(2, Arg3, howMuch(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {30, 80, 60}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {40, 10, 15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 57; double Arg3 = 35.18518518518519; verify_case(3, Arg3, howMuch(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {50,50,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {395,971,964}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; double Arg3 = 2330.0; verify_case(4, Arg3, howMuch(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MixingLiquids ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

