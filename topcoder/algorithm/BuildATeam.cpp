// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Several people want to play hockey, so they use the 
// following algorithm to split themselves into teams. First, 
// there are teams captains, numbered from 1 to teams. 
// 
// The captains select players for their teams, always trying 
// to pick the strongest player who hasn't been picked yet.
// The draft process is split into several rounds, which are 
// enumerated starting from 1. Captain 1 starts round 1 of 
// the draft by picking the strongest available player, 
// followed by captain 2 and all other captains in order of 
// ascending indices. When captain teams makes his pick, 
// round 1 is over. If not all the players were picked, the 
// draft continues with round 2. In round 2, all captains 
// make their picks in the reverse order - so captain teams 
// starts the round, and captain 1 ends it. Rounds 3, 5 and 
// all other rounds with odd numbers go similar to round 1, 
// while all rounds with even numbers go similar to round 2. 
// For example, if there are 4 captains, they'll pick players 
// in the following order: 1, 2, 3, 4, 4, 3, 2, 1, 1, 2, 3, 
// ... The draft is over when all players are picked. 
// 
// 
// You will be given a vector <int> skills, representing the 
// skills of all players. Also you will be given an int teams 
// - the number of teams which must be created. You are to 
// simulate the draft process and return the maximal team 
// strength among all the teams. The strength of a team is 
// the sum of the skills of all its players.
// 
// 
// DEFINITION
// Class:BuildATeam
// Method:maximalStrength
// Parameters:vector <int>, int
// Returns:int
// Method signature:int maximalStrength(vector <int> skills, 
// int teams)
// 
// 
// CONSTRAINTS
// -skills will contain between 2 and 50 elements, inclusive.
// -Each element of skills will be between 1 and 100, 
// inclusive.
// -teams will be between 2 and 50, inclusive.
// -The number of elements in skills will be an integer 
// multiple of teams.
// 
// 
// EXAMPLES
// 
// 0)
// {10, 9, 7, 3, 3, 2}
// 3
// 
// Returns: 12
// 
// The players will be split into the following teams:
// 
// Team      1    2   3
// Round 1   10   9   7 
// Round 2   2    3   3 
// 
// 
// Teams 1 and 2 both have a strength of 12, while team 3 has 
// a strength of 10.
// 
// 1)
// {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
// 4
// 
// Returns: 21
// 
// Team 1 has the maximal strength of 12 + 5 + 4 = 21.
// 
// 2)
// {10, 10, 10, 9, 8, 8, 3, 1}
// 2
// 
// Returns: 31
// 
// Players 1, 4, 5 and 8 (with strengths of 10, 9, 8 and 1) 
// go to team 1, while the other four players (with strengths 
// of 10, 10, 8 and 3) go to team 2.  The total strength of 
// team 1 is 28, and the total strength of team 2 is 31.
// 
// 3)
// {10, 8, 10, 1, 10, 9, 3, 8}
// 2
// 
// Returns: 31
// 
// The same people as in example 2, but placed in another 
// order.
// 
// 4)
// {98, 19, 11, 11, 11, 11, 23, 55, 1, 4, 3, 4, 6, 8}
// 7
// 
// Returns: 99
// 
// 
// 
// END CUT HERE
#line 108 "BuildATeam.cpp"
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

    class BuildATeam
        { 
        public: 
        int maximalStrength(vector <int> sk, int teams) 
            { 
							int cu = 0;
							int dx = 1;
							bool f = true;
							VI t(teams, 0);
							while (sk.size()) {
								VI::iterator itr = max_element(sk.begin(), sk.end());
								t[cu] += *itr;
								sk.erase(itr);
								if (f) {
									cu += dx;
									f = false;
								} else if (cu == teams - 1 || cu == 0) {
									dx *= -1;
									f = true;
								} else {
									cu += dx;
									f = false;
								}
							}

							return *max_element(t.begin(), t.end());
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 9, 7, 3, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 12; verify_case(0, Arg2, maximalStrength(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 21; verify_case(1, Arg2, maximalStrength(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {10, 10, 10, 9, 8, 8, 3, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 31; verify_case(2, Arg2, maximalStrength(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {10, 8, 10, 1, 10, 9, 3, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 31; verify_case(3, Arg2, maximalStrength(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {98, 19, 11, 11, 11, 11, 23, 55, 1, 4, 3, 4, 6, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 99; verify_case(4, Arg2, maximalStrength(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BuildATeam ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

