// BEGIN CUT HERE
// PROBLEM STATEMENT
// Some sharks are having dinner and they are eating each 
// other. For every shark we know its size, speed and 
// intelligence (measured in positive integers). Shark A can 
// eat shark B if and only if A's size, speed and 
// intelligence are all greater than or equal to B's. Due to 
// digestive restrictions, each shark can eat at most two 
// other sharks.
// 
// Given vector <int> size, vector <int> speed and vector 
// <int> intelligence, return the minimum number of sharks 
// that will survive.
// 
// DEFINITION
// Class:SharksDinner
// Method:minSurvivors
// Parameters:vector <int>, vector <int>, vector <int>
// Returns:int
// Method signature:int minSurvivors(vector <int> size, 
// vector <int> speed, vector <int> intelligence)
// 
// 
// CONSTRAINTS
// -size, speed and intelligence will contain the same number 
// of elements.
// -size, speed and intelligence will each contain between 1 
// and 50 elements, inclusive.
// -Each element of size, speed and intelligence will be 
// between 1 and 2,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// { 1, 4, 3 }
// { 2, 3, 1 }
// { 1, 5, 2 }
// 
// Returns: 1
// 
// Shark 1 eats sharks 0 and 2 so we get 1 survivor.
// 
// 1)
// { 4, 10, 5, 8, 8 }
// { 5, 10, 7, 7, 10 }
// { 5, 8, 10, 7, 3 }
// 
// Returns: 2
// 
// Shark 2 eats shark 0, and shark 1 eats sharks 3 and 4.
// 
// 2)
// { 1, 2, 3, 4, 100 }
// { 4, 3, 2, 1, 100 }
// { 2, 4, 1, 3, 100 }
// 
// Returns: 3
// 
// The big shark eats two of the smaller sharks and is not 
// hungry anymore, so the other two of the smaller sharks are 
// lucky (and they cannot eat each other).
// 
// 3)
// { 4, 4, 4, 4 }
// { 3, 3, 3, 3 }
// { 8, 8, 8, 8 }
// 
// Returns: 1
// 
// Sharks with the same level of speed, size and intelligence 
// can eat each other.
// 
// END CUT HERE
#line 76 "SharksDinner.cpp"
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

bool eat[55][55];

bool done[55];

    class SharksDinner
        { 
        public: 
        int minSurvivors(vector <int> sz, vector <int> sp, vector <int> in) 
            { 
							memset(eat, 0, sizeof(eat));
							memset(done, 0, sizeof(done));
							int n = sz.size();
							fi(n) {
								fj(n) {
									if (j==i) continue;

									if (sz[i] >= sz[j] &&
											sp[i] >= sp[j] &&
											in[i] >= in[j]) eat[i][j] = true;
								}
							}

							vector<pair<int, int> > inc(n);
							fi(n) {
								int p = 0;
								fj(n) {
									if (i==j) continue;
									if (eat[j][i]) p++;
								}
								inc[i] = make_pair(p, i);
							}

							sort(inc.begin(), inc.end());

							int pos = 0;
							int ret = n;
							while (pos < inc.size()) {
								int sh = inc[pos].second;
								int co = 0;
								f(i,pos+1,inc.size()) {
									int ind = inc[i].second;
									if (eat[sh][ind] && !done[ind]) { done[ind] = 1; co++;}
									if (co == 2) break;
								}
								ret -= co;

								f(i, pos+1, inc.size()) {
									if (eat[sh][i]) inc[i].first--;
								}
								pos++;
								sort(inc.begin() + pos, inc.end());
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 1, 4, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 3, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 5, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, minSurvivors(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = { 4, 10, 5, 8, 8 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 5, 10, 7, 7, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 5, 8, 10, 7, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, minSurvivors(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = { 1, 2, 3, 4, 100 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 4, 3, 2, 1, 100 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 4, 1, 3, 100 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(2, Arg3, minSurvivors(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = { 4, 4, 4, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 3, 3, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 8, 8, 8, 8 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(3, Arg3, minSurvivors(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SharksDinner ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

