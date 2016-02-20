// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are a prisoner and you want to escape from your jail.  
// The jail is a grid where each square is either free or 
// impassible.  There are one or more exits located in free 
// squares.  You are initially standing in a free square and 
// your goal is to reach one of the exits.  Unfortunately, 
// your eyes are covered, so you cannot see where you're 
// going.  Each time you move, you check up, down, left and 
// right to see which of those four adjacent squares are 
// free, and you randomly walk to one of the free squares.  
// You continue to do this until you land on a square 
// containing an exit. If there is no adjacent free cell, you 
// stay at your current position.
// 
// You are given a vector <string> jail, where your start 
// location is marked by the '@' character, impassible 
// squares are marked with '#', exits are marked with '$' and 
// all other free squares are '.'.  Return a double 
// representing the expected number of moves required to 
// escape.  If it is impossible to escape, return -1.
// 
// DEFINITION
// Class:EscapeTheJail
// Method:findExit
// Parameters:vector <string>
// Returns:double
// Method signature:double findExit(vector <string> jail)
// 
// 
// CONSTRAINTS
// -jail will contain between 1 and 15 elements, inclusive.
// -Each element of jail will contain between 1 and 15 
// characters, inclusive.
// -All elements in jail will contain the same number of 
// characters.
// -Each character in each element of jail will be '.', '#', 
// '$' or '@'.
// -jail will contain exactly one '@' character.
// -jail will contain at least one '$' character.
// 
// 
// EXAMPLES
// 
// 0)
// {"@$"}
// 
// Returns: 1.0
// 
// You have only one possible move, and it leads you to the 
// exit. So, the answer is 1.
// 
// 1)
// {"$.",
//  ".@"}
// 
// Returns: 4.0
// 
// 
// 
// 2)
// {"@..$"}
// 
// Returns: 9.0
// 
// 
// 
// 3)
// {"@#",
//  "#$"}
// 
// Returns: -1.0
// 
// 
// 
// END CUT HERE
#line 78 "EscapeTheJail.cpp"
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

    class EscapeTheJail
        { 
        public: 
        double findExit(vector <string> jail) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"@$"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, findExit(Arg0)); }
	void test_case_1() { string Arr0[] = {"$.",
 ".@"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 4.0; verify_case(1, Arg1, findExit(Arg0)); }
	void test_case_2() { string Arr0[] = {"@..$"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 9.0; verify_case(2, Arg1, findExit(Arg0)); }
	void test_case_3() { string Arr0[] = {"@#",
 "#$"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = -1.0; verify_case(3, Arg1, findExit(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        EscapeTheJail ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

