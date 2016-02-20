// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// The vector <int> bag describes a bag of non-negative 
// integers. A bag is the same thing as a set, only it may 
// contain repeated elements.
// The order of elements in a bag does not matter.
// 
// 
// 
// Given two bags A and B, we say that A is a sub-bag of B if 
// A can be obtained by erasing zero or more elements from B.
// 
// 
// 
// The weight of a bag is the sum of its elements.
// 
// 
// 
// Examples: 
// The bags (1,2,1,3,1) and (3,1,1,1,2) are the same, but 
// different from the bag (1,2,3,3). 
// Bags (1,2) and (3,1,1) are sub-bags of the bag 
// (1,2,1,3,1), but bag (1,2,2) is not. 
// The weight of the bag (1,2,1,3,1) is 1+2+1+3+1=8.
// 
// 
// 
// Write a method that will compute how many sub-bags of bag 
// have a prime weight.
// 
// 
// DEFINITION
// Class:PrimeSums
// Method:getCount
// Parameters:vector <int>
// Returns:long long
// Method signature:long long getCount(vector <int> bag)
// 
// 
// NOTES
// -A prime number is a positive integer with exactly two 
// positive integer divisors.
// -Zero (0) and one (1) are not prime numbers.
// 
// 
// CONSTRAINTS
// -bag will contain between 1 and 50 elements, inclusive.
// -Each element in bag will be between 0 and 10,000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1,1,2,7}
// 
// Returns: 5
// 
// 
// This bag has 12 different sub-bags: (1,1,2,7), (1,2,7), 
// (2,7), (1,1,7), (1,7), (7), (1,1,2), (1,2), (2), (1,1), 
// (1), and ().
// 
// 
// Out of these 12, 5 have prime weights: (1,1,2,7) has 
// weight 11, (7) has weight 7, (1,2) has weight 3, and both 
// (2) and (1,1) have weight 2.
// 
// 
// 1)
// {1,1,1,1,1,1,1,1,1,1}
// 
// Returns: 4
// 
// This bag has eleven different sub-bags. Out of them four 
// have prime weights (2, 3, 5, and 7).
// 
// 2)
// {4,6,8,10,12,14}
// 
// Returns: 0
// 
// The empty sub-bag has weight zero, and any other sub-bag 
// has an even weight greater than 2.
// 
// 3)
// {1,2,4,8,16,32,64,128}
// 
// Returns: 54
// 
// 
// 
// 4)
// {1234,5678,9012,3456,7890,2345,6789,123,4567,8901}
// 
// Returns: 97
// 
// 
// 
// 5)
// {0,0,7}
// 
// Returns: 3
// 
// 
// 
// END CUT HERE
#line 110 "PrimeSums.cc"
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
typedef long long ll;

ll sum[500005];

bool prime(int i) {
	if (i == 0 || i == 1) return false;
	if (i == 2) return true;
	if (i % 2 == 0) return false;

	for(int j = 3; j * j <= i; j += 2) {
		if (i % j == 0) return false;
	}

	return true;
}

    class PrimeSums
        { 
        public: 
        long long getCount(vector <int> bag) 
            { 
							int t = 0;
							fi(bag.size()) t += bag[i];

							memset(sum, 0, sizeof(sum));
							sum[0] = 1;

							sort(bag.begin(), bag.end());

							int p = -1;
							int pno = -1;

							fi(bag.size()) {
								if (bag[i] == 0) {
									sum[0]++;
									continue;
								}
								for(int j = t; j >= bag[i]; j--){
									if (p == bag[i] && j <= pno) break;
									if (sum[j - bag[i]] > 0) {
										sum[j] += sum[j - bag[i]];
										pno = j;
									}
								}
								p = bag[i];
							}


							ll ret = 0;
							fi(t+1) {
								if (prime(i)) ret += sum[i];
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1,2,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { int Arr0[] = {4,6,8,10,12,14}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { int Arr0[] = {1,2,4,8,16,32,64,128}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 54LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { int Arr0[] = {1234,5678,9012,3456,7890,2345,6789,123,4567,8901}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 97LL; verify_case(4, Arg1, getCount(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(5, Arg1, getCount(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PrimeSums ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

