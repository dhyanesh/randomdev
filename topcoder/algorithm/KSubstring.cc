// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 	You are given numbers A0, X, Y, M and n. 
// 	Generate a list A of length n using the following 
// recursive definition:
// 	A[0] = A0
// 	A[i] = (A[i - 1] * X + Y) MOD M (note that A[i - 1] * X + 
// Y may overflow 32-bit integer)
// 
// 
// 
// 	Let s(i, k) be a sum of k consecutive elements of the 
// list A starting with the element at
// 	position i (0 indexed).
// 	More formally, s(i, k) = A[i] + A[i + 1] + ... + A[i + k 
// - 1].
// 	
// 	Your task is to find the smallest difference between s(i, 
// k) and s(j, k) 
// 	(where difference is defined as abs(s(i, k) - s(j, k))) 
// such that
// 	i + k <= j. 
// 	In other words, you must find the smallest difference 
// between two subsequences of the same 
// 	length that do not overlap.
// 	Call this smallest difference val, and return a vector 
// <int> containing exactly two elements.
// 	The first element should be k, and the second element 
// should be val.
// 	If there are multiple solutions with the same val, return 
// the one among them with the highest k.
// 
// 
// 
// DEFINITION
// Class:KSubstring
// Method:maxSubstring
// Parameters:int, int, int, int, int
// Returns:vector <int>
// Method signature:vector <int> maxSubstring(int A0, int X, 
// int Y, int M, int n)
// 
// 
// CONSTRAINTS
// -M will be between 1 and 1,000,000,000, inclusive.
// -A0 will be between 0 and M-1, inclusive.
// -X will be between 0 and M-1, inclusive.
// -Y will be between 0 and M-1, inclusive.
// -n will be between 2 and 3,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 5
// 3
// 4
// 25
// 5
// 
// Returns: {2, 1 }
// 
// The elements of the list are {5, 19, 11, 12, 15}. There is 
// no way to find two subsequences that have equal sums and 
// do not overlap, so there is no way to obtain 0 as a 
// difference. |s(0, 2) - s(2, 2)| = 1 and that is the 
// minimal difference. Note that |s(2, 1) - s(3, 1)| is also 
// 1, but we don't choose these subsequences because they 
// have a lower value for k.
// 
// 1)
// 8
// 19
// 17
// 2093
// 12
// 
// Returns: {5, 161 }
// 
// The elements of the list are {8, 169, 1135, 652, 1940, 
// 1296, 1618, 1457, 491, 974, 1779, 330}. The smallest 
// difference is |s(1, 5) - s(7, 5)| = 161.
// 
// 2)
// 53
// 13
// 9
// 65535
// 500
// 
// Returns: {244, 0 }
// 
// 
// 
// 3)
// 12
// 34
// 55
// 7890
// 123
// 
// Returns: {35, 4 }
// 
// 
// 
// END CUT HERE
#line 109 "KSubstring.cc"
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
typedef vector <long long > VL;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   
typedef long long ll;

ll mat[2][3003];
ll t[3003];

    class KSubstring
        { 
        public: 
          int findmin(ll arr[], int k, int n){ 
            vector<pair<ll,ll> > t(n);
            fi(n) {
              t[i].first = arr[i];
              t[i].second = i;
            }
            sort(t.begin(), t.end());
            int min = 1<<30;
            for (int i = 0; i < n; ++i) {
              int l = i + 1;
              int h = n;
              while (l < h) {
                int m = (l+h) / 2;
                if (abs(t[i].second - t[m].second) >= k) {
                  h = m;
                } else {
                }
              }
              f(j,i+1,n) {
                if (abs(t[i].second - t[j].second) >= k) {
                  min <?= abs(t[i].first - t[j].first);
                  break;
                }
              }
            }
            return min;
          }

        vector <int> maxSubstring(int A0, int X, int Y, int M, int n) 
            { 
              VL a(n);
              a[0] = A0;

              f(i,1,n) {
                a[i] = (a[i-1] * X + Y) % M;
              }

              fi(n) {
                mat[0][i] = a[i];
              }

              VI ret(2);
              ret[0] = 1;
              ret[1] = findmin(mat[0],1,n);

              int ne = 1;
              f(i,2,n) {
                fj(n-i+1) {
                  mat[ne][j] = mat[1-ne][j] + a[j + i - 1];
                }
                int p = findmin(mat[ne], i, n - i + 1);
                if (p<=ret[1]) { ret[0] = i; ret[1] = p; }
                ne = 1 - ne;
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 4; int Arg3 = 25; int Arg4 = 5; int Arr5[] = {2, 1 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, maxSubstring(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 8; int Arg1 = 19; int Arg2 = 17; int Arg3 = 2093; int Arg4 = 12; int Arr5[] = {5, 161 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, maxSubstring(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 53; int Arg1 = 13; int Arg2 = 9; int Arg3 = 65535; int Arg4 = 500; int Arr5[] = {244, 0 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, maxSubstring(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 12; int Arg1 = 34; int Arg2 = 55; int Arg3 = 7890; int Arg4 = 123; int Arr5[] = {35, 4 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, maxSubstring(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        KSubstring ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

