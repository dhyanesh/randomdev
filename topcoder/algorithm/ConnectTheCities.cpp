// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A and B are two cities distance units away from each 
// other. Several transmitters have been placed along the 
// straight road connecting them. 
// The transmission range can be set to any positive integer 
// value, but it must be the same for all transmitters.
// Any two transmitters can communicate directly if the 
// distance between them is not greater than the transmission 
// range.
//   Each transmitter can communicate with city A or city B 
// if the distance between the transmitter and the city is 
// not greater than the transmission range. 
// 
// You have been assigned to set up a connection between the 
// cities. You are allowed to move any number of 
// transmitters, but moving a transmitter for k units costs 
// you k dollars and the budget does not allow you to spend 
// more than funds dollars in total. You can move the 
// transmitters into points with integer coordinates only.
// 
// You will be given a vector <int> position, with the i-th 
// element of position representing the initial distance 
// between the i-th transmitter and city A. You will be also 
// given funds, the maximal total cost you are allowed to 
// spend when moving transmitters.
// Return the minimal transmission range which still allows 
// you to establish a connection between the cities. See 
// notes for the formal definition of the connection.
// 
// 
// 
// DEFINITION
// Class:ConnectTheCities
// Method:minimalRange
// Parameters:int, int, vector <int>
// Returns:int
// Method signature:int minimalRange(int distance, int funds, 
// vector <int> position)
// 
// 
// NOTES
// -Cities A and B are connected if there exists a sequence 
// of transmitters t1, t2, ..., tn such that transmitter t1 
// can communicate directly with city A, transmitter tn can 
// communicate directly with city B and, for every i between 
// 1 and n-1, inclusive, transmitters ti and ti+1 can 
// communicate directly.
// 
// 
// CONSTRAINTS
// -distance will be between 1 and 100, inclusive.
// -position will contain between 1 and 50 elements, inclusive.
// -Each element of position will be between 0 and distance, 
// inclusive.
// -funds will be between 0 and 100000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 10
// 5
// { 3, 7, 9 }
// 
// Returns: 3
// 
// We can move the second transmitter one unit left and the 
// range of 3 units will be enough for a connection.
// 
// 1)
// 20
// 100
// { 0, 0, 0, 0 }
// 
// Returns: 4
// 
// We have enough money to place transmitters at positions 4, 
// 8, 12 and 16.
// 
// 2)
// 63
// 19
// { 34, 48, 19, 61, 24 }
// 
// Returns: 12
// 
// 
// 
// END CUT HERE
#line 93 "ConnectTheCities.cpp"
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

vector<int> p;
int r;
int dist;

map<pair<int, pair<int,int> > , bool> memo;

bool ok(int pos, int prev, int f) {
	pair<int,int> t1(prev, f);
	pair<int, pair<int, int> > t2(pos, t1);

	if (memo.count(t2) > 0) return memo[t2];

	if (pos == p.size()) {
		if (dist - prev <= r) {
			return true;
		}
		return false;
	}

	bool &ret = memo[t2] = false;
	int nf = f - (abs(prev + r - p[pos]));
	if (nf > 0) {
		if (prev + r < dist)
		ret |= ok(pos + 1, prev + r, nf);
		else ret = true;
	}
	if (prev + r >= p[pos]) {
		ret |= ok(pos + 1, p[pos], f);
	}

	return ret;
}

    class ConnectTheCities
        { 
        public: 
        int minimalRange(int distance, int funds, vector <int> position) 
            { 
							dist = distance;
							sort(position.begin(), position.end());
							p  = position;
							f(i,1,distance+1) {
								r = i;
								memo.clear();
								if (ok(0, 0, funds)) {
									return i;
								}
							}
							return distance;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 5; int Arr2[] = { 3, 7, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(0, Arg3, minimalRange(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 20; int Arg1 = 100; int Arr2[] = { 0, 0, 0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(1, Arg3, minimalRange(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 63; int Arg1 = 19; int Arr2[] = { 34, 48, 19, 61, 24 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; verify_case(2, Arg3, minimalRange(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        ConnectTheCities ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

