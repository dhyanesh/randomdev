// BEGIN CUT HERE
// PROBLEM STATEMENT
// A number is written on a traditional digital display. If 
// the display looks identical when flipped horizontally (i.
// e., around a vertical axis), the number is called a 
// "mirror number". On a digital display, the digits 0, 1 and 
// 8 are symmetrical, and the digits 2 and 5 are mirror 
// images of each other. No other digits make sense when 
// flipped horizontally. For example, 0, 101 and 1521 are all 
// mirror numbers, while 1221 and 1010 are not (see images 
// below). Given two strings A and B, both representing 
// integers with no extra leading zeroes, return the number 
// of mirror numbers between A and B, inclusive.
// Mirror numbers (both remain unchanged after mirroring):
//     
// Not mirror numbers (1221 mirrors to 1551, and 1010 mirrors 
// to 0101):
//     
// 
// DEFINITION
// Class:MirrorNumber
// Method:count
// Parameters:string, string
// Returns:int
// Method signature:int count(string A, string B)
// 
// 
// CONSTRAINTS
// -A will represent an integer between 0 and 10^18, inclusive.
// -B will represent an integer between A and 10^18, inclusive.
// -Both A and B will have no extra leading zeros.
// 
// 
// EXAMPLES
// 
// 0)
// "0"
// "10"
// 
// Returns: 3
// 
// There is only 0, 1 and 8 here.
// 
// 1)
// "0"
// "100"
// 
// Returns: 7
// 
// Few more: 11, 25, 52, 88.
// 
// 2)
// "143"
// "23543"
// 
// Returns: 54
// 
// END CUT HERE
#line 60 "MirrorNumber.cpp"
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
typedef long long ll;

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

int dig(ll no) {
	int ret = 0;
	
	while (no) {
		no/=10;
		ret++;
	}

	return ret;
}

int arr[] = { 0,1,8};
int aarr[] = { 0,1,2,5,8};

int power(int a,int b) {
	int ret = 1;
	fi(b)
		ret *=a ;
	return ret;
}

int digi(int d) {
	if (d==1) return 3;

	if (d==2) return 4;

	if (d%2==0) {
		return 4*power(5, d/2-1);
	}

		return 4*3*power(5, d/2-1);
}

int tot(char *buff, int d, int pos, bool eq) {
	if (d==1) {
		int p = strlen(buff);
		int no = buff[pos] - '0';
		if (eq) {
			if (p%2) {
				fi(5) {
					if (no==aarr[i])
						return i;
					if (no<aarr[i])
						return i-1;
				}
				return 5;
			} else {
				fi(3) {
					if (no==arr[i])
						return i;
					if (no<arr[i])
						return i-1;
				}
				return 3;
			}
		} else {
			if (p%2) {
				return 5;
			} else {
				return 3;
			}
		}


	}

	int ret = 0;

	if (eq) {
	} else {
		fi(5) {
			if (no==aarr[i])
				return i;
			if (no<aarr[i]) {
				return i-1;
		}
		return 5;
	}

	return ret;
}

int go(ll no) {
	char buff[40];
	sprintf(buff, "%lld", no);

	int d = dig(no);

	if (d == 1) {
		fi(3) {
			if (no==arr[i])
				return i;
			if (no<arr[i])
				return i-1;
		}
		return 3;
	}

	int ret = digi(d - 1);
	int p = d - 1;
	for(int i = 1; i < d/2+1; ++i,--p) {
		int te = buff[i] - '0';
		fj(5) {
			if (te==aarr[j]) {
			} else {
				ret += digi(p);
			}
			if (te<aarr[j]) {
				break;
			}
		}
	}
	ret += tot(buff, d/2+1, 0, false);
	return ret;
}

    class MirrorNumber
        { 
        public: 
        int count(string A, string B) 
            { 
							ll a = fromString<ll>(A);
							ll b = fromString<ll>(B);

							return go(b) - go(a - 1);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "0"; string Arg1 = "10"; int Arg2 = 3; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "0"; string Arg1 = "100"; int Arg2 = 7; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "143"; string Arg1 = "23543"; int Arg2 = 54; verify_case(2, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MirrorNumber ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

