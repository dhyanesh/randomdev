// BEGIN CUT HERE
// PROBLEM STATEMENT
// Some pedestrians are crossing a road. A car arrives at the 
// crosswalk and wants to pass through, but can only get by 
// if there's an empty gap of at least carWidth centimeters. 
// The road is roadWidth centimeters wide. All the 
// pedestrians are walking in the same direction.
// 
// You are given a vector <string> pedestrians, each element 
// of which is formatted as "T V" (quotes for clarity), where 
// T is the time that one pedestrian starts crossing the road 
// (in seconds), and V is his walking speed (in centimeters 
// per second). The car arrives at time carArrival seconds. 
// The car can pass through at any time after its arrival 
// (including the moment of arrival), when there is 
// sufficient free space to pass through. Return a double 
// indicating the earliest time (in seconds) the car can pass 
// through.
// 
// DEFINITION
// Class:RoadCrossing
// Method:passTime
// Parameters:vector <string>, int, int, int
// Returns:double
// Method signature:double passTime(vector <string> 
// pedestrians, int roadWidth, int carWidth, int carArrival)
// 
// 
// NOTES
// -The returned value must have an absolute or relative 
// error less than 1e-9.
// -The car passes through instantly, i.e., it takes no time 
// for the car to pass through.
// 
// 
// CONSTRAINTS
// -pedestrians will contain between 0 and 50 elements, 
// inclusive.
// -Each element of pedestrians will be formatted as "T V" 
// (quotes for clarity), where T and V are integers with no 
// extra leading zeros.
// -Each T will be between 0 and 1000, inclusive.
// -Each V will be between 1 and 1000, inclusive.
// -roadWidth will be between 1 and 1000, inclusive.
// -carWidth will be between 1 and roadWidth, inclusive.
// -carArrival will be between 1 and 1000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"0 1", "2 5"}
// 8
// 4
// 3
// 
// Returns: 3.5
// 
// At time 3.5, the pedestrians are 3.5 and 7.5 centimeters 
// from the side of the road. The car can pass through the 4 
// centimeter gap between the pedestrians. This is the 
// earliest time it can pass through.
// 
// 1)
// {"40 1"}
// 100
// 100
// 41
// 
// Returns: 140.0
// 
// The pedestrian starts crossing the road at time 40. At 
// time 41, the car arrives, and the pedestrian is 1 cm from 
// the side of the road. The car needs the entire width of 
// the road to pass through, and therefore, it must wait 
// until the pedestrian finishes crossing. The pedestrian 
// reaches the other side of the road at time 140.
// 
// 2)
// {"0 1", "0 2", "0 4", "0 8", "0 16", "0 32", "0 64", "0 
// 128", "0 256"}
// 100
// 50
// 3
// 
// Returns: 3.125
// 
// 
// 
// 3)
// {"0 1", "0 2", "0 4", "0 8", "0 16", "0 32", "0 64", "0 
// 128", "0 256"}
// 100
// 51
// 3
// 
// Returns: 51.0
// 
// 
// 
// 4)
// {"1000 1", "100 1"}
// 1000
// 1000
// 1000
// 
// Returns: 2000.0
// 
// Maximal possible answer.
// 
// END CUT HERE
#line 113 "RoadCrossing.cpp"
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
#include <queue>    
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
typedef long double ld;


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

    class RoadCrossing
        { 
        public: 
        double passTime(vector <string> ped, int rw, int cw, int ca) 
            { 
							VVI p = toksvvi(ped, " ");

							priority_queue<ld, vector<ld>,
								greater<ld> > times; 
							times.push(ca);

							fi(p.size()) {
								ld arr = p[i][0] + cw / (ld) p[i][1];
								if (arr > ca || fabsl(arr - ca) < 1.0e-9)
									times.push(arr);
								arr = p[i][0] + rw / (ld) p[i][1];
								if (arr > ca || fabsl(arr - ca) < 1.0e-9)
									times.push(arr);
							}

							while (!times.empty()) {
								ld ti = times.top();
								times.pop();

								vector<pair<ld, int> > pos;
								fi(p.size())  {
									if (ti > p[i][0] ||
											fabsl(ti - p[i][0]) < 1.0e-9) {
										ld po = p[i][1] * (ti - p[i][0]);
										if (po < rw)
											pos.push_back(make_pair(po, i));
									}
								}
								if (pos.size() == 0) return ti;
								sort(pos.begin(), pos.end());

								if (pos[0].first > cw || fabsl(pos[0].first - cw) < 1.0e-9) return ti;

								f(i,1,pos.size()) {
									if (pos[i].first - pos[i - 1].first > cw ||
											fabsl((pos[i].first - pos[i-1].first) - cw) < 1.0e-9) {
										return ti;
									}

									int i1 = pos[i].second;
									int i2 = pos[i-1].second;

									if (p[i1][1] > p[i2][1]) {
										ld nt = cw - (pos[i].first - pos[i-1].first);

										nt /= (p[i1][1] - p[i2][1]);
										times.push(ti + nt);
									} else if (p[i1][1] < p[i2][1]) {
										ld nt = (pos[i].first - pos[i-1].first);

										nt /= (p[i2][1] - p[i1][1]);
										times.push(ti + nt);

										nt = (pos[i].first - pos[i-1].first) + cw;

										nt /= (p[i2][1] - p[i1][1]);
										times.push(ti + nt);
									}
								}

								int n = pos.size() - 1;
								if ((rw - pos[n].first) > cw ||
										fabsl((rw - pos[n].first) - cw) < 1.0e-9) {
									return ti;
								}
							}

							ld max = 0.0;
							fi(p.size()) {
								max >?= p[i][0] + rw / (ld)(p[i][1]);
							}

							return max;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 1", "2 5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 4; int Arg3 = 3; double Arg4 = 3.5; verify_case(0, Arg4, passTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"40 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 100; int Arg3 = 41; double Arg4 = 140.0; verify_case(1, Arg4, passTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"0 1", "0 2", "0 4", "0 8", "0 16", "0 32", "0 64", "0 128", "0 256"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 50; int Arg3 = 3; double Arg4 = 3.125; verify_case(2, Arg4, passTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"0 1", "0 2", "0 4", "0 8", "0 16", "0 32", "0 64", "0 128", "0 256"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 51; int Arg3 = 3; double Arg4 = 51.0; verify_case(3, Arg4, passTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { string Arr0[] = {"1000 1", "100 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 1000; int Arg3 = 1000; double Arg4 = 2000.0; verify_case(4, Arg4, passTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        RoadCrossing ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

