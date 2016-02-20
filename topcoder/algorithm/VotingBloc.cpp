// BEGIN CUT HERE
// PROBLEM STATEMENT
// The members of a committee vote 'Yes' or 'No' on various 
// issues. However, some pairs of 
// committee members have formed alliances, promising
// never to cast opposite votes. No one is willing to vote 
// contrary 
// to her own opinion, so some of the members may need to
// abstain from voting in order to avoid conflict between 
// allies.
// 
// We have devised a method to determine who 
// should abstain. Before each issue is voted on, we randomly 
// assign each 
// committee member an identifying number, 1, 2, ..., n. 
// The member will then indicate her opinion on the issue. 
// Then we will calculate
// the smallest collection of abstentions that will avoid 
// conflict.
// 
// The k-th element of the vector <string> voter contains the 
// information about the 
// k-th committee member -- the first element describes the 
// member whose id is 1,
// the second describes the member whose id is 2, etc. Each 
// element contains its member's 
// opinion, either 'Y' or 'N', followed by the identifying 
// number of each higher-numbered member 
// who has formed an alliance with its member.
//  Return a vector <int> 
// containing, in ascending order, the identifying numbers of 
// the minimal collection
// of members who must abstain from voting. If there is more 
// than one minimal collection, 
// return the one that is earliest lexicographically.
// 
// 
// DEFINITION
// Class:VotingBloc
// Method:abstainers
// Parameters:vector <string>
// Returns:vector <int>
// Method signature:vector <int> abstainers(vector <string> 
// voter)
// 
// 
// CONSTRAINTS
// -voter will contain exactly n elements, where n is between 
// 1 and 50, inclusive.
// -Each element of voter will contain between 1 and 50 
// characters, inclusive.
// -Each element of voter will be the character 'N' or 'Y' 
// followed by a list of numbers.
// -Each number on a list (which may be empty) will be 
// preceded by one space (' ').
// -The numbers on each list will be distinct, and will have 
// no leading zeroes.
// -Each number on each list will be less than or equal to n.
// -Each number on the k-th list will be greater than the 
// identifier of the k-th committee member. 
// 
// 
// EXAMPLES
// 
// 0)
// {"Y 2","N"}
// 
// Returns: {1 }
// 
// 
// 
//    Here there are 2 members (1 and 2) and there is an 
// alliance between them.
//    Since they disagree on the issue, one of them must 
// abstain. 
//    We choose 1 since it is earlier lexicographically.
// 
// 
// 
// 1)
// {"N 2","N 3","Y"}
// 
// Returns: {2 }
// 
// 
// 
//    Member 2 has an alliance with both 1 and 3. If member 3 
// abstains there
//    will be no conflict since all the remaining members 
// vote N. If member 1 abstains
//    a conflict will remain since 2 and 3 are allies who 
// disagree. If member 2
//    abstains, 1 and 3 are no longer in conflict. So there 
// are two minimal sets
//    of abstainers, and {2} is earlier lexicographically.
//  
// 
// 2)
// {"N 2 3 4","N 3 4","Y 4","Y"}
// 
// Returns: {1, 2 }
// 
// 
// 
//    Each member is allied with all the other members. The 
// only way to avoid conflict is
//    for all those whose opinion is 'Y' to abstain, or for 
// all those whose opinion
//    is 'N' to abstain. Either way it will take 2 abstentions.
// 
// 
// 3)
// {"N 2 3 4","N 3 4","Y 4","N"} 
// 
// Returns: {3 }
// 
// 
// 
//     This is the same as the preceding case except that now 
// 3 of the members agree
//     on 'N', so it takes only 1 abstention to avoid conflict.
// 
// 
// 4)
// {"Y 2 3 4","Y 3 4","Y 4","Y"}
// 
// Returns: { }
// 
// 
// 
//     Everyone agrees, so no abstentions are needed.
// 
// END CUT HERE
#line 135 "VotingBloc.cpp"
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

    class VotingBloc
        { 
        public: 
        vector <int> abstainers(vector <string> voter) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"Y 2","N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, abstainers(Arg0)); }
	void test_case_1() { string Arr0[] = {"N 2","N 3","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, abstainers(Arg0)); }
	void test_case_2() { string Arr0[] = {"N 2 3 4","N 3 4","Y 4","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, abstainers(Arg0)); }
	void test_case_3() { string Arr0[] = {"N 2 3 4","N 3 4","Y 4","N"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, abstainers(Arg0)); }
	void test_case_4() { string Arr0[] = {"Y 2 3 4","Y 3 4","Y 4","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, abstainers(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        VotingBloc ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

