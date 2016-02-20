// BEGIN CUT HERE
// PROBLEM STATEMENT
// The hotel industry  is difficult to thrive in, especially 
// when competing at a resort city like Las Vegas.  
// Marketing is essential and often gets a large part of 
// total revenues.  You have a list of cities you can market 
// at, 
// and a good estimate of how many customers you will get for 
// a certain amount of money spent at each city.  
// 
// 
// You are given int[]s customers and cost.  cost[i] is the 
// amount of money required to get customers[i] customers 
// from the i-th city.  You are only allowed to spend integer 
// multiples of the cost for any city. For example, if it 
// costs 9 to get 3 customers from a certain city, you can 
// spend 9 to get 3 customer, 18 to get 6 customers, 27 to 
// get 9 customers, but not 3 to get 1 customer, or 12 to get 
// 4 customers.  Each city has an unlimited number of 
// potential customers.  Return the minimum amount of money 
// required to get at least minCustomers customers.
// 
// DEFINITION
// Class:Hotel
// Method:marketCost
// Parameters:int, vector <int>, vector <int>
// Returns:int
// Method signature:int marketCost(int minCustomers, vector 
// <int> customers, vector <int> cost)
// 
// 
// CONSTRAINTS
// -minCustomers will be between 1 and 1000, inclusive.
// -customers will contain between 1 and 20 elements, 
// inclusive.
// -cost will have the same number of elements as customers.
// -Each element of cost and customers will be between 1 and 
// 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 10
// {1,2,3}
// {3,2,1}
// 
// Returns: 4
// 
// Just get 12 customers from the third city.
// 
// 1)
// 10
// {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
// {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
// 
// Returns: 10
// 
// It does not matter from which city you get your customers.
// 
// 2)
// 12
// {5, 1}
// {3, 1}
// 
// Returns: 8
// 
// Get 10 customers from the first city, and 2 from the 
// second city.
// 
// 3)
// 100
// {9, 11, 4, 7, 2, 8}
// {4, 9, 3, 8, 1, 9}
// 
// Returns: 45
// 
// 
// 
// END CUT HERE
#line 82 "Hotel.cpp"
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

int dp[5005];

    class Hotel
        { 
        public: 
        int marketCost(int n, vector <int> cu, vector <int> co) 
            { 
							memset(dp, 0x7f, sizeof(dp));

							dp[0] = 0;
							fi(5005) {
								fj(cu.size()) {
									int in = i + cu[j];
									int cos = dp[i] + co[j];

									if (in < 5005) {
										dp[in] <?= cos;
									}
								}
							}

							int min = dp[n];
							f(i,n,5005) {
								min <?= dp[i];
							}

							return min;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(0, Arg3, marketCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; verify_case(1, Arg3, marketCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 12; int Arr1[] = {5, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 8; verify_case(2, Arg3, marketCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 100; int Arr1[] = {9, 11, 4, 7, 2, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4, 9, 3, 8, 1, 9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 45; verify_case(3, Arg3, marketCost(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Hotel ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

