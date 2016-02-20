// BEGIN CUT HERE
// PROBLEM STATEMENT
// There's a shoe store in which some models are popular, and 
// some are not. In order to sell more unpopular models, the 
// store introduced a system of discounts. Each discount 
// works in the following way: if you buy an unpopular model 
// for a cost of COST, then you can buy a popular model with 
// a PERCENT% discount. However, the owner of the store is 
// greedy, and therefore only discounts with PERCENTs equal 
// to 1, 2 and 3 were introduced.
// After it became obvious that such low discounts didn't 
// work well, the store allowed people to apply more than one 
// discount to the same pair of shoes. For example, you can 
// buy three unpopular models, obtain three discounts and use 
// all three to reduce the cost of the same popular model. 
// When many discounts are applied to the same model, they 
// are applied one after another. For example, if you apply 
// 2% and 3% discounts to a model with cost 100, it's cost 
// will be 0.98 * 0.97 * 100 = 95.06.
// The available discounts are given in a vector <string> 
// discounts, each element of which is formatted "COST 
// PERCENT" (quotes for clarity). Different elements of 
// discounts correspond to different unpopular models. You 
// want to buy a popular model, which costs price. In order 
// to reduce the model's cost, you can buy some unpopular 
// models and obtain discounts from them, but you don't wish 
// to buy the same unpopular model more than once. Return the 
// minimum amount of money you need to spend in order to buy 
// the desired popular model.
// 
// DEFINITION
// Class:DiscountCombination
// Method:minimumPrice
// Parameters:vector <string>, int
// Returns:double
// Method signature:double minimumPrice(vector <string> 
// discounts, int price)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative 
// or absolute value of 1E-9.
// 
// 
// CONSTRAINTS
// -discounts will contain between 1 and 50 elements, 
// inclusive.
// -Each element of discounts will be formatted "COST 
// PERCENT" (quotes for clarity), where COST and PERCENT are 
// integers with no leading zeros.
// -Each COST will be between 1 and 10,000,000, inclusive.
// -Each PERCENT will be between 1 and 3, inclusive.
// -price will be between 1 and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"1 1", "1 2", "1 3"}
// 100
// 
// Returns: 97.06
// 
// The best choice is to take 3% and 2% discounts. You pay 2 
// for unpopular models and reduce the cost of the popular 
// model to 95.06.
// 
// 1)
// {"1000 1", "100 2", "10 3"}
// 33
// 
// Returns: 33.0
// 
// It doesn't make sense to use any discounts.
// 
// 2)
// {"10 2", "2 3", "6 2", "3 2", "3 1",
//  "2 3", "9 3", "4 3", "2 3", "10 1"}
// 
// 1000000000
// 
// Returns: 7.921497975738132E8
// 
// price is very large and discounts are cheap, so we use all 
// of them.
// 
// 3)
// {"8667276 2",
//  "3833771 1",
//  "9208836 1",
//  "5081823 3",
//  "3367749 1",
//  "4393655 2",
//  "552508 1",
//  "8648685 2",
//  "3798496 2",
//  "8104796 1"}
// 246918635
// 
// Returns: 2.415526549689562E8
// 
// 
// 
// END CUT HERE
#line 106 "DiscountCombination.cc"
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

VVI toksvvi(vector <string> inp,string delim)   
{   
  VVI ret;   
  for(int i=0;i<inp.size();i++)   
    ret.push_back(toksT<int>(inp[i],delim));   
  return ret;   
}   

int n;
VVI d;
int p;
bool done[51][51][51][51];
double memo[51][51][51][51];

long double go(int pos, int one, int two, int th) {
  if (done[pos][one][two][th]){ 
    return memo[pos][one][two][th];
  }
  if (pos == n) {
    long double pr = p;
    fi(one) {
      pr *= 0.99;
    }
    fi(two) {
      pr *= 0.98;
    }
    fi(th) {
      pr *= 0.97;
    }
    done[pos][one][two][th]= 1;
    return memo[pos][one][two][th]=pr;
  }

  double &ret = memo[pos][one][two][th];
  done[pos][one][two][th] = 1;

  ret = go(pos + 1, one , two, th);

  int none = one;
  int ntwo = two;
  int nth = th;
  if (d[pos][1] == 1)  none++;
  else if (d[pos][1] == 2) ntwo++;
  else nth++;

  ret <?= go(pos + 1, none, ntwo, nth) + d[pos][0];

  return ret;
}

    class DiscountCombination
        { 
        public: 
        double minimumPrice(vector <string> discounts, int price) 
            { 
              d = toksvvi(discounts, " ");
              n = d.size();
              p = price;
              memset(done, 0, sizeof(done));

              return go(0, 0, 0, 0);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3", "2 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; double Arg2 = 97.06; verify_case(0, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1000 1", "100 2", "10 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 33; double Arg2 = 33.0; verify_case(1, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"10 2", "2 3", "6 2", "3 2", "3 1",
 "2 3", "9 3", "4 3", "2 3", "10 1"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; double Arg2 = 7.921497975738132E8; verify_case(2, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"8667276 2",
 "3833771 1",
 "9208836 1",
 "5081823 3",
 "3367749 1",
 "4393655 2",
 "552508 1",
 "8648685 2",
 "3798496 2",
 "8104796 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 246918635; double Arg2 = 2.415526549689562E8; verify_case(3, Arg2, minimumPrice(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        DiscountCombination ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

