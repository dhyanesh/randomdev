// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You and your friends have gotten together for a Trivia 
// night at the local pub.  There are N questions asked 
// during the night.  Each question is worth a number of 
// points; the i-th element of the points array corresponds 
// to the score received if you correctly answer the i-th 
// question, but you lose that many points if you answer it 
// incorrectly.  The questions are given in the order 
// specified, and you must answer each question before the 
// next is asked.
// 
// In addition, after each correct answer you will receive a 
// token.  If you then have tokensNeeded tokens, the pub will 
// immediately take all of your tokens and award you 
// additional bonus points.  However, if you get the question 
// wrong, the pub will take away all of your tokens without 
// giving you any bonuses.  The bonuses change after each 
// question; element i of the bonuses array corresponds to 
// the bonus you receive if you win the bonus on question i.  
// Note that it is possible to receive multiple bonuses 
// during the game.
// 
// To generate the arrays points and bonuses described above, 
// you should use the following pseudo-code on the arrays p 
// and b, respectively.
// 
// 
// Input array:  X
// Output array:  P (size N)
// k := 0
// M := size of X
// For i=0 to N-1
// 	P[i] := X[k]
// 	s := (k+1)%M
// 	X[k] := ( ( X[k] ^ X[s] ) + 13 ) % G
// 	k := s
// 
// 
// In the above code, use the value 1001 for G when 
// generating points, and 10001 when generating bonus; this 
// guarantees that all questions will be worth between 0 and 
// 1000 points, inclusive, and that all bonuses will be worth 
// between 0 and 10,000 points, inclusive.  In the above 
// code, % represents the modulo operator, and ^ is the 
// binary XOR operator (see the Notes section for the 
// implementation in your language).
// 
// You know the answer to all the questions and want to 
// maximize the number of points that you receive.  Return 
// the maximum points that you can receive if you correctly 
// choose which questions to answer.
// 
// 
// DEFINITION
// Class:PubTrivia
// Method:maximumScore
// Parameters:int, int, vector <int>, vector <int>
// Returns:long long
// Method signature:long long maximumScore(int N, int 
// tokensNeeded, vector <int> p, vector <int> b)
// 
// 
// NOTES
// -The input is only coded for convenience.  The intended 
// solution does not rely on any property of the number 
// generation; it just generates both arrays and works on them.
// -If x and y are ints, (x^y) represents the bitwise XOR 
// operation on them in C++, Java, and C#.  In VB.net, (x 
// BitXor y) does it.
// 
// 
// CONSTRAINTS
// -N will be between 1 and 500,000, inclusive.
// -tokensNeeded will be between 1 and 500,000, inclusive.
// -p and b will each contain between 1 and 50 elements, 
// inclusive.
// -Each element of p will be between 0 and 1000, inclusive.
// -Each element of b will be between 0 and 10000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 5
// 5
// {1, 2, 3, 4, 5}
// {0, 0, 0, 2, 5}
// 
// Returns: 20
// 
// The best strategy here is to answer all five questions 
// correctly.  You score 15 points for the questions, and a 5 
// point bonus for answering five questions in a row.
// 
// 1)
// 5
// 3
// {1, 2, 3, 4, 5}
// {0, 0, 0, 2, 5}
// 
// Returns: 16
// 
// This time, it is best to answer all of the questions 
// correctly except for the second question.  You then 
// receive the bonus on the final question for answering 
// three in a row.
// 
// 2)
// 5
// 3
// {1, 2, 3}
// {7, 0}
// 
// Returns: 98
// 
// Here the question values are {1, 2, 3, 16, 14}, and the 
// bonuses are {7, 0, 20, 33, 66}.
// 
// 3)
// 4
// 4
// {998, 1}
// {9998, 1}
// 
// Returns: 1056
// 
// 
// 
// END CUT HERE
#line 133 "PubTrivia.cc"
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

void get(VI &X, VI &out, int G) {
  int k = 0;
  int m = X.size();

  fi(out.size()) {
    out[i] = X[k];
    int s = (k+1) % m;
    X[k] = ( (X[k] ^ X[s]) + 13) % G;
    k = s;
  }
}

VI p,b;
int no, mt;

map<pair<int,int>, ll> memo;

ll go(int pos, int t) {
  if (pos == no) {
    return 0;
  }

  pair<int,int> te(pos,t);
  if (memo.count(te) > 0) return memo[te];

  ll &ret = memo[te];
  ret = 0;

  if (t + 1 == mt) {
    ret = go(pos+1, 0) + b[pos] + p[pos];
  } else {
    ret = go(pos+1, t+1) + p[pos];
  }

  ret >?= go(pos+1,0) - p[pos];

  return ret;
}

    class PubTrivia
        { 
        public: 
        long long maximumScore(int n, int tn, vector <int> P, vector <int> B) 
            { 
              memo.clear();
              p.resize(n); b.resize(n);

              no = n;
              mt = tn;
              get(P, p, 1001);
              get(B, b, 10001);


              return go(0, 0);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {1, 2, 3, 4, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 2, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 20LL; verify_case(0, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 3; int Arr2[] = {1, 2, 3, 4, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 2, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 16LL; verify_case(1, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 98LL; verify_case(2, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 500000; int Arg1 = 500000; int Arr2[] = {998, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {9998, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 1056LL; verify_case(3, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        PubTrivia ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

