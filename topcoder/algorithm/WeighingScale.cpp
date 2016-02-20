// BEGIN CUT HERE
// PROBLEM STATEMENT
// Little George has found an old-fashioned balance scale and 
// a set of weights in the attic. The scale has two weighing 
// pans and it allows you to check if the content of the left 
// pan is heavier, lighter, or the same weight as the content 
// of the right pan. The box where the weights were kept says 
// that each of them weigh 10, 20, or 30 grams, but the faded 
// paint makes it impossible to tell which is which.
// George started playing with the scale by comparing one 
// weight against another, and noting down all his results. 
// After a while he got bored with that, and came up with a 
// new experiment. He put the A-th and B-th weights on the 
// left pan and tried to guess what would happen when he put 
// another two weights on the right pan.
// You are given a vector <string> measures with the results 
// of the previous experiments. The j-th character of the i-
// th element represents the result of comparing the i-th 
// weight against the j-th weight, and it can have one of 
// four values:
// 
// '+' - the i-th weight is heavier than the j-th weight.
// '-' - the i-th weight is lighter than the j-th weight.
// '=' - both weights have the same weight.
// '?' - the two weights weren't compared.
// 
// Return a vector <int> containing exactly three integers in 
// the following order: the number of different pairs of 
// weights you can put on the right pan to make it lighter 
// than the left pan, the number of pairs to make both pans 
// the same weight, and the number of pairs to make the left 
// pan lighter.  Two pairs of weights are different if one 
// pair contains at least one weight with an index that's not 
// contained in the other pair. You should only consider the 
// pairs that make the result unambiguously predictable based 
// on the results in measures.
// 
// DEFINITION
// Class:WeighingScale
// Method:count
// Parameters:vector <string>, int, int
// Returns:vector <int>
// Method signature:vector <int> count(vector <string> 
// measures, int A, int B)
// 
// 
// NOTES
// -Since the weights with indices A and B are already on the 
// left pan you should only consider pairs that contain 
// neither A nor B for the right pan.
// 
// 
// CONSTRAINTS
// -measures will contain between 4 and 50 elements, inclusive.
// -Each element of measures will contain exactly N 
// characters, where N is the number of elements in measures.
// -Each element of measures will contain only '+','-', '=', 
// or '?'.
// -The i-th character of the i-th element of measures will 
// be '?'
// -If the j-th character of the i-th element of measures is 
// '+' than the i-th character of the j-th element will be 
// '-' and vice versa.
// -If the j-th character of the i-th element of measures is 
// '=' or '?' than the i-th character of the j-th element 
// will be the same.
// -There will exist at least one way to assign values to the 
// weights that will match the results in measures.
// -A will be between 0 and N-1, inclusive, where N is the 
// number of elements in measures.
// -B will be between 0 and N-1, inclusive, where N is the 
// number of elements in measures.
// -A will be different than B.
// 
// 
// EXAMPLES
// 
// 0)
// {"?+????","-?+???","?-????","????+?", "???-?+","????-?"}
// 1
// 4
// 
// Returns: {1, 4, 1 }
// 
// We have the following weight relations:
// w0 > w1 > w2
// w3 > w4 > w5
// It can only be true if the values are (30,20,10,30,20,10). 
// The left pan contains weights 1 and 4 with total weight
//  20+20=40.
// There is one pair (0,3) heavier than that, one pair (2,5) 
// lighter than that and the remaining four pairs have the 
// same weight.
// 
// 1)
// {"?+?????","-?+????","?-?????","????+??", "???-?+?","????-
// ??", "???????"}
// 0
// 3
// 
// Returns: {10, 0, 0 }
// 
// The first six weights are the same as in example 0 
// (30,20,10,30,20,10). We know nothing about the 7th weight, 
// but still,  putting the two 30 gram weights on the left 
// pan assures that it will be heavier than any other pair.
// 
// 2)
// {"?+?????","-?+????","?-?????","????+??", "???-?+?","????-
// ??", "???????"}
// 1
// 4
// 
// Returns: {1, 4, 1 }
// 
// With the same measures as in the previous example, now 
// weights 1 and 4 lie on the left pan, for a total weight of 
// 40. We can predict what will happen only if the pair on 
// the right pan doesn't contain the 7th weight; otherwise 
// it's impossible to tell.
// 
// 3)
// {"??+?", "???+", "-???", "?-??"}
// 0
// 1
// 
// Returns: {1, 0, 0 }
// 
// We know that w0 > w2 and w1 > w3 thus w0+w1 must be 
// heavier than w2+w3.
// 
// 4)
// {"??+??", "???+?", "-???=", "?-???", "??=??"}
// 0
// 1
// 
// Returns: {3, 0, 0 }
// 
// 
// 
// 5)
// {"?+???++?????++","-??=?=???????=","??????????=???","?=??+?
// ==??????",
// "???-???-???-??","-=????????????","-??=???=?-+???","???=+?
// =???????",
// "??????????????","??????+???????","??=???-????-??","????
// +?????+???",
// "-?????????????","-=????????????"}
// 6
// 2
// 
// Returns: {1, 10, 36 }
// 
// 
// 
// END CUT HERE
#line 158 "WeighingScale.cpp"
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

