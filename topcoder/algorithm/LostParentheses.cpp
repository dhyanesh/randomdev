// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// We have an arithmetic expression made up of positive 
// integers, the + and - operators and parentheses. All the 
// parentheses,
// however, have been erased by the cleaning staff and we 
// want to calculate the minimum value the original 
// expression may have had.
// 
// You will be given a string e containing the expression 
// without the parentheses. Return the minimum value
// the original expression could have had before the 
// parentheses were erased.
// 
// 
// DEFINITION
// Class:LostParentheses
// Method:minResult
// Parameters:string
// Returns:int
// Method signature:int minResult(string e)
// 
// 
// NOTES
// -All operations in the original expression were addition 
// and subtraction; there were no parentheses placed between 
// two consecutive digits.
// 
// 
// CONSTRAINTS
// -e will contain between 1 and 50 characters, inclusive.
// -Each character of e will be a digit ('0'-'9'), a plus 
// sign ('+') or a minus sign ('-').
// -The first and last characters of e will be digits.
// -No two operators (characters '+' and '-') will appear 
// consecutively in e.
// -There will not be a sequence of more than 5 consecutive 
// digits in e.
// 
// 
// EXAMPLES
// 
// 0)
// "55-50+40"
// 
// Returns: -35
// 
// The expression can only have two different values: 55-
// 50+40=45 and 55-(50+40)=-35.
// 
// 1)
// "10+20+30+40"
// 
// Returns: 100
// 
// Since the sum is associative, any parenthesization of the 
// expression would get the same result.
// 
// 2)
// "00009-00009"
// 
// Returns: 0
// 
// Numbers may contain leading zeroes.
// 
// END CUT HERE
#line 69 "LostParentheses.cpp"
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

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

VS toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  VS ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
    }   
  free(ch);   
  return ret;   
}   

template<class T>
vector<T> toksT(string inp,string delim)   
{   
  VS temp = toks(inp,delim);   
  vector<T> ret;   
  for(int i=0;i<temp.size();i++)   
    ret.push_back(fromString<T>(temp[i]));   
  return ret;   
}   

    class LostParentheses
        { 
        public: 
        int minResult(string e) 
            { 
							VI t = toksT<int>(e, "+-");
							if (t.size() == 1) return t[0];

							int lastpos = 0;
							int j = 0;
							int ret = t[j++];
							while (1) {
								int pos = e.find_first_of("+-", lastpos + 1);
								if (pos == string::npos) break;

								if (e[pos] == '+') {
									ret += t[j++];
									lastpos = pos;

								}

								if (e[pos] == '-') {
									int te = 0;
									int lp = pos;
									while (1) {
										int p = e.find_first_of("+-", lp + 1);
										te += t[j++];
										if (p == string::npos || e[p] == '-') break;
										lp = p;
									}

									ret -= te;
									lastpos = lp;
								}
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "55-50+40"; int Arg1 = -35; verify_case(0, Arg1, minResult(Arg0)); }
	void test_case_1() { string Arg0 = "10+20+30+40"; int Arg1 = 100; verify_case(1, Arg1, minResult(Arg0)); }
	void test_case_2() { string Arg0 = "00009-00009"; int Arg1 = 0; verify_case(2, Arg1, minResult(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        LostParentheses ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

