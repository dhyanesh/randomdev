// BEGIN CUT HERE
// PROBLEM STATEMENT
// We have an undirected graph where each vertex is either 
// black or white and has a mark, which is a non-negative 
// integer.  There are no edges that connect vertices of the 
// same color.  We are going to play a game with this graph.  
// The rules are simple:
// 
// White and black alternate turns.  The first turn is white.
// During a white turn, we set the mark of each black vertex 
// equal to the sum of the marks of all its neighbors. The 
// marks of the white vertices remain unchanged.
// During a black turn, we set the mark of each white vertex 
// equal to the sum of the marks of all its neighbors. The 
// marks of the black vertices remain unchanged.
// 
// You are to find the marks of all vertices after N turns.
// 
// You are given a vector <string> adj where the j-th 
// character of the i-th element is '1' (one) if there is an 
// edge between vertices i and j, and '0' (zero) otherwise.  
// You are given the coloring of the graph in the string 
// colors, the i-th element of which is the color of the i-th 
// vertex.  'W' denotes white and 'B' denotes black.  The 
// initial marks are given in the string marks, the i-th 
// element of which is a digit representing the initial mark 
// of the i-th vertex.
// 
// Return a vector <int> where the i-th element is the mark 
// of the i-th vertex modulo 10^9+7 after N turns.
// 
// 
// DEFINITION
// Class:GameOnAGraph
// Method:getMarks
// Parameters:vector <string>, string, string, int
// Returns:vector <int>
// Method signature:vector <int> getMarks(vector <string> 
// adj, string colors, string marks, int N)
// 
// 
// NOTES
// -If a vertex whose mark is being calculated has no 
// neighbors, its mark becomes zero.
// 
// 
// CONSTRAINTS
// -adj will contain between 1 and 50 elements, inclusive.
// -Each element of adj will contain exactly n characters, 
// where n is the number of elements in adj.
// -colors and marks will each contain exactly n characters, 
// where n is the number of elements in adj
// -Each element of adj will contain only the characters '0' 
// (zero) and '1' (one).
// -adj will be symmetric, i.e., adj[i][j] = adj[j][i], for 
// all possible i and j.
// -adj[i][i] will be equal to '0', for all possible i.
// -colors will contain only the characters 'W' and 'B'.
// -There will be no edges that connect vertices of the same 
// color.  In other words, for all possible i and j, where 
// colors[i] equals colors[j], adj[i][j] will be '0'.
// -marks will contain only digits ('0'-'9').
// -N will be between 1 and 10^9, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"0110","1000","1000","0000"}
// "WBBW"
// "1000"
// 1
// 
// Returns: {1, 1, 1, 0 }
// 
// In this case there is only one turn, so both black 
// vertices get their marks from the first white vertex.
// The marks of the white vertices remain unchanged.
// 
// 1)
// {"00000","00000","00000","00000","00000"}
// "BBWWW"
// "99999"
// 1
// 
// Returns: {0, 0, 9, 9, 9 }
// 
// There are no edges in this graph, so all black vertices 
// get their marks nullified.
// 
// 2)
// {"01","10"}
// "BW"
// "56"
// 2
// 
// Returns: {6, 6 }
// 
// After the first turn, the black vertex will have the same 
// mark as the white one. After that, both marks will always 
// be equal to 6.
// 
// 3)
// {"010101","101010","010101","101010","010101","101010"}
// "BWBWBW"
// "012345"
// 10
// 
// Returns: {59049, 177147, 59049, 177147, 59049, 177147 }
// 
// END CUT HERE
#line 113 "GameOnAGraph.cpp"
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

#define max 1000000007

typedef vector <int> VI;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   
typedef long long ll;

ll wmat[55][55];
ll bmat[55][55];
ll tmat[55][55];
ll temp[55][55];
ll mult[55][55];
ll final[55][55];
int n;
ll m[55];

void mul(ll one[][55], ll two[][55], ll out[][55]) {
	fi(n)
		fj(n) {
			out[i][j] = 0;
			f(k,0,n) {
				out[i][j] = (out[i][j] + (one[i][k] * two[k][j]) % max) % max;
			}
		}
}

    class GameOnAGraph
        { 
        public: 
        vector <int> getMarks(vector <string> adj, string colors, string marks, int N) 
            { 
							n = adj.size();

							fi(marks.size())
								m[i] = marks[i] - '0';

							memset(wmat, 0 , sizeof(wmat));
							memset(bmat, 0 , sizeof(bmat));
							memset(tmat, 0 , sizeof(tmat));

							fi(n)
								fj(n) {
									if (adj[i][j] == '1'){
										if (colors[i] == 'B') {
											wmat[j][i] = 1;
										}
										else {
											bmat[j][i] = 1;
										}
									}
								}

							fi(n) if (colors[i] == 'B') bmat[i][i] = 1; 
							else wmat[i][i] = 1;

							mul(wmat, bmat, tmat);

							int p = N / 2;

							memcpy(mult, tmat, sizeof(tmat));
							memset(final, 0 , sizeof(final));

							fi(n) final[i][i] = 1;

							while (p) {
								if (p & 1) {
									memcpy(temp, final, sizeof(final));
									mul(temp, mult, final);
								}
								memcpy(temp, mult, sizeof(temp));
								mul(temp, temp, mult);
								p >>= 1;
							}

							if (N % 2) {
								memcpy(temp, final, sizeof(final));
								mul(temp, wmat, final);
							}

							VI ret(n ,0);
							fi(n) {
								fj(n) {
									ret[i] = (ret[i] + (m[j] * final[j][i]) % max) % max;	
								}
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"0110","1000","1000","0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "WBBW"; string Arg2 = "1000"; int Arg3 = 1; int Arr4[] = {1, 1, 1, 0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, getMarks(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"00000","00000","00000","00000","00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "BBWWW"; string Arg2 = "99999"; int Arg3 = 1; int Arr4[] = {0, 0, 9, 9, 9 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, getMarks(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"01","10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "BW"; string Arg2 = "56"; int Arg3 = 2; int Arr4[] = {6, 6 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, getMarks(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"010101","101010","010101","101010","010101","101010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "BWBWBW"; string Arg2 = "012345"; int Arg3 = 10; int Arr4[] = {59049, 177147, 59049, 177147, 59049, 177147 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(3, Arg4, getMarks(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        GameOnAGraph ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

