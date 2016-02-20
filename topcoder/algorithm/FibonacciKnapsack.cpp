// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// We have n items, each with a specified weight and cost, 
// and a bag that can carry a specified maximum weight.  We 
// want to place a subset of these items into the bag such 
// that the total cost is maximized.
// 
// Unfortunately, this problem cannot be solved effectively 
// in the general case. However, there are pretty good 
// solutions for some special cases.  In this problem, you 
// are required to solve it for the special case where the 
// weights of the items are all Fibonacci numbers.
// 
// The first two Fibonacci numbers are 1 and 2. Each 
// successive number is obtained by adding together the two 
// previous numbers. Thus, the first Fibonacci numbers are 1, 
// 2, 3, 5, 8, 13... 
// 
// 
// You will be given vector <string> items and a string C. 
// Each element of items describes a single item and is 
// formatted "W P" (quotes for clarity only), where W is the 
// weight of the item and P is the cost. C is the maximum 
// weight that the bag can carry. Return the maximum total 
// cost of the subset of items that can fit into the bag.
// 
// 
// 
// DEFINITION
// Class:FibonacciKnapsack
// Method:maximalCost
// Parameters:vector <string>, string
// Returns:long long
// Method signature:long long maximalCost(vector <string> 
// items, string C)
// 
// 
// CONSTRAINTS
// -items will contain between 1 and 50 elements, inclusive.
// -Each element of items will be formatted "W P" (quotes for 
// clarity only).
// -In each element of items, W and P will be integers 
// between 1 and 1016, inclusive, with no leading zeroes.
// -Each W will be a Fibonacci number.
// -C will represent an integer between 1 and 1016, 
// inclusive, with no leading zeroes.
// 
// 
// EXAMPLES
// 
// 0)
// {"5 555", "8 195", "13 651"}
// "15"
// 
// Returns: 750
// 
// We should take the first and the second items. Their total 
// weight is 5+8=13, which does not exceed the maximum 
// capacity of 15, and their total cost is 555+195=750.
// 
// 1)
// {"5 555", "8 195", "13 751"}
// "15"
// 
// Returns: 751
// 
// Now it is more profitable to take only the last item with 
// the 751 cost.
// 
// 
// 2)
// {"55 1562", "5 814", "55 1962", "8 996", "2 716", "34 1792"}
// "94"
// 
// Returns: 4568
// 
// 
// 
// 3)
// {"13 89"}
// "1"
// 
// Returns: 0
// 
// 4)
// {"27777890035288 9419696870097445", 
//  "53316291173 6312623457097563", 
//  "165580141 8848283653257131"}
// "27777900000000"
// 
// Returns: 15160907110354694
// 
// 
// 
// END CUT HERE
#line 98 "FibonacciKnapsack.cpp"
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

struct ab {
	ll w,p;

};

    class FibonacciKnapsack
        { 
        public: 
        long long maximalCost(vector <string> items, string C) 
            { 
							vector<ab> it(items.size());

							fi(items.size()) {
								sscanf(items[i].c_str(), "%lld %lld", &it[i].w, &it[i].p);
							}

							ll c;
							sscanf(C.c_str(), "%lld", &c);

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"5 555", "8 195", "13 651"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "15"; long long Arg2 = 750LL; verify_case(0, Arg2, maximalCost(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"5 555", "8 195", "13 751"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "15"; long long Arg2 = 751LL; verify_case(1, Arg2, maximalCost(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"55 1562", "5 814", "55 1962", "8 996", "2 716", "34 1792"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "94"; long long Arg2 = 4568LL; verify_case(2, Arg2, maximalCost(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"13 89"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "1"; long long Arg2 = 0LL; verify_case(3, Arg2, maximalCost(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"27777890035288 9419696870097445", 
 "53316291173 6312623457097563", 
 "165580141 8848283653257131"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "27777900000000"; long long Arg2 = 15160907110354694LL; verify_case(4, Arg2, maximalCost(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        FibonacciKnapsack ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

