// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// The Change-O-Matic is a deterministic machine with a 
// single goal: to provide change. That is, you throw in a 
// banknote or a coin, and the machine throws out a bunch of 
// smaller coins with the same total value.
// 
// 
// 
// More precisely, the Change-O-Matic operates as follows:
// 
// 
// 
// The machine contains several large stacks of coins. The 
// values of these coins are given as a vector <int> 
// outputValues. For the purpose of this problem we may 
// assume that the
// machine contains an infinite number of coins of each of 
// these values. One of the available values is always 1.
// 
// 
// 
// The customer may throw in any coin or banknote with value 
// greater than 1. The machine will output a set of at least 
// two coins with the same total value. 
// If there are multiple ways to satisfy this requirement, 
// the machine prefers the one where the total number of 
// output coins is minimized.
// If there are still multiple ways, the machine prefers the 
// one that is lexicographically maximal (see Notes for a 
// precise definition).
// 
// 
// 
// You have a single banknote, and its value is given as a 
// long long inputValue. You would like to change it into 
// coins of value 1 each. 
// Return the number of times you have to throw something 
// into the machine.
// 
// 
// 
// DEFINITION
// Class:ChangeOMatic
// Method:howManyRounds
// Parameters:vector <int>, long long
// Returns:long long
// Method signature:long long howManyRounds(vector <int> 
// outputValues, long long inputValue)
// 
// 
// NOTES
// -Let A=(a1,...,aN) and B=(b1,...,bN) be two different but 
// equally large sets of coins, with a1 >= a2 >= ... >= aN 
// and b1 >= b2 >= ... >= bN. Let x be the smallest index 
// such that ax != bx. If ax > bx, we say that the set A is 
// lexicographically larger than the set B.
// -Given a collection of different but equally large sets of 
// coins, the lexicographically maximal set is the one that 
// is lexicographically larger than each of the other sets. 
// (Note that there is always exactly one such set.)
// 
// 
// CONSTRAINTS
// -outputValues will contain between 1 and 50 elements, 
// inclusive.
// -outputValues will be sorted in strictly ascending order. 
// That is, for each i, outputValues[i] < outputValues[i+1].
// -Each element of outputValues will be between 1 and 1,000, 
// inclusive.
// -Element 0 of outputValues will be equal to 1.
// -inputValue will be between 2 and 10^15, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1,5,10}
// 21
// 
// Returns: 7
// 
// The process of changing your money may look as follows:
// 
// You insert:    You get:      You then have:
// 21             10+10+1       10+10+1
// 10             5+5           10+5+5+1
// 5              1+1+1+1+1     10+5+1+1+1+1+1+1
// 10             5+5           5+5+5+1+1+1+1+1+1
// 5              1+1+1+1+1     5+5+(eleven times 1)
// 5              1+1+1+1+1     5+(sixteen times 1)
// 5              1+1+1+1+1     twenty-one coins worth 1 each
// 
// 
// 
// 1)
// {1,33,90,91,92,93,94,95,96,97,98}
// 99
// 
// Returns: 12
// 
// In each step, the machine minimizes the number of coins it 
// throws out, not the number of steps you need to accomplish 
// your task. In the first step it will output a coin worth 
// 98 and a coin worth 1.
// 
// 2)
// {1,30,60}
// 50
// 
// Returns: 2
// 
// The value of the banknote may be less than the values of 
// some coin types.
// 
// 3)
// {1,30,60,90}
// 60
// 
// Returns: 3
// 
// The value of the banknote may even be equal to the value 
// of some coin type. Note that for any input the machine 
// must always output at least two coins. Therefore if you 
// throw in the banknote worth 60, you will get two coins 
// worth 30 each.
// 
// 4)
// {1,8,9,11,12,100}
// 120
// 
// Returns: 37
// 
// In the first step the machine would output 100+12+8. (The 
// combination 100+11+9 has the same number of coins, but 
// 100+12+8 is lexicographically larger.)
// 
// END CUT HERE
#line 141 "ChangeOMatic.cc"
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
typedef long long ll;

    class ChangeOMatic
        { 
        public: 
        long long howManyRounds(vector <int> co, long long in) 
            { 
              int n = co.size();
              ll large = in / (co[n] * co[n-1]);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,5,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 21LL; long long Arg2 = 7LL; verify_case(0, Arg2, howManyRounds(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,33,90,91,92,93,94,95,96,97,98}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 99LL; long long Arg2 = 12LL; verify_case(1, Arg2, howManyRounds(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,30,60}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; long long Arg2 = 2LL; verify_case(2, Arg2, howManyRounds(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,30,60,90}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 60LL; long long Arg2 = 3LL; verify_case(3, Arg2, howManyRounds(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,8,9,11,12,100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 120LL; long long Arg2 = 37LL; verify_case(4, Arg2, howManyRounds(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ChangeOMatic ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

