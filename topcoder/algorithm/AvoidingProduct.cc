// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are given a set A of integers and a positive integer 
// n. You must find positive integers x, y and z such that 
// their product is as close to n as possible (minimize |n - 
// x * y * z|), and none of them belongs to A. If there are 
// several such triples, find the one with the smallest x. If 
// there are still several such triples, minimize y. If there 
// is still a tie, minimize z.
// 
// 
// You are given the elements of A as a vector <int> a. 
// Return a vector <int> with exactly three elements: x, y 
// and z, in this order.
// 
// 
// DEFINITION
// Class:AvoidingProduct
// Method:getTriple
// Parameters:vector <int>, int
// Returns:vector <int>
// Method signature:vector <int> getTriple(vector <int> a, 
// int n)
// 
// 
// CONSTRAINTS
// -a will contain between 0 and 50 elements, inclusive.
// -Each element of a will be between 1 and 1000, inclusive.
// -All elements of a will be distinct.
// -n will be between 1 and 1000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {2,4}
// 4
// 
// Returns: {1, 1, 3 }
// 
// You can get 3=1*1*3 and 5=1*1*5. 3 is better.
// 
// 1)
// {1}
// 10
// 
// Returns: {2, 2, 2 }
// 
// 
// 
// 2)
// {1,2}
// 10
// 
// Returns: {3, 3, 3 }
// 
// 
// 
// 3)
// {1,3}
// 12
// 
// Returns: {2, 2, 2 }
// 
// 
// 
// 4)
// {1,3}
// 13
// 
// Returns: {2, 2, 4 }
// 
// 
// 
// 5)
// {1,15}
// 90
// 
// Returns: {2, 5, 9 }
// 
// 
// 
// END CUT HERE
#line 86 "AvoidingProduct.cc"
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

bool done[1005];

    class AvoidingProduct
        { 
        public: 
        vector <int> getTriple(vector <int> a, int n) 
            { 
              memset(done, 0, sizeof(done));
              ll best = 1LL<<40;
              VI ret(3);
              fi(a.size()) done[a[i]] = true;
              f(i,1,1002) {
                if (done[i]) continue;
                f(j,i,1002) {
                  if (done[j]) continue;
                 f(k,j,1002) {
                   if (done[k]) continue;
                   
                   ll t = (long long)n - i * j * (long long) k;
                   if (t < 0) t = - t;
                   if (t < best) {
                     best = t;
                     ret[0] = i;
                     ret[1] = j;
                     ret[2] = k;
                   }
                 }
                }
              }
                  
              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arr2[] = {1, 1, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getTriple(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arr2[] = {2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getTriple(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arr2[] = {3, 3, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getTriple(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arr2[] = {2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getTriple(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; int Arr2[] = {2, 2, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getTriple(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 90; int Arr2[] = {2, 5, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, getTriple(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        AvoidingProduct ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

