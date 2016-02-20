// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// There are several people that will sit around the same 
// table in a circular fashion. Since all these people are 
// very self-conscious about their height, you don't want to 
// sit any short person next to a tall one. To formalize 
// this, we want to minimize the maximum height difference 
// between 2 adjacent persons.
// 
// You will be given the heights of the people as a vector 
// <int>. Return a vector <int> with the height of each 
// individual in clockwise order of a seating arrangement 
// that follows the above rule. If there are several 
// solutions, return the lexicographically first one.
// 
// 
// DEFINITION
// Class:HeightRound
// Method:getBestRound
// Parameters:vector <int>
// Returns:vector <int>
// Method signature:vector <int> getBestRound(vector <int> 
// heights)
// 
// 
// CONSTRAINTS
// -heights will contain between 3 and 50 elements, inclusive.
// -Each element of heights will be between 1 and 1000, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1,2,3,4}
// 
// Returns: {1, 2, 4, 3 }
// 
// It's better to separate the tallest and shortest people in 
// the round. All solutions with 1 and 4 separated are 
// equivalent, so we choose the lexicographically first one.
// 
// 1)
// {1000,500,1}
// 
// Returns: {1, 500, 1000 }
// 
// In a round of only 3 persons, everybody is next to 
// everyone else, so we only have to return the 
// lexicographically first representation.
// 
// 2)
// {1,3,4,5,7}
// 
// Returns: {1, 3, 5, 7, 4 }
// 
// 
// 
// 3)
// {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 
// Returns: {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
// 
// 
// 
// END CUT HERE
#line 72 "HeightRound.cpp"
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

    class HeightRound
        { 
        public: 
        vector <int> getBestRound(vector <int> hts) 
            { 
							sort(hts.begin(), hts.end());

							VI r,l;
							r.push_back(hts[0]);
							f(i,1,hts.size()) {
								if (i%2) 
									r.push_back(hts[i]);
								else 
									l.push_back(hts[i]);
							}
							reverse(l.begin(), l.end());

							fi(l.size())
								r.push_back(l[i]);


							return r;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 4, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getBestRound(Arg0)); }
	void test_case_1() { int Arr0[] = {1000,500,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 500, 1000 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getBestRound(Arg0)); }
	void test_case_2() { int Arr0[] = {1,3,4,5,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 5, 7, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getBestRound(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getBestRound(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        HeightRound ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

