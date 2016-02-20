// BEGIN CUT HERE
// PROBLEM STATEMENT
// A redundant storage system can survive a certain number of 
// hard drive failures without losing any data. You are doing 
// some analysis to determine the risk of various numbers of 
// drives failing during one week. Your task is complicated 
// by the fact that the drives in this system have different 
// failure rates. You will be given a vector <double> 
// containing n elements that describe the probability of 
// each drive failing during a week. Return a vector <double> 
// containing n + 1 elements, where element i is the 
// probability that exactly i drives will fail during a week. 
// Assume that drive failures are independent events.
// 
// DEFINITION
// Class:DriveFailures
// Method:failureChances
// Parameters:vector <double>
// Returns:vector <double>
// Method signature:vector <double> failureChances(vector 
// <double> failureProb)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative 
// or absolute value of 1E-9.
// -If events with probabilities p1 and p2 are independent, 
// then the probability of both occurring is p1p2.
// 
// 
// CONSTRAINTS
// -failureProb will contain between 1 and 15 elements, 
// inclusive.
// -Each element of failureProb will be between 0.0 and 1.0, 
// inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {1.0, 0.25, 0.0}
// 
// Returns: {0.0, 0.75, 0.25, 0.0 }
// 
// The first drive is guaranteed to fail, the second has a 
// 25% chance of failing, and the third is guaranteed not to 
// fail. So there is a 25% of two failures and a 75% chance 
// of only one failure.
// 
// 
// 1)
// {0.4, 0.7}
// 
// Returns: {0.18000000000000002, 0.54, 0.27999999999999997 }
// 
// There is a probability of 0.4 x 0.7 = 0.28 that both 
// drives will fail. The chance that only the first will fail 
// is 0.12 and that only the second will fail is 0.42, for a 
// total probability of 0.54 that exactly one drive will 
// fail. This leaves a probability of 0.18 that no drives 
// will fail.
// 
// 2)
// {0.2, 0.3, 0.0, 1.0, 0.8, 0.9}
// 
// Returns: {0.0, 0.011199999999999993, 0.15319999999999995, 
// 0.5031999999999999, 0.2892, 0.0432, 0.0 }
// 
// 
// 
// END CUT HERE
#line 73 "DriveFailures.cpp"
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

double p[50][50];

    class DriveFailures
        { 
        public: 
        vector <double> failureChances(vector <double> fp) 
            { 
							int n = fp.size();
							vector<double> ret(fp.size()+1);

							ret[0] = 1.0;
							fi(n) 
								ret[0] *= (1.0 - fp[i]);

							fi(n+1) fj(n+1) p[i][j] = 0.0;

							ret[1] = 0.0;
							fi(n) {
								double t = 1.0;
								fj(n)  {
									if (i==j) continue;
									t *= (1-fp[j]);
								}

								ret[1] = p[i][1] += fp[i] * t;
							}

							f(i,2,n+1) {
								fj(n) {
									f(k,0,n) {
										if (j==k) continue;

										if (fabs(1.0-fp[j]) > 1.0e-9)
										p[j][i] += p[k][i-1] * fp[j] / (1.0-fp[j]);
									}
								}
								ret[i] = 0.0;
								fj(n) {
									ret[i] += p[j][i];
								}
								ret[i] /= i;
							}

							return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { double Arr0[] = {1.0, 0.25, 0.0}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.0, 0.75, 0.25, 0.0 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, failureChances(Arg0)); }
	void test_case_1() { double Arr0[] = {0.4, 0.7}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.18000000000000002, 0.54, 0.27999999999999997 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, failureChances(Arg0)); }
	void test_case_2() { double Arr0[] = {0.2, 0.3, 0.0, 1.0, 0.8, 0.9}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.0, 0.011199999999999993, 0.15319999999999995, 0.5031999999999999, 0.2892, 0.0432, 0.0 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, failureChances(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        DriveFailures ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

