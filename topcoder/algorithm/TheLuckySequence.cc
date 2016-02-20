// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// John thinks 4 and 7 are lucky digits, and all other digits 
// are not lucky.  A lucky number is a number that contains 
// only lucky digits in decimal notation.
// 
// 
// 
// A lucky sequence is a sequence of length numbers A[0], A
// [1], ..., A[length - 1] that satisfies all of the 
// following properties:
// 
// Each number A[i] is lucky, where 0 <= i < length.
// For each i, where 0 <= i < length, there exists at least 
// one j such that A[i] = numbers[j].
// For each i, where 0 <= i < length - 1, the last digit of A
// [i] is the same as the first digit of A[i + 1].
// 
// 
// 
// 
// You are given a vector <int> numbers and an int length.  
// Return the number of distinct lucky sequences modulo 
// 1234567891. 
// 
// 
// 
// DEFINITION
// Class:TheLuckySequence
// Method:count
// Parameters:vector <int>, int
// Returns:int
// Method signature:int count(vector <int> numbers, int length)
// 
// 
// NOTES
// -Two lucky sequences A[0], A[1], ..., A[length - 1] and B
// [0], B[1], ..., B[length - 1] are considered distinct if 
// there exists i, 0 <= i < length, such that A[i] ≠ B[i].
// 
// 
// CONSTRAINTS
// -numbers will contain between 1 and 50 elements, inclusive.
// -Each element of numbers will be between 1 and 
// 1,000,000,000, inclusive.
// -length will be between 1 and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
// 1
// 
// Returns: 2
// 
// There are only two lucky numbers among these ten integers.
// 
// 1)
// {47, 74, 47}
// 3
// 
// Returns: 2
// 
// We can construct only two different sequences (47, 74, 47) 
// and (74, 47, 74).
// 
// 2)
// {100, 4774, 200, 747, 300}
// 47
// 
// Returns: 2
// 
// 
// 
// 3)
// {44, 47, 74, 77}
// 2
// 
// Returns: 8
// 
// 
// 
// END CUT HERE
#line 87 "TheLuckySequence.cc"
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

#define MOD 1234567891

typedef vector <int> VI;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   

struct sta {
  int st,en,len;
  bool operator<(const sta &input) const {
    if (st == input.st) {
      if (en == input.en) {
        return len < input.len;
      }
      return en < input.en;
    }
    return st < input.st;
  }
};

VI nums;
map<sta, int> memo;

    class TheLuckySequence
        { 
        public: 
          bool islucky(int no) {
            while (no) {
              int p = no % 10;
              if (p!=4 && p !=7)return false;
              no /= 10;
            }
            return true;
          }

          long long go(int st, int en, int len) {
            sta te;
            te.st = st;
            te.en = en;
            te.len = len;
            if (memo.count(te) > 0) return memo[te];
            if (len == 1) {
              int ret = 0;
              fi(nums.size()) {
                int p = nums[i];
                if (p % 10 != en) continue;
                int f = 0;
                while (p) {
                  f = p % 10;
                  p /= 10;
                }
                if (f != st) continue;
                ++ret;
              }
              return memo[te]=ret;
            }

            int rem = len - len / 2;
            long long ret = go(st, 4, len / 2);
            ret *= go(4, en, rem);
            ret %= MOD;

            ret += (go(st, 7, len / 2) * go(7, en, rem)) % MOD;
            ret %= MOD;

            return memo[te]=ret;
          }

          long long go(int st, int len) {
            return (go(st, 4, len) + go(st, 7, len)) % MOD;
          }

        int count(vector <int> numbers, int length) 
            { 
              set<int> nos;
              memo.clear();
              fi(numbers.size()) {
                if (islucky(numbers[i]))
                nos.insert(numbers[i]);
              }

              nums.clear();
              for(set<int>::iterator itr = nos.begin(); itr != nos.end(); ++itr) 
                nums.push_back(*itr);

              return (go(4, length) + go(7, length)) % MOD;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {47, 74, 47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {100, 4774, 200, 747, 300}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 47; int Arg2 = 2; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {44, 47, 74, 77}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 8; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        TheLuckySequence ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

