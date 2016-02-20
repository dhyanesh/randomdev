// BEGIN CUT HERE
// PROBLEM STATEMENT
// There is a number of people in a room, and each of them 
// wears a hat which is either black or white.
// Every person counts the number of other people wearing 
// white hats. You are given a vector <int> count, the i-th 
// element of which is the number counted by the i-th person. 
// Return the total number of people wearing white hats, or 
// -1 if count doesn't correspond to a valid situation.
// 
// 
// DEFINITION
// Class:WhiteHats
// Method:whiteNumber
// Parameters:vector <int>
// Returns:int
// Method signature:int whiteNumber(vector <int> count)
// 
// 
// CONSTRAINTS
// -count will contain between 2 and 50 elements, inclusive.
// -Each element of count will be between 0 and 50, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {2,1,1}
// 
// Returns: 2
// 
// The first person wears a black hat and sees two people 
// wearing white hats.  Each person wearing a white hat sees 
// only one other white hat in the room.
// 
// 1)
// {2,2,2}
// 
// Returns: 3
// 
// Everyone wears a white hat here.
// 
// 2)
// {0,0}
// 
// Returns: 0
// 
// Black hats only.
// 
// 3)
// {1,1,1,2}
// 
// Returns: -1
// 
// 
// 
// 4)
// {10,10}
// 
// Returns: -1
// 
// Now that's interesting.  There are only two people in the 
// room, yet each of them counted 10 others.
// 
// END CUT HERE
#line 67 "WhiteHats.cpp"
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

    class WhiteHats
        { 
        public: 
        int whiteNumber(vector <int> c) 
            { 
							int n = c.size();
							int low = *min_element(c.begin(), c.end());
							int high = *max_element(c.begin(), c.end());

							if (high - low > 1) return -1;

							int no = 0;
							fi(c.size()) {
								if (c[i] == high) {
									no++;
								}
							}

							if (low == high) {
								if (!low) return low;
								if (low != n-1) {
									return -1;
								}
								return high + 1;
							}

							if (no + high != n) {
								return -1;
							}


							return high;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, whiteNumber(Arg0)); }
	void test_case_1() { int Arr0[] = {2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, whiteNumber(Arg0)); }
	void test_case_2() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, whiteNumber(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, whiteNumber(Arg0)); }
	void test_case_4() { int Arr0[] = {10,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, whiteNumber(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        WhiteHats ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