bool wts[55][3];

    class WeighingScale
        { 
        public: 
        vector <int> count(vector <string> m, int A, int B) 
            { 
							int n = m.size();

							memset(wts,1,sizeof(wts));

							fi(n) {
								fj(n) {
									f(k,0,n) {
										if (m[j][k]=='=') {
											f(p,0,n) {
												if (m[j][p] == '?') m[j][p] = m[k][p];
												if (m[k][p] == '?') m[k][p] = m[j][p];
											}
										}
									}
								}
							}

							queue<int> bfs;
							fi(n) {
								fj(n) {
									if (m[i][j] == '+') {
										wts[i][0] = false;
										wts[j][2] = false;
									}
									if (m[i][j] == '-') {
										wts[i][2] = false;
										wts[j][0] = false;
									}
								}
							}

							fi(n) {
								fj(n) {
									if (m[i][j]=='=') {
										f(k,0,3) {
											if (!wts[i][k]) wts[i][k] = wts[j][k];
											if (!wts[j][k]) wts[j][k] = wts[i][k];
										}
									}
								}
							}

							fi(n) {
								fj(n) {
									if (m[i][j] == '+') {
										if (wts[j][1] && !wts[j][0]) { 
											wts[i][1] = false;
											wts[i][0] = false;
										}
									}
									if (m[i][j] == '-') {
										if (wts[j][1] && !wts[j][2]) {
											wts[i][1] = false;
											wts[i][2] = false;
										}
									}
								}
							}

							VI wt(n,-1);
							fi(n) {
								int t = -1;
								fj(3) {
									if (wts[i][j]) {
										if (t!=-1) { t = -1; break; }
										t = j;
									}
								}
								wt[i] = t;
							}

							
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"?+????","-?+???","?-????","????+?", "???-?+","????-?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; int Arr3[] = {1, 4, 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"?+?????","-?+????","?-?????","????+??", "???-?+?","????-??", "???????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 3; int Arr3[] = {10, 0, 0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"?+?????","-?+????","?-?????","????+??", "???-?+?","????-??", "???????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; int Arr3[] = {1, 4, 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"??+?", "???+", "-???", "?-??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arr3[] = {1, 0, 0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"??+??", "???+?", "-???=", "?-???", "??=??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arr3[] = {3, 0, 0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"?+???++?????++","-??=?=???????=","??????????=???","?=??+?==??????",
"???-???-???-??","-=????????????","-??=???=?-+???","???=+?=???????",
"??????????????","??????+???????","??=???-????-??","????+?????+???",
"-?????????????","-=????????????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 2; int Arr3[] = {1, 10, 36 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        WeighingScale ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

