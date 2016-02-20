// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Consider the following solitaire game:
// We have a deck of identical cards. Initially, these cards 
// are split into several heaps, with heaps[i] cards on the i-
// th heap.
// Each step of the game looks as follows: Pick one card from 
// each of the heaps and make a new heap out of these cards.
//  
// 
// 
// When describing a position in the game, only the heap 
// sizes matter, their order does not.
// Clearly, sooner or later a position will repeat and the 
// game will become periodic from that point on.
// 
// 
// 
// Write a method that takes a vector <int> heaps and returns 
// the length of the shortest period of the game.
// 
// In other words, find the smallest number of steps S such 
// that for some X the positions after X and X+S steps are 
// equal.
// 
// 
// DEFINITION
// Class:SolitaireSimulation
// Method:periodLength
// Parameters:vector <int>
// Returns:int
// Method signature:int periodLength(vector <int> heaps)
// 
// 
// NOTES
// -After some finite number of moves the game must always 
// become periodic.
// 
// 
// CONSTRAINTS
// -heaps will contain between 1 and 50 elements, inclusive.
// -Each element in heaps will be between 1 and 50, inclusive.
// -The sum of all elements in heaps will be between 1 and 
// 50, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {3,1,3}
// 
// Returns: 4
// 
// 
// In the first step of this game we take one card from each 
// of the heaps, leaving two heaps with two cards each. Then 
// we form a new heap consisting of the three cards we took. 
// Thus the new heap sizes are 2, 2, and 3.
// 
// 
// In the next step, the sizes of these heaps decrease to 1, 
// 1, 2, and a new heap of size 3 appears.
// 
// 
// After the third step the heap sizes will be 1, 2, and 4.
// 
// 
// After the fourth step the heap sizes will be 1, 3, and 3. 
// This is exactly the starting position.
// 
// 
// 1)
// {1,4}
// 
// Returns: 3
// 
// In this case, the positions after the next few steps will 
// look as follows:
// 
// 2,3
// 1,2,2
// 1,1,3
// 2,3
// 1,2,2
// ...
// 
// The shortest period has length 3. Note that the starting 
// position 1,4 is never repeated again.
// 
// 2)
// {1}
// 
// Returns: 1
// 
// After each step we have the same heap with one card.
// 
// 3)
// {4,3,2,1}
// 
// Returns: 1
// 
// 
// 
// 4)
// {3,3,3,3}
// 
// Returns: 5
// 
// 
// 
// END CUT HERE
#line 114 "SolitaireSimulation.cc"
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

    class SolitaireSimulation
        { 
        public: 
        int periodLength(vector <int> heaps) 
            { 
              multiset<int> h;
              fi(heaps.size()) h.insert(heaps[i]);

              int p = 0;

              map<multiset<int>, int> all;
                all.insert(make_pair(h, p));
              while (true) {
                int x = h.size();
                for(multiset<int>::iterator itr = h.begin(); itr!=h.end(); ++itr) {
                  h.erase(itr);
                  if (*itr != 1)
                    h.insert(*itr - 1);
                }
                h.insert(x);
                ++p;
                map<multiset<int>, int>::iterator itr = all.find(h);
                if (itr != all.end()) {
                  return p - itr->second;
                }
                all.insert(make_pair(h, p));
              }

              return p;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,1,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, periodLength(Arg0)); }
	void test_case_1() { int Arr0[] = {1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, periodLength(Arg0)); }
	void test_case_2() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, periodLength(Arg0)); }
	void test_case_3() { int Arr0[] = {4,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, periodLength(Arg0)); }
	void test_case_4() { int Arr0[] = {3,3,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, periodLength(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        SolitaireSimulation ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

