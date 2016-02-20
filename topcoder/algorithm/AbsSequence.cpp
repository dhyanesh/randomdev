// BEGIN CUT HERE
// PROBLEM STATEMENT
// Let's consider an infinite sequence S of non-negative 
// integers defined as follows:
// S0 = first;
// S1 = second;
// Si = |Si-2 - Si-1| for all i >= 2.
// You will be given strings first and second, representing 
// the 0-th and the 1-st elements of the sequence S, and a 
// vector <string> indices, each element of which represents 
// a non-negative integer without extra leading zeros. Return 
// a vector <string> containing as many elements as indices, 
// where the i-th element is equal to the indices[i]-th 
// element of the sequence S (index is 0-based). No element 
// of the return should contain extra leading zeros.
// 
// DEFINITION
// Class:AbsSequence
// Method:getElements
// Parameters:string, string, vector <string>
// Returns:vector <string>
// Method signature:vector <string> getElements(string first, 
// string second, vector <string> indices)
// 
// 
// CONSTRAINTS
// -first will represent an integer between 0 and 10^18, 
// inclusive, with no extra leading zeros.
// -second will represent an integer between 0 and 10^18, 
// inclusive, with no extra leading zeros.
// -indices will contain between 1 and 50 elements, inclusive.
// -Each element of indices will represent an integer between 
// 0 and 10^18, inclusive, with no extra leading zeros.
// 
// 
// EXAMPLES
// 
// 0)
// "21"
// "12"
// {"0", "1", "2", "3", "4"}
// 
// Returns: {"21", "12", "9", "3", "6" }
// 
// Here S0=21 and S1=12. The next three sequence elements are 
// S2 = |21 - 12| = 9, S3 = |12 - 9| = 3 and S4 = |9 - 3| = 6.
// 
// 1)
// "0"
// "0"
// {"1000000000000000000"}
// 
// Returns: {"0" }
// 
// Here we get the sequence consisting of only zeros.
// 
// 2)
// "823"
// "470"
// {"3","1","31","0","8","29","57","75","8","77"}
// 
// Returns: {"117", "470", "2", "823", "115", "87", "49", 
// "25", "115", "23" }
// 
// 
// 
// 3)
// "710370"
// "177300"
// {"5","95","164721","418","3387","710","0","1197","19507","
// 5848"}
// 
// Returns: {"178470", "108270", "90", "0", "90", "90", 
// "710370", "90", "0", "0" }
// 
// 
// 
// END CUT HERE
#line 80 "AbsSequence.cpp"
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
typedef long long  ll;   
typedef vector <ll> VL;   

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

ll get(ll a, ll b, ll ind) {
	ll c = 1;

	while (c < ind) {
		if (b == 0) break;

		ll ti = a / b;
		if (ti < 3) {
			ll p  = llabs(a-b);
			a = b;
			b = p;
			c++;
		} else {
			if (ti%2) ti--;
			c += ti + ti / 2;
			a -= ti * b;
		}
	}
	if (b == 0) {
		return llabs(ind - c) % 2 == 0 ? b : a;
	}
	if (c==ind) return b;

	ll tt = (c - ind) % 3;
	ll td = (c - ind) / 3;

	if (tt == 0) return b;
	
	return a + 2 * b * td + (tt - 1) * b;
}

    class AbsSequence
        { 
        public: 
        vector <string> getElements(string first, string second, vector <string> indices) 
            { 
							ll f = fromString<ll>(first);
							ll s = fromString<ll>(second);
							VL arr(indices.size());
							fi(indices.size()) 
								arr[i] = fromString<ll>(indices[i]);

//								printf("%lld ", f);
//								printf("%lld ", s);
							fi(1000) {
								ll t = llabs(s - f);
//								printf("%lld ", t);
//								f = s;
//								s = t;
							}
//							printf("\n");

							VS ret(arr.size());
								char buff[80];
							fi(arr.size()) {
								ll t = get(f, s, arr[i]);
								sprintf(buff, "%lld", t);
								ret[i] = buff;
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "21"; string Arg1 = "12"; string Arr2[] = {"0", "1", "2", "3", "4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"21", "12", "9", "3", "6" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getElements(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "0"; string Arg1 = "0"; string Arr2[] = {"1000000000000000000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, getElements(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "823"; string Arg1 = "470"; string Arr2[] = {"3","1","31","0","8","29","57","75","8","77"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"117", "470", "2", "823", "115", "87", "49", "25", "115", "23" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, getElements(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "710370"; string Arg1 = "177300"; string Arr2[] = {"5","95","164721","418","3387","710","0","1197","19507","5848"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"178470", "108270", "90", "0", "90", "90", "710370", "90", "0", "0" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, getElements(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        AbsSequence ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

