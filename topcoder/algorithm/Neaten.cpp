// BEGIN CUT HERE
// PROBLEM STATEMENT
// We have a real number that we want to approximate with as 
// few characters as 
// possible. We require that either the absolute
// error or the relative error must be strictly less than 10^-
// k. The absolute
// error is the absolute difference between the values of the 
// shortened version 
// and the original.
// The relative error is the absolute error divided by the 
// absolute value of 
// the original (or is taken to be infinity if the original 
// is 0).
// 
// We want the shortened version expressed as a string of 
// digits, possibly with
// a decimal point. The original number is given to us in 
// that form.
// Given k and number, 
// return the number of characters in the shortest 
// approximation.
// 
// 
// 
// DEFINITION
// Class:Neaten
// Method:shortest
// Parameters:int, string
// Returns:int
// Method signature:int shortest(int k, string number)
// 
// 
// CONSTRAINTS
// -k will be between 1 and 50, inclusive.
// -number will contain between 1 and 50 characters, inclusive.
// -number will contain at most one decimal point ('.').
// -Other than '.', number will contain only digits ('0'-'9').
// -number will contain at least one digit.
// 
// 
// EXAMPLES
// 
// 0)
// 2
//  "00."
// 
// Returns: 1
// 
// The approximation "0" has 1 character and has an absolute 
// error of 0.
//   
// 
// 
// 1)
// 2
// ".20050"
// 
// Returns: 2
// 
// The approximation ".2" has 2 characters and has an 
// absolute error of .0005 (which is less than .01).
// 
// 
// 2)
// 3
// "10000"
// 
// Returns: 4
// 
// The approximation "9995" has a relative error of 5/10000 
// (which is less than .001).
// 
// 3)
// 1
// "0.90"
// 
// Returns: 2
// 
// Please note that the error must be strictly less than 10-k.
// 
// 4)
// 3
// "91.909"
// 
// Returns: 2
// 
// 
// 
// END CUT HERE
#line 92 "Neaten.cpp"
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

    class Neaten
        { 
        public: 
        int shortest(int k, string number) 
            { 
							int val = 0;

							int dx = 0;
							int pos = number.size() - 1;
							int dotpos = number.size();
							fi(number.size()) {
								if (number[i] == '.') {
									dotpos = i;
									dx= 1;
								} else {
									val += dx;
								}
								if (val >= k - 1) { pos = i; break; }
							}

							string temp = number;
							temp.erase(dotpos);

							int nd = dotpos - k;

							if (nd > 0 ) {
								temp.insert(nd, '.');
							} else {
								temp = '.' + temp;
								fi(-nd) 
									temp = '0' + temp;
							}
						} 

				// BEGIN CUT HERE
				public:
				void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
				private:
				template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
				void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
				void test_case_0() { int Arg0 = 2; string Arg1 =  "00."; int Arg2 = 1; verify_case(0, Arg2, shortest(Arg0, Arg1)); }
				void test_case_1() { int Arg0 = 2; string Arg1 = ".20050"; int Arg2 = 2; verify_case(1, Arg2, shortest(Arg0, Arg1)); }
				void test_case_2() { int Arg0 = 3; string Arg1 = "10000"; int Arg2 = 4; verify_case(2, Arg2, shortest(Arg0, Arg1)); }
				void test_case_3() { int Arg0 = 1; string Arg1 = "0.90"; int Arg2 = 2; verify_case(3, Arg2, shortest(Arg0, Arg1)); }
				void test_case_4() { int Arg0 = 3; string Arg1 = "91.909"; int Arg2 = 2; verify_case(4, Arg2, shortest(Arg0, Arg1)); }

				// END CUT HERE

				}; 

// BEGIN CUT HERE 
int main()
{
	Neaten ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE 


