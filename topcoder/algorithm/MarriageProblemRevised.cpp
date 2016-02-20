// BEGIN CUT HERE
// PROBLEM STATEMENT
// There are several unmarried men and women living in a 
// society where marriage is defined as either one husband 
// with one or more wives, or one wife with one or more 
// husbands.  You are given a vector <string> preferences.  
// The j-th character of the i-th element of preferences is 
// '1' (one) if the i-th man and the j-th woman are willing 
// to be part of the same marriage, and '0' (zero) otherwise.
// 
// Your task is to group these people into the minimum 
// possible number of marriages.  Each person must be a 
// member of exactly one marriage, and each marriage must 
// contain only willing members.  Return the number of 
// marriages, or -1 if this is not possible.
// 
// DEFINITION
// Class:MarriageProblemRevised
// Method:neededMarriages
// Parameters:vector <string>
// Returns:int
// Method signature:int neededMarriages(vector <string> 
// preferences)
// 
// 
// CONSTRAINTS
// -preferences will contain between 1 and 12 elements, 
// inclusive.
// -The length of each element of preferences will be betwen 
// 1 and 12, inclusive.
// -All elements of preferences will be of the same length.
// -Each element of preferences will contain only '0' 
// (zeroes) and '1' (ones).
// 
// 
// EXAMPLES
// 
// 0)
// {"111"}
// 
// Returns: 1
// 
// Here, we have one man and three women, and everybody is 
// willing to be in the same marriage.  Therefore, we only 
// need one marriage.
// 
// 1)
// {"100", "010", "001"}
// 
// Returns: 3
// 
// 
// 
// 2)
// {"00", "00"}
// 
// Returns: -1
// 
// Nobody is willing to be in the same marriage as anybody 
// else, so there cannot be any marriages in this case.
// 
// 3)
// {"0001", "0001", "0001", "1111"}
// 
// Returns: 2
// 
// 
// 
// 4)
// {"11101011","00011110","11100100","01010000","01000010","
// 10100011","01110110","10111111"},
// 
// Returns: 3
// 
// 
// 
// END CUT HERE
#line 79 "MarriageProblemRevised.cpp"
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
#include <queue>    
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

int p[50][50];
int m,n;

map<pair<int, int>, int> mp;

    class MarriageProblemRevised
        { 
        public: 
					bool ok(queue<pair<int,int> > &bfs, pair<int,int> &st, int a, int b, int la, int lb) {
						fi(la) {
							if ((1<<i) & a) {
								VI will;
								fj(lb) {
									if (((la == m && p[i][j]) || (la == n && p[j][i])) && ((1<<j) & b)) {
										will.push_back(j);
									}
								}
								int mn = will.size();
								fj(1<<mn) {
									int na = a, nb = b;
									na &= ~(1<<i);
									f(k,0,mn){
										if ((1<<k) & j) {
											nb &= ~(1<<will[k]);
										}
									}
									if (na == 0 && nb ==0)
										return true;

									if (na == 0 || nb == 0) 
										continue;

									pair<int,int> nst(na,nb);
									if (mp.count(nst) > 0) continue;
									bfs.push(nst);
									mp[nst] = mp[st] + 1;
								}
							}
						}

						return false;
					}
        int neededMarriages(vector <string> pref) { 
							m = pref.size();
							n = pref[0].size();

							memset(p, 0, sizeof(p));
							fi(m) 
								fj(n)
								 p[i][j]  = pref[i][j] - '0';

							mp.clear();
							queue<pair<int,int> > bfs;
							pair<int,int> st((1<<m) - 1, (1<<n) - 1);
							bfs.push(st);
							mp[st] = 0;
							while (!bfs.empty()) {
								pair<int, int> t = bfs.front();
								bfs.pop();

								if (ok(bfs, t, t.first, t.second, m, n) ||
										ok(bfs, t, t.second, t.first, n, m)) {
									return mp[t] + 1;
								}
							}

							return -1;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, neededMarriages(Arg0)); }
	void test_case_1() { string Arr0[] = {"100", "010", "001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, neededMarriages(Arg0)); }
	void test_case_2() { string Arr0[] = {"00", "00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, neededMarriages(Arg0)); }
	void test_case_3() { string Arr0[] = {"0001", "0001", "0001", "1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, neededMarriages(Arg0)); }
	void test_case_4() { string Arr0[] = {"11101011","00011110","11100100","01010000","01000010","10100011","01110110","10111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(4, Arg1, neededMarriages(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MarriageProblemRevised ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

