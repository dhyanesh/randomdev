// BEGIN CUT HERE
// PROBLEM STATEMENT
// You want to see some page on the teletext (information 
// service on TV where we refer to pages of information by 
// numbers). Unfortunately, some of the digit buttons on the 
// remote control are broken. But you have an idea! If you 
// can't enter the number of the page you want to see, you 
// could enter some other number and with the buttons '+' and 
// '-' (which are not broken) navigate to the desired page. 
// Button '+' increases the number by 1 and button '-' 
// decreases the number by 1. You are initially at page 100. 
// To go to a different page, you may enter the page number 
// using the digit buttons that aren't broken. Then, press 
// the '+' and '-' buttons to navigate to your desired page.
// 
// You will be given an int page, the page you want to see, 
// and a vector <int> broken, the list of broken digit 
// buttons.  Return the minimum number of button presses 
// required to navigate to the page.
// 
// DEFINITION
// Class:BrokenButtons
// Method:minPresses
// Parameters:int, vector <int>
// Returns:int
// Method signature:int minPresses(int page, vector <int> 
// broken)
// 
// 
// CONSTRAINTS
// -page will be between 0 and 500,000, inclusive.
// -broken will contain between 0 and 10 elements, inclusive.
// -Each element of broken will be between 0 and 9, inclusive.
// -All elements of broken will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// 5457
// { 6, 7, 8 }
// 
// Returns: 6
// 
// You can go to page 5457 either by pressing "5455++" or 
// "5459--".
// 
// 1)
// 100
// { 1, 0, 5 }
// 
// Returns: 0
// 
// If you don't enter anything you'll get page 100.
// 
// 2)
// 14124
// { }
// 
// Returns: 5
// 
// 
// 
// 3)
// 1
// {1, 2, 3, 4, 5, 6, 7, 8, 9}
// 
// Returns: 2
// 
// We can enter page 0.
// 
// 4)
// 80000
// { 8, 9 }
// 
// Returns: 2228
// 
// 
// 
// END CUT HERE
#line 82 "BrokenButtons.cpp"
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

map<int, bool> br;

bool valid(int no) {
	if (no == 0 && br.count(no) > 0) return false;
	while (no){
		int x = no%10;
		if (br.count(x) > 0) return false;
		no/=10;
	}
	return true;
}

int size(int no) {
	if (no == 0) return 1;
	int ret = 0;
	while (no){
		no/=10;
		ret++;
	}
	return ret;
}

    class BrokenButtons
        { 
        public: 
        int minPresses(int page, vector <int> broken) 
            { 
							if (broken.size() == 10) {
								return abs(page - 100);
							}
							br.clear();
							fi(broken.size()) {
								br[broken[i]] = true;
							}

							int min = abs(page-100);
							int no1 = page;
							while(no1 >= 0) {
								if (valid(no1)) {
									break;
								}
								no1--;
							}
							if (no1 >= 0) {
								min <?= size(no1) + abs(page-no1);
							}
							int no2 = page;
							while (abs(page-no2) < min) {
								if (valid(no2)) break;
								no2++;
							}
							min <?= size(no2) + abs(no2 - page);



							return min;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5457; int Arr1[] = { 6, 7, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, minPresses(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 100; int Arr1[] = { 1, 0, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, minPresses(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 14124; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(2, Arg2, minPresses(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1; int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minPresses(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 80000; int Arr1[] = { 8, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2228; verify_case(4, Arg2, minPresses(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        BrokenButtons ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

