// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 
// 
// Several people want to play hockey, so they use the 
// following algorithm to split themselves into teams.  There 
// are teams captains, numbered from 1 to teams, who select 
// players for their respective teams.  The draft process is 
// split into several rounds, which are enumerated starting 
// from 1.  Captain 1 starts round 1 of the draft by picking 
// a single player, followed by captain 2 and all the other 
// captains in order of ascending indices.  When captain 
// teams makes his pick, round 1 is over.  If any unpicked 
// players remain, the draft continues with round 2.  In 
// round 2, all captains make their picks in reverse order - 
// so captain teams starts the round, and captain 1 ends it.  
// Rounds 3, 5 and all other rounds with odd numbers go 
// similar to round 1, while all rounds with even numbers go 
// similar to round 2.  For example, if there are 4 captains, 
// they'll pick players in the following order: 1, 2, 3, 4, 
// 4, 3, 2, 1, 1, 2, 3, ... The draft is over when all 
// players are picked.
// 
// 
// One of the captains wants to have a team which will use 
// powerplay tactics during its games, while all the other 
// captains want to have regular teams.  Powerplay skills are 
// different from the usual skills required for playing 
// hockey.  You will be given vector <int>s usualSkills and 
// powerplaySkills.  The i-th elements of usualSkills and 
// powerplaySkills represent the usual and powerplay skills, 
// respectively, of the i-th player.
// 
// 
// During the draft, a captain of a regular team will always 
// pick the player with the highest usual skill among all 
// remaining players.  If several players have the same 
// maximal usual skill, the player with the higher powerplay 
// skill will be picked.  The captain of the powerplay team 
// will make his picks in such a way that maximizes the final 
// total powerplay skill in his team.  This means he won't 
// necessarily always pick the remaining player with the 
// highest powerplay skill (see examples).  You will be given 
// an int ind - the 1-based number of the captain who wants 
// to build the powerplay team.  Return the total powerplay 
// skill of the team he chooses.
// 
// 
// DEFINITION
// Class:BuildTheBestTeam
// Method:maximalStrength
// Parameters:vector <int>, vector <int>, int, int
// Returns:int
// Method signature:int maximalStrength(vector <int> 
// usualSkills, vector <int> powerplaySkills, int teams, int 
// ind)
// 
// 
// CONSTRAINTS
// -usualSkills will contain between 2 and 50 elements, 
// inclusive.
// -powerplaySkills and usualSkills will contain the same 
// number of elements.
// -Each element of usualSkills will be between 1 and 100, 
// inclusive.
// -Each element of powerplaySkills will be between 1 and 
// 100, inclusive.
// -teams will be between 2 and 50, inclusive.
// -The number of elements in usualSkills will be an integer 
// multiple of teams.
// -ind will be between 1 and teams, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {10, 10, 10, 10, 10, 10}
// {20, 20, 20, 20, 20, 20}
// 3
// 2
// 
// Returns: 40
// 
// All players have equal skills, so the order of picks 
// doesn't matter here. The powerplay team will get 2 players 
// with powerplay skills of 20, resulting in a total skill of 
// 40.
// 
// 1)
// {10, 10, 10, 10, 10, 10}
// {10, 30, 10, 10, 30, 10}
// 3
// 3
// 
// Returns: 20
// 
// The two players with higher powerplay skills will be the 
// first two picks, so team 3 will get only 2 players with 
// powerplay skills of 10.
// 
// 2)
// {1, 2, 3, 4, 5, 6}
// {6, 5, 4, 3, 2, 1}
// 3
// 1
// 
// Returns: 11
// 
// The powerplay team can get players with powerplay skills 
// of 6 and 5.
// 
// 3)
// {1, 2, 3, 4, 5, 6}
// {6, 2, 4, 3, 5, 1}
// 3
// 1
// 
// Returns: 11
// 
// 
// 
// 4)
// {88, 82, 82, 73}
// {68, 74, 14, 1}
// 2
// 1
// 
// Returns: 75
// 
// According to the rules the powerplay captain has the first 
// and the last picks, while the other captain has the second 
// and the third. The powerplay captain has the following 
// choices:
// 
// - Pick player 1. The second team will pick players 2 and 
// 3, and player 4 goes to powerplay team. 
//   The total strength of powerplay team will be 68 + 1 = 69.
// - Pick player 2. The second team will pick players 1 and 
// 3, and player 4 goes to powerplay team. 
//   The total strength of powerplay team will be 74 + 1 = 75.
// - Pick player 3 or player 4. In either case, the second 
// team will pick players 1 and 2.
//   The total strength of powerplay team will be 14 + 1 = 15.
// 
// 
// END CUT HERE
#line 149 "BuildTheBestTeam.cpp"
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

struct p {
	int us,ps;
};

bool cmp(const p &a, const p&b) {
	if (a.us == b.us) 
		return a.ps > b.ps;
	return a.us > b.us;
}
bool cmp1(const p &a, const p&b) {
	if (a.ps == b.ps) 
		return a.us > b.us;
	return a.ps > b.ps;
}

    class BuildTheBestTeam
        { 
        public: 
        int maximalStrength(vector <int> us, vector <int> ps, int n, int ind) 
            { 
							vector<p> pl(us.size());
							fi(us.size()) {
								pl[i].us = us[i];
								pl[i].ps = ps[i];
							}
							sort(pl.begin(), pl.end(), cmp);

							VI ord(us.size());
							int cu = 0;
							int dx = 1;
							bool f  = true;
							fi(us.size()) {
									ord[i] = cu;
								if (f) {
									cu += dx;
									f = false;
								} else if (cu == 0 || cu == n - 1) {
									dx *= -1;
									f = true;
								} else {
									cu += dx;
									f = false;
								}
							}
							fi (ord.size()) cout << ord[i] << " ";
							cout << endl;

							VI ch(ord.size()); 

							ind--;
							fi(ord.size()) {
								if (ord[i]!=ind) continue;
								int le = 0;
								f(j,i,ord.size())
									if (ord[j]==ind) le++;
								ch[i]=le;
							}

							int ret = 0;
							fi(ord.size()) {
								if (ord[i] != ind) {
									continue;
								}
								int t = i;
								f(j,i+1,ord.size()) {
									if (ord[j] == ind && j != i + 1) break;
									if (pl[j].ps > pl[t].ps) {
										t = j;
									}
								}
								int get = pl[t].ps;
								sort(pl.begin() + i, pl.end(), cmp1);
								int lim = min((int)pl.size(), i + ch[i]);
								int pos = i;
								f(j,i,lim) {
									if (pl[j].us > pl[pos].us && pl[j].ps > get) {
										pos = j;
										get = pl[j].ps;
									}
								}
								ret += pl[pos].ps;
								swap(pl[pos],pl[i]);
								sort(pl.begin() + i + 1, pl.end(), cmp);
							}
							
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 10, 10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 20, 20, 20, 20, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 2; int Arg4 = 40; verify_case(0, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {10, 10, 10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 30, 10, 10, 30, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 3; int Arg4 = 20; verify_case(1, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 5, 4, 3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 1; int Arg4 = 11; verify_case(2, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 2, 4, 3, 5, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 1; int Arg4 = 11; verify_case(3, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {88, 82, 82, 73}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {68, 74, 14, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 1; int Arg4 = 75; verify_case(4, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BuildTheBestTeam ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

