// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// For his birthday, Bart received the brand new video game 
// "Paintball!".  In this game, a person plays on teams over 
// the Internet against various competitors, attempting to 
// hit their opponents with paint balls.  Each player earns a 
// point each time that they "splatter" an opponent with a 
// paintball, and lose a point for each time they get 
// "splattered".  Due to the way that the game is played, it 
// is also possible to accidentally splatter yourself or a 
// teammate.  In that case, the shooter loses a point, and 
// the person who was splattered (if not the shooter) does 
// not lose any points.  A team's score is simply the sum of 
// the scores of its players.
// 
// Although Bart loves the game, he is disappointed that the 
// game does not provide a leaderboard during gameplay.  
// However, it does provide the list of players, formatted as 
// "NAME TEAM" (where NAME is the player's name, and TEAM is 
// his team), and a series of messages, each formatted as 
// "NAME1 SPLATTERED NAME2" (all quotes for clarity), where 
// NAME1 indicates the name of the person who shot the 
// paintball, and NAME2 indicates the name of the person who 
// got splattered.  Bart would like to have an updated 
// scoreboard, and that is where you come in.
// 
// All teams will receive a rank number from 1 to M (the 
// total number of teams), based on the team scores (with 1 
// corresponding to the highest score).  If multiple teams 
// have the same score, then the team with the name that 
// comes first alphabetically will receive a lower rank 
// number.  For each team (in order from 1 to M), its 
// leaderboard entry will be formatted as follows:
// 
// The first line will be "TEAM SCORE" (quotes for clarity), 
// where TEAM is the team name, and SCORE is the team score 
// (with no extra leading zeroes).
// Let N be the number of players on the team.  Assign rank 
// numbers to the N players from 1 to N, giving a lower rank 
// number to a higher score.  If multiple players have the 
// same score, assign the player whose name comes first 
// alphabetically to the lower rank number.
// From the player with rank 1 to rank N, output a line with 
// 2 spaces, the player's name, a single space, and then the 
// player's score (with no extra leading zeroes).  
// 
// Thus, if player A from team RED splatters player B from 
// team BLUE (and they are the only players in the game), the 
// leaderboard will be:
// 
// RED 1
//   A 1
// BLUE -1
//   B -1
// 
// You are to generate the leaderboard and return it.
// 
// 
// DEFINITION
// Class:Paintball
// Method:getLeaderboard
// Parameters:vector <string>, vector <string>
// Returns:vector <string>
// Method signature:vector <string> getLeaderboard(vector 
// <string> players, vector <string> messages)
// 
// 
// NOTES
// -A SCORE of 0 should be output as 0, not as -0.
// 
// 
// CONSTRAINTS
// -players will contain between 1 and 50 elements, inclusive.
// -Each element of players will contain between 3 and 50 
// characters, inclusive.
// -Each element of players will be formatted as "NAME TEAM" 
// (quotes for clarity).
// -In each element of players, NAME will consist of 
// uppercase characters ('A'-'Z') and will contain at least 1 
// character.
// -There will be no duplicate NAMEs in players.
// -In each element of players, TEAM will consist of 
// uppercase characters ('A'-'Z') and will contain at least 1 
// character.
// -messages will contain between 1 and 50 elements, inclusive.
// -Each element of messages will contain between 14 and 50 
// characters, inclusive.
// -Each element of messages will be formatted as described 
// in the problem statement.
// -In each element of messages, NAME1 and NAME2 will be 
// NAMEs found in players.
// 
// 
// EXAMPLES
// 
// 0)
// {"A RED", "B BLUE"}
// {"A SPLATTERED B"}
// 
// Returns: {"RED 1", "  A 1", "BLUE -1", "  B -1" }
// 
// The example from the statement.
// 
// 1)
// {"LISA RED", "BART RED", "HOMER BLUE", "MARGE BLUE", 
// "MAGGIE GREEN"}
// {"MAGGIE SPLATTERED HOMER", "MAGGIE SPLATTERED MARGE"}
// 
// Returns: {"GREEN 2", "  MAGGIE 2", "RED 0", "  BART 0", "  
// LISA 0", "BLUE -2", "  HOMER -1", "  MARGE -1" }
// 
// 
// 
// 2)
// {"TODD STRIKEFORCE",
//  "BART OMEGA",
//  "DATA STRIKEFORCE",
//  "MILHOUSE OMEGA",
//  "NELSON DISCOVERYCHANNEL",
//  "MARTIN DISCOVERYCHANNEL"}
// {"BART SPLATTERED MARTIN","TODD SPLATTERED MARTIN"}
// 
// Returns: {"OMEGA 1", "  BART 1", "  MILHOUSE 0", 
// "STRIKEFORCE 1", "  TODD 1", "  DATA 0", "DISCOVERYCHANNEL 
// -2", "  NELSON 0", "  MARTIN -2" }
// 
// 
// 
// 3)
// {"DR COHO", "ST COHO", "PE COHO"}
// {"DR SPLATTERED ST",
//  "ST SPLATTERED PE"}
// 
// Returns: {"COHO -2", "  PE 0", "  DR -1", "  ST -1" }
// 
// Don't shoot your teammates!
// 
// 4)
// {"A B", "AA AA", "AAA AAA"}
// {"A SPLATTERED AAA", "A SPLATTERED AAA", "A SPLATTERED 
// AAA", 
// "AA SPLATTERED AAA", "AA SPLATTERED AAA"}
// 
// Returns: {"B 3", "  A 3", "AA 2", "  AA 2", "AAA -5", "  
// AAA -5" }
// 
// 
// 
// END CUT HERE
#line 152 "Paintball.cpp"
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

