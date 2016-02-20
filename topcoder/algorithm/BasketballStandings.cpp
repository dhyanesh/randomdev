// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Since the rules of basketball do not allow games to result 
// in ties, comparing two teams during a tournament is 
// usually done by comparing the number of games they've won. 
// When comparing two teams that have played a different 
// number of games, the team that played k games less than 
// the other gets k/2 added to its win total.
// For further clarification, please see the following table 
// (the notation 7/15 means that a team played 15 games and 
// won 7 of them):
// 
// 
// Team A   Team B    Difference
// 7 / 15   8 / 20    Team A played 5 games less than team B, 
// so we assume it will win 2.5 games more.
// 		   Therefore Team A is (7 + 2.5) - 8 = 1.5 games ahead 
// of team B.
// 8 / 8    18 / 18   Though both teams have won all their 
// games, team A played 10 games less. 
//                    We assume it wins 5 of those 10 games, 
// so it is 5 games behind team B.
// 20 / 40  10 / 20   Team B played 20 games less, so we 
// assume it will have 10 more wins.
//                    Therefore, the gap between the teams is 
// 0. 
// 
// 
// Since this comparison is transitive (if team A is better 
// than team B, and team B is better than team C, then team A 
// is better than team C), the teams can be placed into the 
// standings table according to this order. If the gap 
// between two teams is 0, the team whose name comes earlier 
// alphabetically is given the better rank.
// 
// 
// You will be given a vector <string> teams, with the i-th 
// element of teams representing the i-th team. Each element 
// of teams will be formatted as "NAME WINS LOSSES" (quotes 
// for clarity), where NAME is a sequence of uppercase 
// letters representing the name of the team, and WINS and 
// LOSSES are integers representing the number of games the 
// team won and lost respectively. You are to sort teams from 
// the best to worst according to the comparison method 
// defined above, and return the standings as a vector 
// <string>. Each element of the result must be formatted as 
// "NAME GAP" (quotes for clarity), where NAME is the team's 
// name and GAP is the gap between this team and the top team 
// in the standings. 
// 
// GAP must consist of one or more digits, followed by a 
// decimal point, followed by exactly one digit.  There must 
// be no extra leading zeroes.  For example, "0.0", "0.5" and 
// "1.0" are valid, but ".5", "0", "05.0" and "5." are not.
// 
// 
// DEFINITION
// Class:BasketballStandings
// Method:constructTable
// Parameters:vector <string>
// Returns:vector <string>
// Method signature:vector <string> constructTable(vector 
// <string> teams)
// 
// 
// CONSTRAINTS
// -teams will contain between 1 and 50 elements, inclusive.
// -Each element of teams will contain between 5 and 16 
// characters, inclusive.
// -Each element of teams will be formatted as "NAME WINS 
// LOSSES" (quotes for clarity).
// -In each element of teams, NAME will contain between 1 and 
// 10 uppercase letters ('A'-'Z'), inclusive.
// -In each element of teams, WINS will be an integer between 
// 0 and 99, with no extra leading zeroes.
// -In each element of teams, LOSSES will be an integer 
// between 0 and 99, with no extra leading zeroes.
// 
// 
// EXAMPLES
// 
// 0)
// {"A 1 1", "A 8 8","D 0 0", "B 7 7", "C 99 99", "BAA 13 13"}
// 
// Returns: {"A 0.0", "A 0.0", "B 0.0", "BAA 0.0", "C 0.0", 
// "D 0.0" }
// 
// All teams win 50% of their games. They are all tied in the 
// standings and sorted in alphabetical order. Please note 
// that multiple teams may have the same name.
// 
// 1)
// {"B 11 10", "A 10 10", "C 10 11", "D 20 5"}
// 
// Returns: {"D 0.0", "B 7.0", "A 7.5", "C 8.0" }
// 
// D is a clear favorite here. 
// Team B played 1 game more than team A, therefore A is 
// supposed to get 0.5 wins out of this game. Since B has 1 
// win more, it is 0.5 wins ahead of team A.
// Team B and team C played the same number of games. Team B 
// get 1 win more, therefore it is 1 win ahead.
// 
// 2)
// {"MAVS 54 11", "SUNS 50 16", "SPURS 46 20", "JAZZ 43 23"}
// 
// Returns: {"MAVS 0.0", "SUNS 4.5", "SPURS 8.5", "JAZZ 11.5" }
// 
// Top 4 NBA team as of March 20, 2007.
// 
// 3)
// {"TEAMA 17 15", "TEAMB 14 11", "TEAMC 3 0",
//  "TEAMD 99 94", "LOSER 10 85", "WINNER 76 34"}
// 
// Returns: {"WINNER 0.0", "TEAMD 18.5", "TEAMB 19.5", "TEAMC 
// 19.5", "TEAMA 20.0", "LOSER 58.5" }
// 
// 
// 
// END CUT HERE
#line 123 "BasketballStandings.cpp"
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

struct te {
	string name;
	int p, w;

};

	bool cmp(const te &a, const te&b){ 
		if (a.p < b.p) {
			int aw = 2*a.w + (b.p - a.p);
			int bw = 2*b.w;
			if (aw == bw) return a.name < b.name;

			return aw>bw;
		} else {
			int aw = 2*a.w;
			int bw = 2*b.w + (a.p - b.p);
			if (aw == bw) return a.name < b.name;

			return aw>bw;
		}
	}
template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}


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

int gap(const te &a, const te& b) {
	if (a.p < b.p) {
		int aw = 2*a.w + (b.p - a.p);
		int bw = 2*b.w;
	return aw - bw;
	} else {
		int aw = 2*a.w;
		int bw = 2*b.w + (a.p - b.p);
	return aw - bw;
	}
}

    class BasketballStandings
        { 
        public: 
        vector <string> constructTable(vector <string> teams) 
            { 
							vector<te>  t(teams.size());
							fi(teams.size()) {
							VS tea = toks(teams[i], " ");
								t[i].name = tea[0];
								t[i].w = fromString<int>(tea[1]);
								t[i].p = t[i].w + fromString<int>(tea[2]);
							}

							sort(t.begin(), t.end(), cmp);

							VS ret;
							fi(t.size()) {
								char buf[100];
								sprintf(buf, "%s %.1lf", t[i].name.c_str(), gap(t[0], t[i])/2.0);
								ret.push_back(buf);
							}
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"A 1 1", "A 8 8","D 0 0", "B 7 7", "C 99 99", "BAA 13 13"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A 0.0", "A 0.0", "B 0.0", "BAA 0.0", "C 0.0", "D 0.0" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, constructTable(Arg0)); }
	void test_case_1() { string Arr0[] = {"B 11 10", "A 10 10", "C 10 11", "D 20 5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"D 0.0", "B 7.0", "A 7.5", "C 8.0" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, constructTable(Arg0)); }
	void test_case_2() { string Arr0[] = {"MAVS 54 11", "SUNS 50 16", "SPURS 46 20", "JAZZ 43 23"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"MAVS 0.0", "SUNS 4.5", "SPURS 8.5", "JAZZ 11.5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, constructTable(Arg0)); }
	void test_case_3() { string Arr0[] = {"TEAMA 17 15", "TEAMB 14 11", "TEAMC 3 0",
 "TEAMD 99 94", "LOSER 10 85", "WINNER 76 34"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"WINNER 0.0", "TEAMD 18.5", "TEAMB 19.5", "TEAMC 19.5", "TEAMA 20.0", "LOSER 58.5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, constructTable(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BasketballStandings ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

