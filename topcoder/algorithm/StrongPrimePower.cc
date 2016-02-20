// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// 
// NOTE: This problem statement contains superscripts that 
// may not display properly if viewed outside of the applet.
// 
// 
// 
// A number which can be represented as pq, where p is a 
// prime number and q is an integer greater than 0, is called 
// a prime power. If q is larger than 1, we call the number a 
// strong prime power. You are given an integer n.  If n is a 
// strong prime power, return an vector <int> containing 
// exactly two elements.  The first element is p and the 
// second element is q.  If n is not a strong prime power, 
// return an empty vector <int>.
// 
// 
// DEFINITION
// Class:StrongPrimePower
// Method:baseAndExponent
// Parameters:string
// Returns:vector <int>
// Method signature:vector <int> baseAndExponent(string n)
// 
// 
// CONSTRAINTS
// -n will contain digits ('0' - '9') only.
// -n will represent an integer between 2 and 10^18, inclusive.
// -n will have no leading zeros.
// 
// 
// EXAMPLES
// 
// 0)
// "27"
// 
// Returns: {3, 3 }
// 
// 27 = 33. This is a strong prime power.
// 
// 1)
// "10"
// 
// Returns: { }
// 
// 10 = 2 * 5. This is not a strong prime power.
// 
// 2)
// "7"
// 
// Returns: { }
// 
// A prime number is not a strong prime power.
// 
// 3)
// "1296"
// 
// Returns: { }
// 
// 
// 
// 4)
// "576460752303423488"
// 
// Returns: {2, 59 }
// 
// 
// 
// 5)
// "999999874000003969"
// 
// Returns: {999999937, 2 }
// 
// 
// 
// END CUT HERE
#line 80 "StrongPrimePower.cc"
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

bool isprime(long long no) {
  if (no == 1) return false;
  if (no == 2) return true;
  if (no % 2 == 0) return false;

  for(int i = 3; i * i <= no; i+=3) {
    if (no % i == 0) return false;
  }
  return true;
}

    class StrongPrimePower
        { 
        public: 
        vector <int> baseAndExponent(string n) 
            { 
              long long a;
              a = fromString<long long>(n);

              VI ret;
              f(i, 2, 100) {
                long double p = powl(a, 1.0 / i);
                
                long long p1 = p;

                fj(3) {
                  long long b = 1;
                  if (!isprime(p1 + j)) continue;
                  f(k,0,i)
                    b *= p1 + j;
                  if (b == a) {
                    ret.push_back(p1+j);
                    ret.push_back(i);
                    return ret;
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
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "27"; int Arr1[] = {3, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, baseAndExponent(Arg0)); }
	void test_case_1() { string Arg0 = "10"; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, baseAndExponent(Arg0)); }
	void test_case_2() { string Arg0 = "7"; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, baseAndExponent(Arg0)); }
	void test_case_3() { string Arg0 = "1296"; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, baseAndExponent(Arg0)); }
	void test_case_4() { string Arg0 = "576460752303423488"; int Arr1[] = {2, 59 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, baseAndExponent(Arg0)); }
	void test_case_5() { string Arg0 = "999999874000003969"; int Arr1[] = {999999937, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, baseAndExponent(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        StrongPrimePower ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

