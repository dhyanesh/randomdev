// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Several boxes are placed in a row. Each box is one of 
// three colors. We want to rearrange these boxes in a such 
// way that no three consecutive boxes are of the same color. 
// This process should affect the fewest boxes possible. More 
// formally, we want to achieve the desired configuration by 
// swapping pairs of boxes, and we want to maximize the 
// number of boxes that are never moved.
// 
// You will be given a string boxes which describes the 
// colors of the boxes. Colors are given as characters 'A', 
// 'B' and 'C' respectively. Rearrange the boxes as described 
// above and return the maximum possible number of boxes that 
// are never moved. Return -1 if it is not possible to 
// achieve the desired configuration.
// 
// 
// DEFINITION
// Class:BoxesArrangement
// Method:maxUntouched
// Parameters:string
// Returns:int
// Method signature:int maxUntouched(string boxes)
// 
// 
// CONSTRAINTS
// -boxes will contain between 1 and 50 characters, inclusive. 
// -boxes will consist of characters 'A', 'B' and 'C' only. 
// 
// 
// EXAMPLES
// 
// 0)
// "AAABBBCCC"
// 
// Returns: 6
// 
// The boxes could be rearranged into "ABABCBCAC".
// 
// 1)
// "AAAAAAAACBB"
// 
// Returns: 7
// 
// The best rearangement is "AABAABAACAA".
// 
// 2)
// "CCCCCB"
// 
// Returns: -1
// 
// 3)
// "BAACAABAACAAA"
// 
// Returns: 5
// 
// 4)
// "CBBABA"
// 
// Returns: 6
// 
// 
// 
// END CUT HERE
#line 68 "BoxesArrangement.cpp"
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

    class BoxesArrangement
        { 
        public: 
        int maxUntouched(string box) 
            { 
							VI tomove;
							char c=box[0];
							int co=1;
							f(i, 1,box.size()) {
								if (c==box[i]) {
									co++;

									if (co >=3) {

									}
								}
							}
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "AAABBBCCC"; int Arg1 = 6; verify_case(0, Arg1, maxUntouched(Arg0)); }
	void test_case_1() { string Arg0 = "AAAAAAAACBB"; int Arg1 = 7; verify_case(1, Arg1, maxUntouched(Arg0)); }
	void test_case_2() { string Arg0 = "CCCCCB"; int Arg1 = -1; verify_case(2, Arg1, maxUntouched(Arg0)); }
	void test_case_3() { string Arg0 = "BAACAABAACAAA"; int Arg1 = 5; verify_case(3, Arg1, maxUntouched(Arg0)); }
	void test_case_4() { string Arg0 = "CBBABA"; int Arg1 = 6; verify_case(4, Arg1, maxUntouched(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BoxesArrangement ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

