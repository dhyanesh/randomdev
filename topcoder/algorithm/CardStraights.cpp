// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are playing a card game where the goal is to make 
// straights.  Each card  in the deck has a number between 1 
// and 1000000, inclusive.  A straight is a sequence of cards 
// with consecutive values.  Values do not wrap around, so 1 
// does not come after 1000000.  In addition to regular 
// cards, the deck also contains jokers.  Each joker can be 
// used as any valid number (between 1 and 1000000, inclusive).
// 
// You will be given a vector <int> cards containing the 
// cards in your hand.  Jokers are represented by 0s, and 
// other cards are represented by their values.  Return the 
// number of cards in the longest straight that can be formed 
// using one or more cards from your hand.
// 
// 
// DEFINITION
// Class:CardStraights
// Method:longestStraight
// Parameters:vector <int>
// Returns:int
// Method signature:int longestStraight(vector <int> cards)
// 
// 
// CONSTRAINTS
// -cards will contain between 1 and 50 elements, inclusive.
// -Each element of cards will be between 0 and 1000000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {0,6,5,10,3,0,11}
// 
// Returns: 5
// 
// You can make 3-4-5-6-7 using one of your jokers as a 4 and 
// the other one as a 7.
// 
// 1)
// {100,100,100,101,100,99,97,103}
// 
// Returns: 3
// 
// Not a very lucky hand.
// 
// 2)
// {0,0,0,1,2,6,8,1000}
// 
// Returns: 6
// 
// You can make 1-2-3-4-5-6 using your jokers cleverly.
// 
// 3)
// {1,9,5,7,3,4,0,0,0,10}
// 
// Returns: 10
// 
// 
// 
// END CUT HERE
#line 66 "CardStraights.cpp"
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

    class CardStraights
        { 
        public: 
        int longestStraight(vector <int> cards) 
            { 
							sort(cards.begin(), cards.end());

							int co = 0;
							fi(cards.size()) {
								if (cards[i]==0) co++;
								else break;
							}

							cards.erase(cards.begin(),cards.begin()+co);

							if (cards.size() == 0) {
								return co;
							}
							cards.erase(unique(cards.begin(), cards.end()),
										cards.end());

							int best = 0;
							fi(cards.size())
								f(j, i, cards.size()) {
									int lco = co;
									int k;
									int len = 0;
									for(k=i+1;k<=j;k++) {
										lco -= cards[k] - cards[k-1] - 1;
										len += cards[k] - cards[k-1] - 1;
										if (lco<0) break;
									}
									if (lco>=0) {
										 len += j - i + 1;
										if (lco>0) {
											int lim = min(lco, cards[i] - 1);
											len += lim;
											lco -= lim;
										}
										if (lco>0) {
											int add = cards[j] + lco;
											if (add > 1000000)
												len += 1000000 - cards[j];
											else 
												len += lco;
										}
										best >?= len;
									}
								}	

							return best;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,6,5,10,3,0,11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, longestStraight(Arg0)); }
	void test_case_1() { int Arr0[] = {100,100,100,101,100,99,97,103}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, longestStraight(Arg0)); }
	void test_case_2() { int Arr0[] = {0,0,0,1,2,6,8,1000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(2, Arg1, longestStraight(Arg0)); }
	void test_case_3() { int Arr0[] = {1,9,5,7,3,4,0,0,0,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, longestStraight(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CardStraights ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

