// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are organizing a dance party.  The party will be 
// attended by n boys and n girls.  There will be several 
// rounds of dancing.
// 
// 
// In each round, you divide the guests into n dancing 
// pairs.  Each guest must be in exactly one pair, and each 
// pair must contain one boy and one girl.  Each boy must 
// dance with a different girl in every round.  Some boys and 
// girls like each other and some do not.  During the party, 
// each boy agrees to dance with at most k girls he doesn't 
// like.  Similarly, each girl agrees to dance with at most k 
// boys she doesn't like.
// 
// 
// You are given a vector <string> likes.  The j-th character 
// of likes[i] is 'Y' if the i-th boy and the j-th girl like 
// each other, and 'N' if they don't.  Return the maximum 
// number of rounds you can organize.
// 
// 
// 
// DEFINITION
// Class:DancingParty
// Method:maxDances
// Parameters:vector <string>, int
// Returns:int
// Method signature:int maxDances(vector <string> likes, int k)
// 
// 
// CONSTRAINTS
// -likes will contain between 1 and 50 elements, inclusive.
// -Each element of likes will contain exactly n characters, 
// where n is the number of elements in likes.
// -Each element of likes will contain only the characters 
// 'Y' and 'N'.
// -k will be between 0 and 50, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"YYY", "YYY", "YYY"}
// 0
// 
// Returns: 3
// 
// Every boy likes every girl, so you can organize 3 rounds.
// 
// 1)
// {"YYY", "YYN", "YNY"}
// 0
// 
// Returns: 2
// 
// For example, you can have one round with pairs 1-2, 2-1 
// and 3-3 and one round with pairs 1-3, 2-2 and 3-1.
// 
// 2)
// {"YN", "YN"}
// 0
// 
// Returns: 0
// 
// The second girl doesn't like anybody.
// 
// 3)
// {"YN", "YN"}
// 1
// 
// Returns: 1
// 
// The second girl doesn't like anybody again, but this time 
// she agrees to dance with someone she doesn't like once.
// 
// END CUT HERE
#line 81 "DancingParty.cc"
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

    class DancingParty
        { 
        public: 
        int maxDances(vector <string> likes, int k) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"YYY", "YYY", "YYY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 3; verify_case(0, Arg2, maxDances(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YYY", "YYN", "YNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; verify_case(1, Arg2, maxDances(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"YN", "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; verify_case(2, Arg2, maxDances(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"YN", "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; verify_case(3, Arg2, maxDances(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        DancingParty ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

