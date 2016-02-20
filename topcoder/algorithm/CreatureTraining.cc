// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are playing a strategy game and you wish to train the 
// strongest army for the final fight. There are creatures of 
// N levels in the game, numbered from 0 to N-1, inclusive. 
// You already have some creatures in your army and D days to 
// train them. The number of creatures you have is given in a 
// vector <int> count. It contains N elements and its i-th 
// element is the number of creatures of level i.
// 
// During each day, you can choose one creature and train it. 
// Training increases a creature's level by 1, i.e., a 
// creature of level 0 becomes a creature of level 1, a 
// creature of level 1 becomes a creature of level 2, and so 
// on. The only exception is creatures of level N-1 - such 
// creatures can't be trained as N-1 is the largest possible 
// level. You can train the same creature during more than 
// one day. For example, if you train a creature during 3 
// days, it will gain 3 levels. You can also skip days and 
// not train any creatures during those days.
// 
// You are given a vector <int> power, where the i-th element 
// of power is the power of one creature of level i. The 
// power of your army is the sum of the powers of all its 
// creatures. Return the maximum possible power your army can 
// have after all D days of training are finished.
// 
// DEFINITION
// Class:CreatureTraining
// Method:maximumPower
// Parameters:vector <int>, vector <int>, int
// Returns:long long
// Method signature:long long maximumPower(vector <int> 
// count, vector <int> power, int D)
// 
// 
// CONSTRAINTS
// -count will contain between 1 and 50 elements, inclusive.
// -power will contain the same number of elements as count.
// -Each element of count and power will be between 0 and 
// 1,000,000, inclusive.
// -D will be between 1 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1, 2, 3, 4, 5}
// {1, 2, 3, 4, 5}
// 10
// 
// Returns: 65
// 
// The initial power of your army is 1*1 + 2*2 + 3*3 + 4*4 + 
// 5*5 = 55. Independent of a creature's level, training 
// increases its power by 1. After 10 days of training the 
// power of your army will be 55 + 10 = 65.
// 
// 1)
// {1, 2, 3, 4, 5}
// {1, 4, 9, 16, 25}
// 10
// 
// Returns: 309
// 
// Now it's better to train higher level creatures, as it'll 
// give your army more additional power. In 10 days you're 
// able to convert 3 creatures with initial level 3 and 4 
// creatures with initial level 4 into level 5.
// 
// 2)
// {1000, 0, 0, 0, 0}
// {0, 100, 10, 1000, 0}
// 8
// 
// Returns: 2200
// 
// You have 1000 newcomers of level 0. The best solution is 
// to train 2 of them up to level 3, and 2 up to level 1.
// 
// 3)
// {1, 2, 3, 4, 5}
// {5, 4, 3, 2, 1}
// 50
// 
// Returns: 35
// 
// It doesn't make sense to train anybody.
// 
// 4)
// {0, 5, 0, 0, 5, 0}
// {13, 20, 21, 30, 32, 36}
// 12
// 
// Returns: 318
// 
// Train 5 creatures from level 1 to level 3, and 2 creatures 
// from level 4 to level 5.
// 
// 5)
// {0, 2, 1, 0, 0, 1, 2}
// {25, 292, 328, 391, 618, 771, 952}
// 11
// 
// Returns: 5088
// 
// Train everybody except a creature with initial level 2 up 
// to the maximum possible level.
// 
// END CUT HERE
#line 112 "CreatureTraining.cc"
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

ll gain[55][55];


ll best[105];

    class CreatureTraining
        { 
        public: 
        long long maximumPower(vector <int> count, vector <int> power, int D) 
            { 
              int n = power.size();
              fi(n) {
                f(j,0, n){
                  gain[i][j] = power[j] - power[i];
                }
              }

              ll ini = 0;
              fi(n)
                ini += power[i] * (ll) count[i];

              memset(best, 0, sizeof(best));

              fi(n) {
                int le = count[i]<D?count[i]:D;
                for (int co = 0; co < le; ++ co) {
                  for(int k = D; k >= 0; k--){ 
                    for(int j=n-1;j>=i;--j) {
                      if (k-(j-i) >= 0)
                      best[k] >?= best[k - (j - i)] + gain[i][j];
                    }
                  }
                }
              }

              ll max = 0;
              fi(D + 1) {
                max >?= best[i];
              }

              return max + ini;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; long long Arg3 = 65LL; verify_case(0, Arg3, maximumPower(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 4, 9, 16, 25}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; long long Arg3 = 309LL; verify_case(1, Arg3, maximumPower(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1000, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 100, 10, 1000, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; long long Arg3 = 2200LL; verify_case(2, Arg3, maximumPower(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 4, 3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; long long Arg3 = 35LL; verify_case(3, Arg3, maximumPower(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0, 5, 0, 0, 5, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13, 20, 21, 30, 32, 36}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; long long Arg3 = 318LL; verify_case(4, Arg3, maximumPower(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0, 2, 1, 0, 0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {25, 292, 328, 391, 618, 771, 952}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; long long Arg3 = 5088LL; verify_case(5, Arg3, maximumPower(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CreatureTraining ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

