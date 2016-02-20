// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are to populate a 5x5 square with each of the numbers 
// between 1 and 25, inclusive.  The numbers in each row must 
// be in increasing order from left to right.  Some of the 
// cells are already filled in, but no more than one number 
// per row.  You must fill in the remaining cells.
// 
// You will be given a vector <string> square. Each row is 
// given as a space-separated list of cells. Each cell is 
// either a number written with two digits (numbers less than 
// 10 have an additional leading zero) or two '?' characters 
// which represent an empty cell. Your method should return a 
// vector <string> in the same format, but with all the empty 
// cells filled in. If there are no arrangements possible 
// return an empty vector <string>. If there are several 
// arrangements possible return the one with the smallest 
// first number in the first row. If there are still several 
// arrangements possible return the one with the smallest 
// second number in the first row, and so on. 
// 
// 
// DEFINITION
// Class:NewMagicSquare
// Method:completeTheSquare
// Parameters:vector <string>
// Returns:vector <string>
// Method signature:vector <string> completeTheSquare(vector 
// <string> square)
// 
// 
// CONSTRAINTS
// -square will contain exactly 5 elements.
// -Each element of square will contain exactly 14 characters.
// -Each element of square will be a space-separated list of 
// cells.
// -Each cell will be either a number written with two digits 
// or two '?' characters.
// -Each element of square will contain at most one filled 
// cell.
// -All numbers in square will be between 1 and 25, inclusive.
// -All numbers in square will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// {"?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??"}
// 
// Returns: {"01 02 03 04 05", "06 07 08 09 10", "11 12 13 14 
// 15", "16 17 18 19 20", "21 22 23 24 25" }
// 
// You are not limited by prefilled cells. The answer is the 
// lexicographically smallest square.
// 
// 1)
// {"?? ?? 20 ?? ??", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? 05 ??", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??"}
// 
// Returns: {"01 06 20 21 22", "07 08 09 10 11", "02 03 04 05 
// 12", "13 14 15 16 17", "18 19 23 24 25" }
// 
// 
// 
// 2)
// {"?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? 24", 
//  "?? ?? ?? ?? ??", 
//  "?? ?? ?? ?? ??", 
//  "21 ?? ?? ?? ??"}
// 
// Returns: { }
// 
// You should place four numbers greater than 21 into the 5th 
// row. There are four such numbers - 22, 23, 24 and 25, but 
// 24 is already used in the second row.
// 
// 3)
// {"?? ?? 15 ?? ??", 
//  "02 ?? ?? ?? ??", 
//  "?? ?? ?? 07 ??", 
//  "?? ?? 16 ?? ??", 
//  "?? ?? ?? ?? 21"}
// 
// Returns: {"01 03 15 17 18", "02 08 09 10 22", "04 05 06 07 
// 23", "11 12 16 24 25", "13 14 19 20 21" }
// 
// 
// 
// END CUT HERE
#line 100 "NewMagicSquare.cpp"
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

int g[5][5];

bool solve(int r, int c, int used, int max) {
	if (r==5) return true;

	if (g[r][c] != -1) {
		max >?= g[r][c];
		if (c == 4) return solve(r+1, 0, used, 1);
		return solve(r, c+1, used, max);
	}

	int m = 25;
	f(i,r+1,5) 
		if (g[r][i]!=-1 ) m <?= g[r][i];

	f(i,max,m+1) {
		if (!(used & (1<<i))) {
			g[r][c] = i;
			if (c == 4) {
				if (solve(r+1, 0, used | (1<<i), 1)) {
					return true;
				}
			}
			int ma = g[r][c]>max?g[r][c]:max;
			if (solve(r, c+1, used | (1<<i), ma)) {
				return true;
			}
			g[r][c] = -1;
		}
	}

	return false;
}

    class NewMagicSquare
        { 
        public: 
        vector <string> completeTheSquare(vector <string> sq) 
            { 
							int done = 0;
							memset(g, 0xff, sizeof(g));
							fi(sq.size()) {
								VS t = toks(sq[i], " ");
								fj(t.size()) {
									if (t[j] != "??") {
										g[i][j] = fromString<int>(t[j]);
										done |= (1<<g[i][j]);
									}
								}
							}

							vector<string>  ret;
							if (!solve(0, 0, done, 1)) {
								return ret;
							}

							fi(5) {
									char buff[50];
								fj(4) {
									sprintf(buff, "%02d ", g[i][j]);
								}
								sprintf(buff, "%02d", g[i][4]); 
								ret.push_back(buff);
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01 02 03 04 05", "06 07 08 09 10", "11 12 13 14 15", "16 17 18 19 20", "21 22 23 24 25" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, completeTheSquare(Arg0)); }
	void test_case_1() { string Arr0[] = {"?? ?? 20 ?? ??", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? 05 ??", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01 06 20 21 22", "07 08 09 10 11", "02 03 04 05 12", "13 14 15 16 17", "18 19 23 24 25" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, completeTheSquare(Arg0)); }
	void test_case_2() { string Arr0[] = {"?? ?? ?? ?? ??", 
 "?? ?? ?? ?? 24", 
 "?? ?? ?? ?? ??", 
 "?? ?? ?? ?? ??", 
 "21 ?? ?? ?? ??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, completeTheSquare(Arg0)); }
	void test_case_3() { string Arr0[] = {"?? ?? 15 ?? ??", 
 "02 ?? ?? ?? ??", 
 "?? ?? ?? 07 ??", 
 "?? ?? 16 ?? ??", 
 "?? ?? ?? ?? 21"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01 03 15 17 18", "02 08 09 10 22", "04 05 06 07 23", "11 12 16 24 25", "13 14 19 20 21" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, completeTheSquare(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        NewMagicSquare ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

