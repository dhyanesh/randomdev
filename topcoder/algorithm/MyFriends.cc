// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 	There is a group of n kids, numbered 0 through n-1, where 
// n is an odd number.  
// 	Each kid has some friends within the group, and each kid 
// knows how many friends each of the other kids has.  
// 	Friendship is symmetric, so if kid 0 is a friend of kid 
// 1, then kid 1 is a friend of kid 0.  Each kid i also 
// 	supports exactly one other kid (i+k) % n, not necessarily 
// a friend.
// 
// 
// 
// 	You ask each kid to answer the following question:  
// Consider each kid in the 
// 	group except yourself and the kid you support.  What is 
// the sum of the number of friends each of them has?  
// 	For example, if you ask kid 0 this question, and kid 0 
// supports kid 1, 
// 	he should tell you (the number of friends kid 2 has) + 
// (the number of friends kid 3 has) + ... + 
// 	(the number of friends kid n-1 has).
// 
// 
// 
// 	You are given a vector <int> sumFriends, where the i-th 
// element (0-indexed) is the answer given to 
// 	you by kid i. Some of the kids might not be telling the 
// truth (they are just kids, forgive them). 
// 	Return "IMPOSSIBLE" if it is impossible for all the given 
// answers to be accurate. Otherwise, return 
// 	"POSSIBLE" (all quotes for clarity).
// 
// 
// 
// DEFINITION
// Class:MyFriends
// Method:calcFriends
// Parameters:vector <int>, int
// Returns:string
// Method signature:string calcFriends(vector <int> 
// sumFriends, int k)
// 
// 
// CONSTRAINTS
// -sumFriends will contain odd number of elements.
// -sumFriends will contain between 3 and 49 elements, 
// inclusive.
// -Each element of sumFriends will be between 0 and 9999, 
// inclusive.
// -k will be between 1 and (number of elements in sumFriends)
// -1, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {8, 9, 8, 8, 9}
// 2
// 
// Returns: "POSSIBLE"
// 
// We can get such sums only if kid 1 has 2 friends and all 
// other kids have 3 friends. Such a situation is possible. 
// For example:
// 
// Kid             His/her friends
// 0               1, 3, 4
// 1               0, 2
// 2               1, 3, 4
// 3               0, 2, 4
// 4               0, 2, 3
// 
// 
// 1)
// {7, 6, 5, 4, 4}
// 2
// 
// Returns: "IMPOSSIBLE"
// 
// 
// 
// 2)
// {5, 6, 5, 4, 4}
// 1
// 
// Returns: "POSSIBLE"
// 
// 
// 
// 3)
// {1, 2, 3}
// 1
// 
// Returns: "IMPOSSIBLE"
// 
// Here kid 2 supports kid 0, so he tells us the number of 
// friends of kid 1. But it's obviously impossible for kid 1 
// to have 3 friends.
// 
// END CUT HERE
#line 104 "MyFriends.cc"
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

string ret[2] = { "POSSIBLE", "IMPOSSIBLE" };

VVI mat;

    class MyFriends
        { 
        public: 
        string calcFriends(vector <int> sf, int k) 
            { 
              int n = sf.size();

              mat.resize(55);
              fi(n) mat[i].resize(n);

              fi(n) {
                fj(n) {
                  if (j == i || j == ( i + k ) % n) mat[i][j] = 0;
                  else mat[i][j] = 1;
                }
              }

              fi(n) {
                int p = -1;
                int curr = 1<<20;
                f(j, i, n) {
                  if (abs(mat[j][i]) < curr && mat[j][i] != 0){
                    p = j;
                    curr = abs(mat[j][i]);
                  }
                }

                if (i!=p) {
                  swap(mat[i],mat[p]);
                  swap(sf[i],sf[p]);
                }

                int div = mat[i][i];
                  f(k,0,n) {
                    if (mat[i][k] % div != 0) return ret[1];
                    mat[i][k] /= div;
                  }
                  if (sf[i] % div != 0 ) return ret[1];
                  sf[i] /= div;


                f(j,i+1,n) {
                  int sc = mat[j][i] / mat[i][i];
                  f(k,0,n) {
                    mat[j][k] -= sc * mat[i][k];
                  }
                  sf[j] -= sc * sf[i];
                }
              }

              fi(n) {
                fj(n) cout << mat[i][j] << " ";
                cout << endl;
              }
              fi(n) {
                cout << sf[i] << " ";
              }
                cout << endl;

              VI sol(n);

              for(int i=n-1; i >=0; --i) {
                sol[i] = sf[i];
                f(j,i+1,n)
                  sol[i] -= mat[i][j] * sol[j];
                if (sol[i] % mat[i][i] != 0) return ret[1];
                sol[i] /= mat[i][i];
                if (sol[i] < 0) return ret[1];
              }

              return ret[0];
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {8, 9, 8, 8, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; string Arg2 = "POSSIBLE"; verify_case(0, Arg2, calcFriends(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {7, 6, 5, 4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; string Arg2 = "IMPOSSIBLE"; verify_case(1, Arg2, calcFriends(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {5, 6, 5, 4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; string Arg2 = "POSSIBLE"; verify_case(2, Arg2, calcFriends(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; string Arg2 = "IMPOSSIBLE"; verify_case(3, Arg2, calcFriends(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MyFriends ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

