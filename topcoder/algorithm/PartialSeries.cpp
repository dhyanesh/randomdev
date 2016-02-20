// BEGIN CUT HERE
// PROBLEM STATEMENT
// We say that a local maximum of a series of numbers is a 
// number in the series such that the previous and next 
// numbers in the series are both strictly smaller than it.  
// Similarly, a local minimum is a number such that the 
// previous and next numbers are both strictly greater than 
// it.  A local extremum of a series is either a local 
// maximum or minimum.  Note that the first and last elements 
// of a series cannot be local extrema.
// 
// You've been given a partial series of numbers with some 
// numbers in the series missing.  You know that the missing 
// numbers are all from the set of available numbers (each 
// one may be used at most once).  Your task is to fill in 
// the missing numbers of the series such that the number of 
// local extrema is as small as possible.  If there are many 
// such series that satisfy this contraint, you should return 
// the one with the smallest first entry.  If there is still 
// more than one solution, you should return the one with the 
// smallest second entry, and so on if there are still 
// several solutions.
// 
// The input will be described by a vector <int> series.  
// Each element of series will be either -1, representing a 
// missing number, or non-negative otherwise.
// 
// DEFINITION
// Class:PartialSeries
// Method:getFirst
// Parameters:vector <int>, vector <int>
// Returns:vector <int>
// Method signature:vector <int> getFirst(vector <int> 
// series, vector <int> available)
// 
// 
// NOTES
// -Each available number may be used at most one time.
// 
// 
// CONSTRAINTS
// -series will contain between 1 and 50 elements, inclusive.
// -available will contain between 0 and 15 elements, 
// inclusive.
// -Each element of series will be between -1 and 10, 
// inclusive.
// -Each element of available will be between 0 and 10, 
// inclusive.
// -There will be at least as many available numbers as 
// missing ones.
// 
// 
// EXAMPLES
// 
// 0)
// {-1,-1,-1,-1,-1}
// {1,2,3,4,5}
// 
// Returns: {1, 2, 3, 4, 5 }
// 
// We just fill in the numbers in increasing order to avoid 
// any local extrema.
// 
// 1)
// {1,2,-1,4,5}
// {10}
// 
// Returns: {1, 2, 10, 4, 5 }
// 
// Since we only have one choice, 10 must be a local maximum 
// while 4 is a local minimum.
// 
// 2)
// {1,-1,6,2,4,-1,2,7,-1,-1}
// {1,2,4,7,8,8}
// 
// Returns: {1, 1, 6, 2, 4, 2, 2, 7, 7, 4 }
// 
// 
// 
// 3)
// {8,-1,6,4,-1,-1,6}
// {2,3,6}
// 
// Returns: {8, 6, 6, 4, 2, 3, 6 }
// 
// 
// 
// 4)
// {-1, 5, -1}
// {1, 1, 9}
// 
// Returns: {1, 5, 9 }
// 
// 
// 
// END CUT HERE
#line 99 "PartialSeries.cpp"
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

VI s,a;
int ns,na;

map<pair<int,int> ,pair<int,int> > memo;

bool ismax(int pos) {
	return (s[pos] > s[pos+1] && s[pos] > s[pos-1]);
}

bool ismin(int pos) {
	return (s[pos] < s[pos+1] && s[pos] < s[pos-1]);
}

bool isextr(int pos) {
	if (pos == 0 || pos >= ns-1) return false;
	return ismin(pos) || ismax(pos);
}

pair<int,int> go(int pos, int st) {
	pair<int,int> te(pos,st);

	if (pos == ns) return pair<int,int>(0,-1);
	if (st == (1<<na) - 1) return pair<int,int>(0,-1);

	if (memo.count(te) > 0) return memo[te];

	if (s[pos] != -1)
		return memo[te]=pair<int,int>(go(pos+1, st).first, -1);

	int ret = 1<<20;
	int bpos = 0;
	fi(na) {
		if (st&(1<<i)) {
			continue;
		}
		s[pos] = a[i];
		pair<int,int> t = go(pos + 1, st | (1<<i));
		bool f = false;
		if (pos + 1 < ns && s[pos+1] == -1) {
			s[pos+1] = a[t.second];
			f=true;
		}
		if (pos  + 1< ns && s[pos+1] != -1 && isextr(pos)) {
			t.first++;
		}
		if (isextr(pos-1)) {
			t.first++;
		}
		if (f) s[pos+1] = -1;
		if (t.first == ret &&
				a[i] < a[bpos]) {
			ret = t.first;
			bpos = i;
		}
		if (t.first< ret) {
			ret = t.first;
			bpos = i;
		}
		s[pos] = -1;
	}

	return memo[te] = pair<int,int>(ret,bpos);
}

    class PartialSeries
        { 
        public: 
        vector <int> getFirst(vector <int> series, vector <int> available) 
            { 
							s = series;
							a = available;
							ns = series.size();
							na = available.size();
							memo.clear();

							go(0,0);

							VI ns = s;

							int st = 0;
							fi(s.size()) {
								if (s[i] == -1) {
									pair<int,int> p = memo[pair<int,int>(i,st)];
									ns[i] = a[p.second];
									st |= (1<<p.second);
								}
							}

							return ns;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {-1,-1,-1,-1,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 4, 5 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getFirst(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,-1,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 10, 4, 5 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getFirst(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,-1,6,2,4,-1,2,7,-1,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,4,7,8,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 6, 2, 4, 2, 2, 7, 7, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getFirst(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {8,-1,6,4,-1,-1,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8, 6, 6, 4, 2, 3, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getFirst(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-1, 5, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 5, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getFirst(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PartialSeries ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

