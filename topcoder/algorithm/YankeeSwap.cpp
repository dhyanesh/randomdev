// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Little Lisa has been invited to a holiday party with her 
// friends.  So that everyone receives a gift, the host of 
// the party has decided to give presents through a "Yankee 
// swap".
// 
// In this version of a Yankee swap (which may differ from 
// the version that you are used to), each person begins 
// holding a present; the first person (indexed from 1) holds 
// present 'A', the second person holds present 'B', etc.  
// Each guest in turn (starting with guest 1 and ending with 
// guest N) decides whether or not he wants to swap 
// presents.  If he decides to swap, he chooses a person to 
// swap with, and the chosen person cannot reject the swap.  
// When every person has had a turn, the Yankee swap is over, 
// and each person leaves with the gift they are holding.
// 
// For example, one way that the party (with 3 people) could 
// proceed is as follows:
// 
// 
// "ABC" --&gt Person 1 swaps with person 2 --&gt "BAC"
// "BAC" --&gt Person 2 does not swap       --&gt "BAC"
// "BAC" --&gt Person 3 swaps with person 2 --&gt "BCA"
// 
// 
// In the above example, person 1 leaves with present B, 
// person 2 leaves with present C, and person 3 leaves with 
// present A.
// 
// The guests at the party have given you their preferences, 
// where the i-th element corresponds to the preference list 
// of the i-th guest.  If a guest ends up with the gift in 
// the j-th position of his preference list, he will have an 
// unhappiness of j.  Each guest knows the preferences of all 
// other guests.  Each guest will act optimally to minimize 
// his own unhappiness, and knows all other guests will do 
// the same.  If there are multiple ways for a guest to 
// minimize his own unhappiness,
// he will choose not to swap at all if possible; if there 
// are still multiple ways, he will choose to swap with the 
// guest with the lowest index.
// 
// 
// Return a String, the i-th character of which corresponds 
// to the turn of the i-th person. If the i-th person did not 
// swap in his turn, the i-th character of the result must be 
// equal to '-'. If he did swap with the k-th person, the i-
// th character of the result must be equal to the k-th 
// lowercase letter (so, 'a' corresponds to swapping with the 
// first person, 'b' to the second and so on).
// 
// 
// DEFINITION
// Class:YankeeSwap
// Method:sequenceOfSwaps
// Parameters:vector <string>
// Returns:string
// Method signature:string sequenceOfSwaps(vector <string> 
// preferences)
// 
// 
// CONSTRAINTS
// -preferences will contain N elements, where N is between 1 
// and 20 inclusive.
// -Each element of preferences will be a permutation of the 
// first N uppercase letters of the alphabet.
// 
// 
// EXAMPLES
// 
// 0)
// {"BAC",
//  "ACB",
//  "BCA"}
// 
// Returns: "-aa"
// 
// This swap will proceed as follows:
// 1)  Guest 1 keeps his present.
// 2)  Guest 2 swaps with Guest 1.
// 3)  Guest 3 swaps with Guest 1.
// 
// 1)
// {"ABC",
//  "BCA",
//  "CAB"}
// 
// Returns: "---"
// 
// In this scenario, everyone keeps their own gift.
// 
// 2)
// {"AECDBF",
//  "BAEDCF",
//  "DEBACF",
//  "BEDCAF",
//  "CEABDF",
//  "CBDEAF"}
// 
// Returns: "-aac-a"
// 
// 
// 
// 3)
// {"FDBHMAIELGKNJC",
//  "KGMDJBAFLECNHI",
//  "FKLJCADBEHNGIM",
//  "JMHNICABFKEGDL",
//  "IKFCDNJBLEGAMH",
//  "FDNLJGCKHMBIEA",
//  "MBKJAHDNIGECLF",
//  "KNADLFGBJIMHCE",
//  "AIFMGEBDHKJNCL",
//  "MCDALIJGNKBFHE",
//  "AJHMDLEIFKNCGB",
//  "IJLKBCMDGNHFEA",
//  "EAKFLJBDGMHCIN",
//  "JEMANBDFGICHKL"}
// 
// Returns: "--acacbdcahcja"
// 
// 
// 
// END CUT HERE
#line 129 "YankeeSwap.cpp"
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

int done[200];

    class YankeeSwap
        { 
        public: 
        string sequenceOfSwaps(vector <string> p) 
            { 
							int n = p.size();

							string str(n, ' ');
							memset(done, 0, sizeof(done));


							map<char, int> wa;
							for(int i = n - 1; i>=0;--i) {
								char g;
								fj(n) {
									if (!done[p[i][j]]) {
										g = p[i][j];
										break;
									}
								}
								str[i] = g;
								wa[g] = i;
							}

							string gi;
							map<char, int> m;
							fi(n) {
								gi += 'A' + i;
								m['A' +i] = i;
							}

							string ret;
							fi(n) {
								if (m[str[i]] >= i &&
										wa[gi[i]] >= i) {
									ret+='-';
									continue;
								}

								if (m[str[i]] < i) {
									int t = m[str[i]];
									swap(m[str[i]], m[gi[i]]);
									swap(gi[i], gi[t]);
									ret+='a'+t;
								} else {
									int t = wa[gi[i]];
									swap(m[str[i]], m[gi[i]]);
									swap(gi[i], gi[t]);
									ret+='a'+t;
								}
							}
							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BAC",
 "ACB",
 "BCA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "-aa"; verify_case(0, Arg1, sequenceOfSwaps(Arg0)); }
	void test_case_1() { string Arr0[] = {"ABC",
 "BCA",
 "CAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "---"; verify_case(1, Arg1, sequenceOfSwaps(Arg0)); }
	void test_case_2() { string Arr0[] = {"AECDBF",
 "BAEDCF",
 "DEBACF",
 "BEDCAF",
 "CEABDF",
 "CBDEAF"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "-aac-a"; verify_case(2, Arg1, sequenceOfSwaps(Arg0)); }
	void test_case_3() { string Arr0[] = {"FDBHMAIELGKNJC",
 "KGMDJBAFLECNHI",
 "FKLJCADBEHNGIM",
 "JMHNICABFKEGDL",
 "IKFCDNJBLEGAMH",
 "FDNLJGCKHMBIEA",
 "MBKJAHDNIGECLF",
 "KNADLFGBJIMHCE",
 "AIFMGEBDHKJNCL",
 "MCDALIJGNKBFHE",
 "AJHMDLEIFKNCGB",
 "IJLKBCMDGNHFEA",
 "EAKFLJBDGMHCIN",
 "JEMANBDFGICHKL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "--acacbdcahcja"; verify_case(3, Arg1, sequenceOfSwaps(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        YankeeSwap ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

