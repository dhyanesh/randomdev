// BEGIN CUT HERE
// PROBLEM STATEMENT
// To obtain the reverse of a number, write it backwards from 
// right to left.  For example, the reverse of 1234 is 4321, 
// and the reverse of 100 is 1 (leading zeroes are always 
// ignored). Return the smallest non-negative number x, such 
// that the difference x - reverse(x) is equal to 
// difference.  If no such number exists, return "NONE" 
// (quotes for clarity) instead.
// 
// DEFINITION
// Class:ReverseDistance
// Method:find
// Parameters:int
// Returns:string
// Method signature:string find(int difference)
// 
// 
// CONSTRAINTS
// -difference will be between 1 and 1000000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 18
// 
// Returns: "20"
// 
// 20 - 2 = 18.
// 18 can be also achieved in other ways like 42 - 24, but 20 
// is the smallest possible number.
// 
// 1)
// 15
// 
// Returns: "NONE"
// 
// It's impossible to find a number with a difference of 15.
// 
// 2)
// 4275
// 
// Returns: "5080"
// 
// 5080 - 805 = 4275
// 
// 3)
// 900
// 
// Returns: "101001"
// 
// 101001 - 100101 = 900
// 
// 4)
// 1989
// 
// Returns: "100990"
// 
// 100990 - 99001 = 1989
// 
// 5)
// 857232
// 
// Returns: "860300"
// 
// 860300 - 3068 = 857232
// 
// 6)
// 45
// 
// Returns: "50"
// 
// 
// 
// END CUT HERE
#line 78 "ReverseDistance.cpp"
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

    class ReverseDistance
        { 
        public: 
        string find(int difference) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 18; string Arg1 = "20"; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { int Arg0 = 15; string Arg1 = "NONE"; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { int Arg0 = 4275; string Arg1 = "5080"; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { int Arg0 = 900; string Arg1 = "101001"; verify_case(3, Arg1, find(Arg0)); }
	void test_case_4() { int Arg0 = 1989; string Arg1 = "100990"; verify_case(4, Arg1, find(Arg0)); }
	void test_case_5() { int Arg0 = 857232; string Arg1 = "860300"; verify_case(5, Arg1, find(Arg0)); }
	void test_case_6() { int Arg0 = 45; string Arg1 = "50"; verify_case(6, Arg1, find(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ReverseDistance ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

