// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are writing a simple text editor that supports only 
// the following two commands: 
// 
// "type c" where c is a character: Append character c to the 
// end of the current text.
// "undo t" where t is an integer: Undo all operations that 
// were performed in the previous t seconds in reverse order.
// 
// 
// 
// All quotes are for clarity only.  The text in the editor 
// is initially empty.
// 
// 
// For example, consider the following sequence of commands:
// 
// 
// Second 1: type a
// Second 2: type b
// Second 3: type c
// Second 5: undo 3
// 
// 
// At the end of second 3, the text is "abc".  At second 5, 
// all commands performed in the previous 3 seconds are 
// undone in reverse order.  This means 'c' is removed, and 
// then 'b' is removed.  The text becomes just "a".
// 
// 
// Note that "undo" commands can also be undone.  For example:
// 
// 
// Second 1: type a
// Second 2: type b
// Second 3: undo 2
// Second 4: undo 2
// 
// 
// After second 2, the text is "ab".  After second 3, 
// everything is undone, and the text becomes empty.  At 
// second 4, the previous "undo" is undone, so the text 
// becomes "ab" again.  Then, the "type b" is also undone and 
// the text becomes just "a".
// 
// 
// You are given a vector <string> commands and a vector 
// <int> time.  Each element of commands is a single command, 
// and commands[i] is performed at time[i].  The commands are 
// given in chronological order.  Return the text after all 
// the commands are executed.
// 
// 
// DEFINITION
// Class:Undo
// Method:getText
// Parameters:vector <string>, vector <int>
// Returns:string
// Method signature:string getText(vector <string> commands, 
// vector <int> time)
// 
// 
// CONSTRAINTS
// -commands will contain between 1 and 50 elements, inclusive.
// -Each element of commands will be either "type c" where c 
// is a lowercase letter ('a'-'z') or "undo t" where t is an 
// integer between 1 and 10^9, inclusive, with no leading 
// zeroes (quotes for clarity only).
// -time will contain the same number of elements as commands.
// -Each element of time will be between 1 and 10^9, inclusive.
// -The elements of time will be in strictly ascending order.
// 
// 
// EXAMPLES
// 
// 0)
// {"type a", "type b", "type c", "undo 3"}
// {1, 2, 3, 5}
// 
// Returns: "a"
// 
// The first example from the problem statement.
// 
// 1)
// {"type a", "type b", "undo 2", "undo 2"}
// {1,2,3,4}
// 
// Returns: "a"
// 
// The second example from the problem statement.
// 
// 2)
// {"type a", "undo 1", "undo 1"}
// {1,2,3}
// 
// Returns: "a"
// 
// 
// 
// 3)
// {"type a", "type b", "type c", "undo 10"}
// {1, 2, 3, 1000}
// 
// Returns: "abc"
// 
// Note that "undo" can undo nothing if it is too late.
// 
// 4)
// {"undo 1"}
// {1}
// 
// Returns: ""
// 
// 
// 
// END CUT HERE
#line 120 "Undo.cc"
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

vector<VS> c;
VI t;

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


    class Undo
        { 
        public: 
          void Und(int pos, string &ret) {
            if (c[pos][0] == "type") {
              b[pos] = 0;
            } else {
              int back = fromString<int>(c[pos][1]);
              Do(pos, t[pos] - back, t[pos] - 1, ret);
            }
          }


          void Do(int pos, int st, int en, string &ret) {
            int cu = pos - 1;
            while (cu >= 0 && t[cu] >= st) {
              Do(cu, ret);
              --cu;
            }
          }


          void Und(int pos, int st, int en, string &ret) {
            int cu = pos - 1;
            while (cu >= 0 && t[cu] >= st) {
              Und(cu, ret);
              --cu;
            }
          }


          void Do(int pos, string &ret) {
            if (c[pos][0] == "type") {
              b[pos] = 1;
            } else {
              int back = fromString<int>(c[pos][1]);
              Und(pos, t[pos] - back, t[pos] - 1, ret);
            }
          }

          VI b;

        string getText(vector <string> co, vector <int> ti) 
            { 
              string ret;

              t = ti;
              c.clear();
              c.resize(co.size());
              fi(co.size()) {
                c[i] = toks(co[i], " ");
              }

              b.clear();
              b.resize(c.size(), 0);
              fi(c.size()) {
                Do(i, ret);
              }

              fi(c.size()) {
                if (c[i][0] == "type" && b[i]) {
                  ret += c[i][1];
                }
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"type a", "type b", "type c", "undo 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "a"; verify_case(0, Arg2, getText(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"type a", "type b", "undo 2", "undo 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "a"; verify_case(1, Arg2, getText(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"type a", "undo 1", "undo 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "a"; verify_case(2, Arg2, getText(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"type a", "type b", "type c", "undo 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 1000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "abc"; verify_case(3, Arg2, getText(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"undo 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(4, Arg2, getText(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Undo ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

