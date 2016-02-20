// BEGIN CUT HERE
// PROBLEM STATEMENT
// In Computer Science we hold weird ceremonies -- at each 
// ceremony we display all our candles but
// only n of them are lit (yeah, a binary code). 
// Unfortunately we have 2
// different types of candles: we have n1 candles that each 
// burn at the rate r1, 
// and n2 candles that each burn at the rate r2. (The rates 
// are in mm/hr.)
// 
// Before each ceremony we can choose which n of our candles 
// will be the ones that are lit during the ceremony -- we do 
// this in an attempt to keep our
// candles approximately the same length. Given n, n1, r1, 
// n2, and r2 return the number of ceremonies
// required for us to return our candles to uniform length. 
// If we can never achieve uniform length,
// return -1. 
// 
// (You may assume that
// our candles are arbitrarily long or that our ceremonies 
// are arbitrarily short so
// we won't completely burn up any candles.)
// 
// 
// 
// DEFINITION
// Class:Candles
// Method:ceremonies
// Parameters:int, int, int, int, int
// Returns:int
// Method signature:int ceremonies(int n, int n1, int r1, int 
// n2, int r2)
// 
// 
// CONSTRAINTS
// -n, n1, r1, n2, r2 will all be between 1 and 1000, 
// inclusive.
// -n1+n2 will be greater than n.
// 
// 
// EXAMPLES
// 
// 0)
// 5
// 6
// 5
// 4
// 5
// 
// Returns: 2
// 
// 
// 
//    We have 6 type 1 candles and 4 type 2's and we burn 5 
// candles at each
//    ceremony. Here they burn at the same rate, so we can 
// burn any 5 of them
//    during the first ceremony and the other five at the 
// next ceremony.
// 
// 
// 
// 
// 1)
// 3
// 12
// 4
// 6
// 2
// 
// Returns: 8
// 
// 
// 
//    For the first 6 ceremonies we could burn fresh candles, 
// 2 of type 1 and 1 of
//    type 2. At that point the type 1 candles will be 
// shorter than the type 2
//    candles. For the last 2 ceremonies burn 3 type 2 
// candles and then the other
//    3 type 2 candles -- all the candles will now be the 
// same length.
// 
// 
// 
// 2)
// 19
// 10
// 1
// 10
// 10
// 
// Returns: -1
// 
// 
// 
//     We don't have much choice here. In each ceremony we must
//     burn all our candles except for 1. We will never be 
// able to burn enough
//     of the slower burning candles to get them as short as 
// the others.
// 
// 
// 3)
// 56
// 50
// 20
// 60
// 16
// 
// Returns: 125
// 
// 
// 
// END CUT HERE
#line 119 "Candles.cpp"
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
#include <queue>    
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

int n,n1,r1,n2, r2;

map<pair<int, int>, int> memo;

int gcd(int a,int b) {
	if (a < b) return gcd(b,a);
	if (a%b==0) return b;
	return gcd(b, a%b);
}

    class Candles
        { 
        public: 
        int ceremonies(int N, int N1, int R1, int N2, int R2) 
            { 
							n = N;
							n1 = N1;
							n2 = N2;
							r1 = R1;
							r2 = R2;
							memo.clear();
							queue<pair<int,int> > bfs;
							pair<int, int> st(0,0);
							bfs.push(make_pair(0,0));
							memo[st] = 0;
							while (!bfs.empty()) {
								pair<int,int> te = bfs.front();
								bfs.pop();
								int d = memo[te];
								fi(n1+1) {
									if (n - i <= n2 && n - i>=0) {
										pair<int,int> t(te.first + i, te.second + n - i);
										if (t.first * r1 / n1 == t.second * r2 / n2 && t.first && t.second && t.first % n1 == 0 && t.second % n2 == 0) return (t.first + t.second) / n;
										pair<int,int> t1 = t;
										if (t.first > 0 && t.second > 0) {
											int c = gcd(t.first,t.second);
											t1 = make_pair(t.first/c, t.second/c);
										}
										if (memo.count(t1) > 0) continue;
										pair<int,int> diff(t1.first - n1, t1.second - n2);
										t1 = diff;
										if (diff.first > 0 && diff.second > 0) {
											int c = gcd(diff.first,diff.second);
											t1 = make_pair(diff.first/c, diff.second/c);
										}
										if (memo.count(t1) > 0) continue;
										
											bfs.push(t1);
											memo[t1] = d + 1;
									}
								}
							}

							return -1;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 6; int Arg2 = 5; int Arg3 = 4; int Arg4 = 5; int Arg5 = 2; verify_case(0, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 12; int Arg2 = 4; int Arg3 = 6; int Arg4 = 2; int Arg5 = 8; verify_case(1, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 19; int Arg1 = 10; int Arg2 = 1; int Arg3 = 10; int Arg4 = 10; int Arg5 = -1; verify_case(2, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 56; int Arg1 = 50; int Arg2 = 20; int Arg3 = 60; int Arg4 = 16; int Arg5 = 125; verify_case(3, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Candles ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

