// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// The king of Absurdistan has become very angry, and thus he 
// has decided to make an evil reform of the road network.
// 
// 
// 
// Currently, the network contains several towns, connected 
// by some one-way and some two-way streets. The king's goal 
// is to change all two-way streets into one-way streets. 
// That is, for each currently present two-way street the 
// king will pick one of the two directions,
// and make the street one-way in the chosen direction.
// 
// 
// 
// To make it even worse, the king has a simple goal he wants 
// to achieve: After the reform the network must be so evil 
// that once someone starts traveling along the roads, he 
// will never be able to return back to the town where he 
// started.
// 
// 
// 
// You will be given the current map as a vector <string> 
// roads. 
// 
// 
// 
// More precisely, the towns are numbered from 0 to N-1 for 
// some N.
// The j-th character of the i-th element of roads is 'Y' if 
// there is a direct road that allows us to travel from i to 
// j, otherwise it will be 'N'.
// Each pair of towns is connected by at most one direct 
// road. If the input contains a 'Y' both for a i->j road and 
// for a j->i road, this means that the road between i and j 
// is currently two-way.
// 
// 
// 
// Write a method that will return
// either "YES" or "NO" (quotes for clarity), depending on 
// whether the king can achieve his evil goal.
// 
// 
// DEFINITION
// Class:OneWayStreets
// Method:canChange
// Parameters:vector <string>
// Returns:string
// Method signature:string canChange(vector <string> roads)
// 
// 
// CONSTRAINTS
// -roads will contain N elements, where N is between 2 and 
// 50, inclusive.
// -Each element of roads will contain exactly N characters.
// -Each character in each element of roads will be either 
// 'Y' or 'N'.
// -For each i the i-th character of the i-th element of 
// roads will be 'N'.
// 
// 
// EXAMPLES
// 
// 0)
// {"NYN","NNY","NNN"}
// 
// Returns: "YES"
// 
// This map contains two roads: 0->1 and 1->2. Both roads are 
// already one-way, so the king can't change
// anything.
// However, the map already has the desired property.
// 
// 1)
// {"NYN","YNY","NYN"}
// 
// Returns: "YES"
// 
// This map contains two roads: 0<->1 and 1<->2. Both roads 
// are two-way. The king can change them to
// one-way streets 0->1 and 1->2, thus creating the situation 
// from the previous example.
// 
// 
// 2)
// {"NYNN","NNYN","YNNY","NNYN"}
// 
// Returns: "NO"
// 
// Roads: 0->1, 1->2, 2->0, and 2<->3.
// The king may change 2<->3 either to 2->3, or to 3->2.
// Neither of these changes will help him, as people will 
// still be able to leave town 0 and return back
// via the route 0->1->2->0.
// 
// 
// 3)
// {"NNN","NNN","NNN"}
// 
// Returns: "YES"
// 
// 
// 
// 4)
// {"NYYYY","YNYYY","YYNYY","YYYNY","YYYYN"}
// 
// Returns: "YES"
// 
// 
// 
// END CUT HERE
#line 117 "OneWayStreets.cc"
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

bool grid[55][55];
bool done[55];
int path[55];

    class OneWayStreets
        { 
        public: 
        string canChange(vector <string> roads) 
            { 
              int n = roads.size();

              fi(n) {
                fj(n) {
                  if (roads[i][j]=='Y') grid[i][j]=true;
                  else grid[i][j] = false;
                }
              }
              VI a,b;
              fi(n) {
                f(j, i+1, n) {
                  if (grid[i][j] == grid[j][i] && grid[i][j] == true) {
                    a.push_back(i),b.push_back(j);
                    grid[i][j] = grid[j][i] = false;
                  }
                }
              }

              f(k,0,n) {
                fi(n)
                  fj(n)
                  if (grid[i][k] && grid[k][j]) grid[i][j]=true;
              }

              fi(n) if (grid[i][i]) return "NO";

              return "YES";
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN","NNY","NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(0, Arg1, canChange(Arg0)); }
	void test_case_1() { string Arr0[] = {"NYN","YNY","NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(1, Arg1, canChange(Arg0)); }
	void test_case_2() { string Arr0[] = {"NYNN","NNYN","YNNY","NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(2, Arg1, canChange(Arg0)); }
	void test_case_3() { string Arr0[] = {"NNN","NNN","NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(3, Arg1, canChange(Arg0)); }
	void test_case_4() { string Arr0[] = {"NYYYY","YNYYY","YYNYY","YYYNY","YYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(4, Arg1, canChange(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        OneWayStreets ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

