// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are trying to predict the outcome of a race between n 
// runners, numbered from 0 to n - 1.You are given two vector 
// <int>s, first and second.  It is guaranteed that for all 
// i, the runner numbered first[i] will always beat the 
// runner numbered second[i]. Determine how many final 
// orderings are possible, modulo 1,000,003. If the 
// information is contradictionary, return 0. Runners are 
// never tied.
// 
// DEFINITION
// Class:RaceOrdering
// Method:countOrders
// Parameters:int, vector <int>, vector <int>
// Returns:int
// Method signature:int countOrders(int n, vector <int> 
// first, vector <int> second)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 30, inclusive.
// -first and second will each contain between 0 and 15 
// elements, inclusive.
// -first and second will contain the same number of elements.
// -Each element of first and second will be between 0 and n 
// - 1, inclusive.
// -first[i] does not equal second[i] for all i between 0 and 
// m - 1, inclusive, where m is the number of elements in 
// first and second.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// {1}
// {2}
// 
// Returns: 3
// 
// Contestant 1 beat contestant 2, so the valid orders are 
// 012, 102 and 120.
// 
// 1)
// 4
// {0, 0}
// {1, 2}
// 
// Returns: 8
// 
// Contestant 0 beat contestants 1 and 2, but there is no 
// information on contestant 3. The valid orderings are 3012, 
// 3021, 0312, 0321, 0132, 0231, 0123 and 0213.
// 
// 2)
// 10
// {1, 2, 3}
// {2, 3, 1}
// 
// Returns: 0
// 
// There is no way to satisfy this cycle.
// 
// 3)
// 30
// {}
// {}
// 
// Returns: 90317
// 
// 
// 
// END CUT HERE
#line 76 "RaceOrdering.cpp"
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

int memo[31][1<<17];

bool ok[31][31];

int n,m;
int x;

VI f,s;

int co(int m){
	int ret = 0;
	while (m) {
		m >>= 1;
		ret++;
	}
	return ret;
}

int go(int pos, int st) {
	if (memo[pos][st] >= 0) return memo[pos][st];

	if (pos >= n){
		if (st == (1<<m) - 1) return 1;
		return 0;
	}

	int ret = 0;
	fi(m) {
		if (st & (1<<i))
			continue;

		
		bool oki = true;
		fj(m) {
			if (st & (1<<j)) {
				if (!ok[f[j]][f[i]]) {
					oki = false;
					break;
				}
			} else {
				if (!ok[f[i]][f[j]]) {
					oki = false;
					break;
				}
			}
		}

		if (oki)
			ret = (ret + go(pos + 1,st|(1<<i))) % 1000003;
	}

	if ( m - co(st) < n - pos)
		ret = (ret + (x * (long long) go(pos + 1, st)) % 1000003) % 1000003;

	return memo[pos][st] = ret;
}

    class RaceOrdering
        { 
        public: 
        int countOrders(int no, vector <int> first, vector <int> second) 
            { 
							m = first.size();
							n = no;

							f = first;
							s = second;

							memset(ok, 1, sizeof(ok));

							fi(m) 
								ok[second[i]][first[i]] = false;

							x = 0;
							int done[40] = { 0 } ;
							fi(m) 
								done[first[i]] = 1;

							fi(n)
								if (!done[i]) ++x;

							memset(memo, 0xff, sizeof(memo));

							return go(0, 0);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(0, Arg3, countOrders(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 8; verify_case(1, Arg3, countOrders(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 3, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, countOrders(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 30; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 90317; verify_case(3, Arg3, countOrders(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        RaceOrdering ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

