// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Frugal Fred and Lucky Lenny were talking the other day, 
// and Fred challenged Lenny to a game.  The rules for the 
// game were as follows:
// 
// Lenny goes first.
// On a player's turn, he must place one coin into an 
// initially empty pot.
// After placing a coin into the pot, the player may then 
// remove any number of coins from the pot, such that the 
// total value of all coins removed is less than the value of 
// the coin placed in the pot.
// The game ends when a player cannot put a coin into the pot 
// on their turn; that player loses.  The loser must pay the 
// winner an amount equal to the value of the coins that the 
// winner is holding.
// 
// Lenny is afraid that Fred has stacked the game in his 
// favor, so he has asked you to find out the outcome if both 
// players play optimally.  There are 3 types of coins.  You 
// are given a int[] values, where the i-th element is the 
// value of the i-th type of coin.  You are also given vector 
// <int>s lennysCoins and fredsCoins, where the i-th element 
// of each is the number of coins of the i-th type initially 
// held by Lenny and Fred, respectively.
// 
// Return the amount of money Lenny receives in this game, 
// assuming that both play optimally.  If Lenny must lose 
// money, return this as a negative number (e.g., if Lenny 
// must lose 2, then this will be returned as -2).
// 
// 
// DEFINITION
// Class:MoneyGame
// Method:play
// Parameters:vector <int>, vector <int>, vector <int>
// Returns:int
// Method signature:int play(vector <int> lennysCoins, vector 
// <int> fredsCoins, vector <int> values)
// 
// 
// CONSTRAINTS
// -lennysCoins and fredsCoins will each contain exactly 3 
// elements.
// -Each element of lennysCoins and fredsCoins will be 
// between 0 and 5, inclusive.
// -values will contain exactly 3 elements.
// -Each element of values will be between 1 and 1000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {0,1,1}
// {0,1,1}
// {20,10,2}
// 
// Returns: -2
// 
// Optimally played, Lenny starts by playing his 2 cost coin. 
// Fred plays his 10 cost coin, taking a 2 cost coin out of 
// the pot.  Lenny plays his 10 cost coin, and Fred (holding 
// two 2 cost coins) plays one of them.  Lenny has no coins 
// left, and so must pay Fred 2.
// 
// 1)
// {0,1,2}
// {0,1,1}
// {20,10,2}
// 
// Returns: 2
// 
// The same game as Example 0, but in this case the extra 
// coin makes a difference, as Lenny wins 2.
// 
// 2)
// {1,1,0}
// {0,0,1}
// {1,5,10}
// 
// Returns: 0
// 
// This game turns out to be a draw.
// 
// 3)
// {4,4,3}
// {4,3,4}
// {100,753,100}
// 
// Returns: 600
// 
// 
// 
// 4)
// {0,0,0}
// {5,5,5}
// {1000,1000,1000}
// 
// Returns: -15000
// 
// Lenny loses a lot of money.
// 
// 5)
// {3,2,1}
// {0,0,0}
// {6,8,14}
// 
// Returns: 42
// 
// 
// 
// END CUT HERE
#line 117 "MoneyGame.cpp"
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

VI v;

struct st {
	st(VI x, VI y)  {
		a = 0;
		long long mul = 1;
		fi(x.size()){
			a+= mul*x[i];
			mul*=6;
		}
		fi(y.size()){
			a+= mul*y[i];
			mul*=6;
		}
	}

	friend bool operator<(const st &x, const st &y);

	long long a;
};


bool operator<(const st &x, const st &y) {
	return x.a<y.a;
}

map<st, int> memo;

int go(VI &fp, VI &np, VI &p);

int choose(VI &fp, VI &np, VI &p, int val) {
	int ret = -1<<30;
	fi(p.size()) {
		if (p[i] && v[i] < val) {
			fp[i]++;
			p[i]--;
			ret >?= -go(np, fp, p);
			ret >?= choose(fp, np, p, val-v[i]);
			fp[i]--;
			p[i]++;
		}
	}
	ret >?= -go(np, fp, p);
	return ret;
}

int go(VI &fp, VI &np, VI &p) {
	bool em = true;
	fi(fp.size()) if (fp[i]) em = false;
	if (em) {
		int sum = 0;
		fi(np.size())  sum += np[i]*v[i];
		return -sum;
	}
	st te(fp,np);
	if (memo.count(te) > 0) return memo[te];

	int &ret = memo[te];

	ret = -1<<30;

	fi(fp.size()) {
		if (fp[i]) {
			fp[i]--;
			p[i]++;
			ret >?= choose(fp, np, p, v[i]);
			p[i]--;
			fp[i]++;
		}
	}

	return ret;
}

    class MoneyGame
        { 
        public: 
        int play(vector <int> lennysCoins, vector <int> fredsCoins, vector <int> values) 
            { 
							v = values;

							memo.clear();

							VI pot(3, 0);

							return go(lennysCoins, fredsCoins, pot);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20,10,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -2; verify_case(0, Arg3, play(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20,10,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, play(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,5,10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, play(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {4,4,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100,753,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 600; verify_case(3, Arg3, play(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,5,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -15000; verify_case(4, Arg3, play(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6,8,14}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 42; verify_case(5, Arg3, play(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MoneyGame ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

