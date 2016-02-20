// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// In the kingdom of Absurdistan there are N airports, and in 
// the far away country of Utopia there are M airports.
// Currently, there is no air traffic on any of these 
// airports. 
// Each airport has some capacity - i.e., a limit on the 
// number of flights it can handle. Capacities may be 
// different for different airports.
// 
// 
// 
// The citizens of the two countries would like to connect 
// them by new flights. The schedule must follow these rules:
// 
// 
// 
// Each flight is a two-way service that directly connects an 
// airport in Absurdistan and an airport in Utopia.
// No pair of airports can be connected by more than one 
// flight.
// Together, the flights must exactly meet the capacities of 
// all airports. That is, for each airport the number of 
// flights scheduled from it to another airports must be 
// exactly the same as the capacity for this airport.
// If there are multiple schedules that satisfy the previous 
// rules, the lexicographically smallest one (definition 
// follows) must be chosen.
// 
// 
// 
// Each possible schedule can be represented as a matrix with 
// N rows and M columns.
// The rows correspond to airports in Absurdistan (in 
// alphabetical order), the columns to airports in Utopia 
// (again, in alphabetical order).
// The cell at (r,c) contains the number 1 if the two 
// airports are connected by a flight and 0 otherwise.
// 
// 
// 
// To compare two schedules, find the first row in which they 
// differ, and in that row find the first column in which 
// they differ.
// The one that contains a zero in this cell is 
// lexicographically smaller.
// 
// 
// 
// You are given two vector <int>s: capacityA and capacityU. 
// The vector <int> capacityA contains the capacities of all 
// the airports in Absurdistan in alphabetical order. The 
// vector <int> capacityU describes the Utopian airports in 
// the same way.
// If there is no valid schedule, return an empty vector 
// <string>. Otherwise, find the lexicographically smallest 
// valid schedule and return it formatted as a vector <string>.
// 
// 
// DEFINITION
// Class:ConnectingAirports
// Method:getSchedule
// Parameters:vector <int>, vector <int>
// Returns:vector <string>
// Method signature:vector <string> getSchedule(vector <int> 
// capacityA, vector <int> capacityU)
// 
// 
// NOTES
// -The exact formatting of the output: A zero-one matrix A 
// with M rows and N columns is encoded as a vector <string> 
// X with M elements, containing N characters each. Character 
// c in element r is '1' if A(r,c)=1, and it is '0' if A(r,c)
// =0.
// 
// 
// CONSTRAINTS
// -capacityA will contain between 1 and 50 elements, 
// inclusive.
// -capacityU will contain between 1 and 50 elements, 
// inclusive.
// -Each element in capacityA will be between 0 and 50, 
// inclusive.
// -Each element in capacityU will be between 0 and 50, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1,2,3}
// {3,1,2}
// 
// Returns: {"100", "101", "111" }
// 
// In this case there is only one way to schedule the flights.
// 
// 1)
// {3,2,1,1}
// {1,3,1,2}
// 
// Returns: {"0111", "0101", "0100", "1000" }
// 
// In this case there are multiple valid schedules. Make sure 
// that you output the lexicographically smallest one.
// 
// 2)
// {1,2,3,4}
// {5,6,7,8}
// 
// Returns: { }
// 
// The capacities of airports in Absurdistan are too small.
// 
// 3)
// {47,47}
// {47,40,7}
// 
// Returns: { }
// 
// Each pair of airports can only be connected by a single 
// flight.
// 
// 4)
// {5,5}
// {1,1,2,1,1,1,1,1,1}
// 
// Returns: {"001001111", "111110000" }
// 
// 
// 
// 5)
// {0,0,0,0}
// {0,0,0,0,0,0}
// 
// Returns: {"000000", "000000", "000000", "000000" }
// 
// Zeros may occur in the input.
// 
// END CUT HERE
#line 143 "ConnectingAirports.cc"
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

int n,m,en;

int gr[55][55];
int done[55];

bool dfs(int st) {
  if (done[st]) return false;
  done[st] = 1;

  if (st == en) {
    return true;
  }

  if (st >= n && st < n+m) {
    if (gr[st][en] > 0) {
      --gr[st][en];
      ++gr[en][st];
      return true;
    }
    f(i,1,n) {
      if (gr[st][i] > 0) {
        --gr[st][i];
        ++gr[i][st];
        if (dfs(i)) {
          return true;
        }
        ++gr[st][i];
        --gr[i][st];
      }
    }
  } else {
    for(int i = 1 ; i < n+m; ++i) {
      if (gr[st][i] > 0) {
        --gr[st][i];
        ++gr[i][st];
        if (dfs(i)) {
          return true;
        }
        ++gr[st][i];
        --gr[i][st];
      }
    }
  }

  done[st] = 0;

  return false;
}

    class ConnectingAirports
        { 
        public: 
        vector <string> getSchedule(vector <int> a, vector <int> u) 
            { 
              n = a.size();
              m = u.size();

              memset(gr,0,sizeof(gr));
              
              ++n;
              int st = 0;
              en = n + m;
              f(i,1,n) {
                gr[0][i] = m - a[i-1];
                f(j,n,n+m) {
                  gr[i][j] = 1;
                }
              }
              f(i,n,n+m) {
                gr[i][en] = n - u[i-n] - 1;
              }


              while (true) {
                memset(done,0,sizeof(done));
                if (!dfs(st)) {
                  break;
                }
              }

              f(i,1,n) {
                if (gr[0][i] > 0) {
                  return VS();
                }
              }
              f(i,n,n+m) {
                if (gr[i][en] > 0) {
                  return VS();
                }
              }

              VS ret(n - 1, string(m, '1'));

              f(i,1,n) {
                f(j,n,n+m) {
                  if (gr[i][j] == 0) {
                    ret[i-1][j-n] = '0';
                  }
                }
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"100", "101", "111" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getSchedule(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {3,2,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,3,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0111", "0101", "0100", "1000" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getSchedule(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,6,7,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getSchedule(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {47,47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {47,40,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getSchedule(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,2,1,1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"001001111", "111110000" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getSchedule(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"000000", "000000", "000000", "000000" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, getSchedule(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ConnectingAirports ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

