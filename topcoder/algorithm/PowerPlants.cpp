// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Our hero, Homer, has just woken to a horrible discovery!  
// While sleeping at work, several of the power plants in the 
// state have lost power.  Even worse, his boss is on the way 
// to his office, and if he doesn't have the situation fixed 
// in time, he'll be fired.  He's called you, desperately 
// asking for help, and you've agreed to help him figure 
// things out.
// 
// Homer has given you connectionCost, in which the j-th 
// character of the i-th element indicates the cost to 
// restart power plant j using power plant i; a digit 
// ('0'-'9') stands for a cost of 0-9, while an uppercase 
// letter ('A'-'Z') stands for a cost of 10-35.  Homer has 
// also given you the plantList, in which the i-th character 
// indicates whether the i-th plant is still working after 
// the power outage; a 'Y' indicates that it has power, 
// otherwise, it is an 'N'.  A plant can only be used to 
// power another plant if it currently has power.  Finally, 
// he gives you numPlants, the minimum number of plants that 
// need to be powered to save Homer's job.  You need to 
// return the minimum cost needed to power at least numPlants 
// plants.
// 
// 
// DEFINITION
// Class:PowerPlants
// Method:minCost
// Parameters:vector <string>, string, int
// Returns:int
// Method signature:int minCost(vector <string> 
// connectionCost, string plantList, int numPlants)
// 
// 
// CONSTRAINTS
// -connectionCost will contain exactly N elements, where N 
// is between 1 and 16, inclusive.
// -Each element of connectionCost will contain exactly N 
// characters.
// -Each character of connectionCost will be a digit 
// ('0'-'9') or uppercase letter ('A'-'Z').
// -plantList will contain exactly N characters.
// -Each character of plantList will be 'Y' or 'N'.
// -At least one character of plantList will be 'Y'.
// -numPlants will be between 0 and N, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"024",
//  "203",
//  "430"}
// "YNN"
// 3
// 
// Returns: 5
// 
// The cheapest way is to restart plant 1 using plant 0.  
// Once plant 1 is active, you can then use it to restart 
// plant 2.
// 
// 1)
// {"0AB",
//  "A0C",
//  "CD0"}
// "YNN"
// 3
// 
// Returns: 21
// 
// Here we can use plant 0 to restart both of the others.
// 
// 2)
// {"1ABCD",
//  "35HF8",
//  "FDM31",
//  "AME93",
//  "01390"}
// "NYNNN"
// 5
// 
// Returns: 14
// 
// 
// 
// 3)
// {"012",
//  "123",
//  "234"}
// "NNY"
// 2
// 
// Returns: 2
// 
// 
// 
// 4)
// {"1309328",
//  "DS2389U",
//  "92EJFAN",
//  "928FJNS",
//  "FJS0DJF",
//  "9FWJW0E",
//  "23JFNFS"}
// "YYNYYNY"
// 4
// 
// Returns: 0
// 
// 
// 
// 5)
// {"01","20"}
// "YN"
// 2
// 
// Returns: 1
// 
// The cost to restart plant 0 using plant 1 may differ from 
// the cost of restarting plant 1 using plant 0.
// 
// END CUT HERE
#line 127 "PowerPlants.cpp"
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

int n,N;
VS cc;

int cbits(int st) {
	int ret = 0;
	while (st){
		st &= (st - 1);
		ret++;
	}
	return ret;
}

map<int, int> memo;

int get(int i, int j) {
	if (isdigit(cc[i][j])) return cc[i][j] - '0';
	return cc[i][j] - 'A' + 10;
}

int go(int st) {
	if (cbits(st) >= n) return 0;
	if (memo.count(st) > 0) return memo[st];

	int ret = 1<<30;
	fi(N) {
		if (st & 1<<i)
			continue;

		int min = 1<<30;
		fj(N) {
			if (st & 1<<j)
			min <?= get(j,i);
		}

		ret <?= go(st | 1<<i) + min;
	}

	return memo[st] = ret;
}

    class PowerPlants
        { 
        public: 
        int minCost(vector <string> connectionCost, string plantList, int numPlants) 
            { 
							n = numPlants;
							cc = connectionCost;
							N = cc.size();
							memo.clear();

							int state = 0;
							fi(plantList.size()) {
								if (plantList[i] == 'Y') state |= 1<<i;
							}

							return go(state);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"024",
 "203",
 "430"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YNN"; int Arg2 = 3; int Arg3 = 5; verify_case(0, Arg3, minCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0AB",
 "A0C",
 "CD0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YNN"; int Arg2 = 3; int Arg3 = 21; verify_case(1, Arg3, minCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1ABCD",
 "35HF8",
 "FDM31",
 "AME93",
 "01390"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NYNNN"; int Arg2 = 5; int Arg3 = 14; verify_case(2, Arg3, minCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"012",
 "123",
 "234"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NNY"; int Arg2 = 2; int Arg3 = 2; verify_case(3, Arg3, minCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"1309328",
 "DS2389U",
 "92EJFAN",
 "928FJNS",
 "FJS0DJF",
 "9FWJW0E",
 "23JFNFS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YYNYYNY"; int Arg2 = 4; int Arg3 = 0; verify_case(4, Arg3, minCost(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"01","20"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YN"; int Arg2 = 2; int Arg3 = 1; verify_case(5, Arg3, minCost(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PowerPlants ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

