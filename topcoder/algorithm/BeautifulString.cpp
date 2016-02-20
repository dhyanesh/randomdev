// BEGIN CUT HERE
// PROBLEM STATEMENT
// A string composed of the letters 'A' and 'B' is called 
// beautiful if it satisfies all of the following criteria:
// 
// it contains no more than countA occurences of 'A';
// it contains no more than countB occurences of 'B';
// each substring that contains only 'A's consists of no more 
// than maxA characters;
// each substring that contains only 'B's consists of no more 
// than maxB characters.
// 
// Given countA, countB, maxA and maxB, return the maximum 
// possible length of a beautiful string.
// 
// DEFINITION
// Class:BeautifulString
// Method:maximumLength
// Parameters:int, int, int, int
// Returns:int
// Method signature:int maximumLength(int countA, int countB, 
// int maxA, int maxB)
// 
// 
// CONSTRAINTS
// -countA will be between 0 and 1000000, inclusive.
// -countB will be between 0 and 1000000, inclusive.
// -maxA will be between 0 and 1000000, inclusive.
// -maxB will be between 0 and 1000000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 0
// 0
// 10
// 10
// 
// Returns: 0
// 
// We don't have any available letters as countA=0 and 
// countB=0, so the only beautiful string is the empty one.
// 
// 1)
// 10
// 10
// 0
// 0
// 
// Returns: 0
// 
// Now we have available letters, but can't include them into 
// the beautiful string as maxA=0 and maxB=0.
// 
// 2)
// 3
// 5
// 1
// 1
// 
// Returns: 7
// 
// In this case we can't have two consecutive 'A's or 'B's, 
// so letters in the beautiful string should alternate. If we 
// start the string from 'A', the longest one we'll be able 
// to get is "ABABA". But if we start the string from 'B', 
// we'll be able to get the longer one - "BABABAB".
// 
// 3)
// 677578
// 502524
// 989951
// 504698
// 
// Returns: 1180102
// 
// Here maxA >= countA and maxB >= countB, so we can easily 
// construct a beautiful string using all available 
// countA+countB letters.
// 
// END CUT HERE
#line 84 "BeautifulString.cpp"
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


    class BeautifulString
        { 
        public: 
        int maximumLength(int ca, int cb, int ma, int mb) 
            { 
							if (ma == 0 && mb ==0 ) return 0;

							int noa = 0;
							int lefa = 0;
							if (ma) {
								noa = ca / ma;
								lefa = ca - noa * ma;
								if (lefa == 0) lefa = ma,noa--;
							}
							int nob = 0;
							int lefb = 0;
							if (mb) { 
								nob = cb / mb;
								lefb = cb - nob *mb ;
								if (lefb == 0) lefb = mb,nob--;
							}

							int aca = lefa  ? noa + 1: noa;
							int acb = lefb  ? nob + 1: nob;

							if (aca > acb) {
								int ala = min(aca, acb + 1);
								int no = (ala - 1) * ma;
								if (ala == aca) no += lefa; else no+=ma;
								return no + cb;
							}
								int alb = min(acb, aca + 1);
								int no = (alb - 1) * mb;
								if (alb == acb) no += lefb; else no+=mb;
								return no + ca;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 10; int Arg3 = 10; int Arg4 = 0; verify_case(0, Arg4, maximumLength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; verify_case(1, Arg4, maximumLength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 1; int Arg3 = 1; int Arg4 = 7; verify_case(2, Arg4, maximumLength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 677578; int Arg1 = 502524; int Arg2 = 989951; int Arg3 = 504698; int Arg4 = 1180102; verify_case(3, Arg4, maximumLength(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BeautifulString ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

