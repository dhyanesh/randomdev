// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Alice and Bob are playing a game called "Naval Battle".  
// The playing field is a row of fieldLength 1x1 squares.  At 
// the beginning of the game, Alice placed one or more 
// battleships on the field.  Each battleship occupies 
// exactly shipLength consecutive squares.  There must be one 
// or more vacant squares between every pair of adjacent 
// battleships.  Bob doesn't know how many battleships Alice 
// has placed, and he doesn't know their positions.
// 
// 
// Now, Bob starts shooting.  For each shot, he says the 
// number of a single square.  The squares are numbered from 
// left to right starting with 0.  After each shot, Alice 
// tells him if he hit a square that contains a battleship or 
// if he missed.
// 
// 
// Bob suspects that Alice is playing dishonestly and 
// providing wrong answers.  You are given a vector <int> 
// shots, the i-th element of which is the number chosen by 
// Bob on his i-th shot.  You are also given a string 
// answers, the i-th character of which is '0' (zero) if 
// Alice tells him that he missed on the i-th shot, or '1' 
// (one) if she tells him that he hit a battleship.
// 
// 
// Return the 0-based index of the earliest answer after 
// which Bob can be sure that Alice is playing dishonestly.  
// Return -1 if there is no such move.
// 
// 
// DEFINITION
// Class:NavalBattle
// Method:firstDishonestMove
// Parameters:int, int, vector <int>, string
// Returns:int
// Method signature:int firstDishonestMove(int fieldLength, 
// int shipLength, vector <int> shots, string answers)
// 
// 
// CONSTRAINTS
// -fieldLength will be between 1 and 50, inclusive.
// -shipLength will be between 1 and fieldLength, inclusive.
// -shots will contain between 1 and 50 elements, inclusive.
// -Each element of shots will be between 0 and fieldLength-
// 1, inclusive.
// -answers will contain exactly n characters, where n is the 
// number of elements in shots.
// -answers will contain only the digits '0' and '1'.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 1
// {0}
// "1"
// 
// Returns: -1
// 
// 
// 
// 1)
// 3
// 2
// {0, 2, 1}
// "110"
// 
// Returns: 1
// 
// 
// 
// 2)
// 5
// 2
// {0, 4, 1, 3, 2}
// "11110"
// 
// Returns: -1
// 
// 
// 
// 3)
// 10
// 1
// {4, 7, 8, 2}
// "0110"
// 
// Returns: 2
// 
// Alice can’t place two battleships without one or more 
// vacant squares between them.
// 
// 4)
// 10
// 10
// {4, 2}
// "01"
// 
// Returns: 0
// 
// 
// 
// END CUT HERE
#line 110 "NavalBattle.cpp"
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

int m[55];
int len;
int size;

map<pair<int, int> , int> memo;

int go(int pos, int last) {
	pair<int,int> te(pos, last);
	if (memo.count(te) > 0) return memo[te];
	int &ret = memo[te];

	if (pos >= size) {
		if (last + len - 1 < size) {
			ret = 1;
		} else {
			ret = 0;
		}
		return ret;
	}
	

	if (m[pos] == 1) {
		int nlast = pos;
		if (last == -1) {
			last = pos;
		} 

		int lim = max(pos - len - 1, 0);
		for(nlast = pos; nlast >= lim && nlast > last + len; nlast--) {
			if (m[nlast] == 0) {
				break;
			}
		}

		if (pos - last < len) {
			int t1 = go(pos + 1, last);
			if (t1) return ret = 1;
		}

		if (nlast <= last + len) nlast = last + len + 1;

		for (int i = nlast; i <= pos; ++i) {
			int t2 = go(pos + 1, nlast);
			if (t2) return ret = 1;
		}
	} else if (m[pos] == 0) {
		if (last + len - 1 < pos) {
			return ret = go(pos + 1, pos + 1);
		} else {
			return ret = 0;
		}
	} else {
		return ret = go(pos + 1, last);
	}

	return ret = 0;
}

class NavalBattle
{ 
	public: 
		int firstDishonestMove(int fl, int sl, vector <int> sh, string ans) 
		{ 
			fi(fl) m[i] = 2;
			size = fl;
			len = sl;
			fi(sh.size()) {
				m[sh[i]] = ans[i] - '0';
				memo.clear();
				if (!go(0, -1)) {
					return i;
				}
			}

			return -1;
		} 

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1"; int Arg4 = -1; verify_case(0, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arr2[] = {0, 2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "110"; int Arg4 = 1; verify_case(1, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {0, 4, 1, 3, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "11110"; int Arg4 = -1; verify_case(2, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_3() { int Arg0 = 10; int Arg1 = 1; int Arr2[] = {4, 7, 8, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "0110"; int Arg4 = 2; verify_case(3, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_4() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {4, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "01"; int Arg4 = 0; verify_case(4, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }

		// END CUT HERE

}; 

// BEGIN CUT HERE 
int main()
{
	NavalBattle ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE 


