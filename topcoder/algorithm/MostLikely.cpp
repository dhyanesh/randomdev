// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// In a contest, we know the scores of all our competitors, 
// and we estimate that
// our own score is equally likely to be any integer value 
// between low and high, 
// inclusive. We want to know what our rank will most likely 
// be. We define our
// rank to be 1 + the number of competitors that beat us, so 
// our rank will be
// number 1 if no one beats us (even if several tie us).
// 
// Given a vector <int> scores, the scores of our 
// competitors, and ints low and high, return our most likely 
// rank. If there
// is more than one most likely rank, return -1.
// 
// 
// 
// DEFINITION
// Class:MostLikely
// Method:likelyRank
// Parameters:vector <int>, int, int
// Returns:int
// Method signature:int likelyRank(vector <int> sc, int low, 
// int high)
// 
// 
// CONSTRAINTS
// -scores will contain between 1 and 50 elements, inclusive.
// -Each element of scores will be between 0 and 
// 1,000,000,000, inclusive.
// -low will be between 0 and 1,000,000,000, inclusive.
// -high will be between low and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {3,12,4}
// 8
// 8
// 
// Returns: 2
// 
// 
// 
//    It is certain that only the 12 will beat us, giving us 
// a rank of 2.
// 
// 
// 
// 1)
//  {3,4,5}
// 3
// 7
// 
// Returns: 1
// 
// 
//    Our score is equally likely to be 3 or 4 or 5 or 6 or 7.
//    One of those scores (the 3) gives us a rank of 3. 
// Similarly, one of those
//    scores gives us a rank of 2. And the remaining 3 scores 
// all give us a
//    rank of 1 which is thus the most likely.
// 
// 
// 2)
//  {3,4,5} 
// 2
// 5
// 
// Returns: -1
// 
// 
//    Each of our possible scores gives us a different rank, 
// so all those
//    ranks are tied for most likely.
// 
// END CUT HERE
#line 84 "MostLikely.cpp"
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

    class MostLikely
        { 
        public: 
        int likelyRank(vector <int> sc, int low, int high) 
            { 
							sort(sc.rbegin(), sc.rend());
							
							int scprev = 2000000000;
							// [sc[i], scprev) [low, high]
							int arr[sc.size() + 1];
							int n = sc.size();
							memset(arr, 0, sizeof(arr));
							fi(sc.size()) {
								if (high < sc[i] || low >=scprev)
									continue;
								arr[i] =
									min(scprev - 1, high) - max(low, sc[i]) + 1;
								scprev = sc[i];
							}
							arr[n] = 
									min(scprev - 1, high) - max(low, -1) + 1;

							int bi = 0;
							fi(n+1) {
								if (arr[i]>arr[bi]) bi=i;
							}
							fi(n+1) {
								if (arr[bi]==arr[i] && bi!=i) return -1;
							}

							return bi + 1;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,12,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 8; int Arg3 = 2; verify_case(0, Arg3, likelyRank(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] =  {3,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 7; int Arg3 = 1; verify_case(1, Arg3, likelyRank(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] =  {3,4,5} ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 5; int Arg3 = -1; verify_case(2, Arg3, likelyRank(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MostLikely ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

