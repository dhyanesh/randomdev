// BEGIN CUT HERE
// PROBLEM STATEMENT
// John takes part in a regional olympiad in informatics 
// together with other participants.
// At the contest each participant gains some nonnegative 
// integer score.
// Each participant (except for John) is assigned to one of 
// the N contest rooms (numbered from 0 to N-1) and John is 
// the only contestant in the room number N.
// John has no idea how many participants are in the other 
// rooms.
// For each of the other rooms he only knows the sum of 
// scores of all participants in it.
// 
// 
// You are given a vector <int> sums containing N elements 
// and an int k.
// The i-th element of sums is the sum of participants' 
// scores in the i-th contest room.
// Return the minimal score John has to gain to be sure that 
// there are at most k participants with strictly higher 
// scores.
// 
// 
// DEFINITION
// Class:TheOlympiadInInformatics
// Method:find
// Parameters:vector <int>, int
// Returns:int
// Method signature:int find(vector <int> sums, int k)
// 
// 
// CONSTRAINTS
// -sums will contain between 1 and 47 elements, inclusive.
// -Each element of sums will be between 0 and 1,000,000,000, 
// inclusive.
// -k will be between 0 and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {4, 7, 0, 5}
// 0
// 
// Returns: 7
// 
// John has to gain at least 7 points, because there might be 
// a competitor with 7 points in room number 1 (0-based index).
// 
// 1)
// {4, 7}
// 2
// 
// Returns: 3
// 
// It is possible that there are three contestants who scored 
// more than 2 points: there can be one in room 0 and two 
// more in room 1.
// There can only be at most two contestants who scored more 
// than 3 points: there can be at most one such contestant in 
// each of the two rooms.
// (Note that the score of each contestant has to be an 
// integer.)
// Therefore, John has to score at least 3 points.
// 
// 
// 2)
// {999999999}
// 1000000000
// 
// Returns: 0
// 
// Here it is enough to gain 0 points.
// 
// 3)
// {95, 23, 87, 23, 82, 78, 59, 44, 12}
// 70
// 
// Returns: 6
// 
// 
// 
// END CUT HERE
#line 86 "TheOlympiadInInformatics.cc"
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

    class TheOlympiadInInformatics
        { 
        public: 
          bool isOK(int mid, VI &sums, int k) {
            int sc = mid + 1;
            int num = 0;
            fi(sums.size()) {
              num += sums[i] / sc;
            }
            return num <= k;
          }

        int find(vector <int> sums, int k) { 
          int high = 0;
          fi (sums.size()) 
            high = std::max(high, sums[i]);

          int low = 0;

          int mid = 0;
          fi(100) {
            mid = (low + high) / 2;
            if (isOK(mid, sums, k)) {
              high = mid;
            } else {
              low = mid + 1;
            }
          }

          return mid;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {4, 7, 0, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 7; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {4, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {999999999}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; int Arg2 = 0; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {95, 23, 87, 23, 82, 78, 59, 44, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 70; int Arg2 = 6; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheOlympiadInInformatics ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