VS toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  VS ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
    }   
  free(ch);   
  return ret;   
}   

map<string, set<string> > team;
map<string, int> play;
map<string, int> tplay;

map<string, string> pt;

struct tp {
	tp(int s, string na) : sc(s), n(na) { }
	bool operator<(const tp &a) const {
		if (sc == a.sc) return n<a.n;
		return sc>a.sc;
	}
	int sc;
	string n;
};

    class Paintball
        { 
        public: 
        vector <string> getLeaderboard(vector <string> pl, vector <string> m) 
            { 
							team.clear();
							play.clear();
							tplay.clear();
							pt.clear();
							fi(pl.size()) {
								VS pla = toks(pl[i], " ");
								team[pla[1]].insert(pla[0]);
								pt[pla[0]] = pla[1];
								play[pla[0]] = 0;
								tplay[pla[1]] = 0;
							}
							fi(m.size()) {
								VS te = toks(m[i], " ");

								if (pt[te[0]] == pt[te[2]]) {
									play[te[0]]--;
									tplay[pt[te[0]]]--;
								} else {
									play[te[0]]++;
									tplay[pt[te[0]]]++;
									play[te[2]]--;
									tplay[pt[te[2]]]--;
								}
							}
							vector<tp> tem;
							for(map<string, int>::iterator itr = tplay.begin();
									itr != tplay.end(); ++itr) {
								tem.push_back(tp(itr->second, itr->first));
							}
							sort(tem.begin(), tem.end());
							VS ret;
							fi(tem.size()) {
								char buff[200];
								sprintf(buff, "%s %d", tem[i].n.c_str(), tem[i].sc);
								ret.push_back(buff);
								vector<tp> p;
								for(set<string>::iterator itr = team[tem[i].n].begin();
										itr != team[tem[i].n].end(); ++itr) {
									p.push_back(tp(play[*itr], *itr));
								}
								sort(p.begin(), p.end());
								fj(p.size()) {
									char buff[200];
									sprintf(buff, "  %s %d", p[j].n.c_str(), p[j].sc);
									ret.push_back(buff);
								}
							}
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"A RED", "B BLUE"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A SPLATTERED B"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"RED 1", "  A 1", "BLUE -1", "  B -1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getLeaderboard(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"LISA RED", "BART RED", "HOMER BLUE", "MARGE BLUE", "MAGGIE GREEN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"MAGGIE SPLATTERED HOMER", "MAGGIE SPLATTERED MARGE"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"GREEN 2", "  MAGGIE 2", "RED 0", "  BART 0", "  LISA 0", "BLUE -2", "  HOMER -1", "  MARGE -1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getLeaderboard(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"TODD STRIKEFORCE",
 "BART OMEGA",
 "DATA STRIKEFORCE",
 "MILHOUSE OMEGA",
 "NELSON DISCOVERYCHANNEL",
 "MARTIN DISCOVERYCHANNEL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"BART SPLATTERED MARTIN","TODD SPLATTERED MARTIN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"OMEGA 1", "  BART 1", "  MILHOUSE 0", "STRIKEFORCE 1", "  TODD 1", "  DATA 0", "DISCOVERYCHANNEL -2", "  NELSON 0", "  MARTIN -2" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getLeaderboard(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"DR COHO", "ST COHO", "PE COHO"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"DR SPLATTERED ST",
 "ST SPLATTERED PE"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"COHO -2", "  PE 0", "  DR -1", "  ST -1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getLeaderboard(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"A B", "AA AA", "AAA AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A SPLATTERED AAA", "A SPLATTERED AAA", "A SPLATTERED AAA", 
"AA SPLATTERED AAA", "AA SPLATTERED AAA"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"B 3", "  A 3", "AA 2", "  AA 2", "AAA -5", "  AAA -5" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getLeaderboard(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Paintball ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

