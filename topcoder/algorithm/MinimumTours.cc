// BEGIN CUT HERE
// PROBLEM STATEMENT
// Little Bonnie has taken a vacation to Ha Long Bay.  There 
// are a few thousand stone islands in the bay, making it one 
// of the most beautiful natural scenes in Vietnam.  Bonnie 
// is so impressed by this fact that she has decided to visit 
// all of the islands.
// 
// 
// She bought a map of all the islands in the bay.  This map 
// is given in the vector <string> islandMap, which is a two-
// dimensional matrix where each cell is either '.' or 
// lowercase 'x'.  '.' cells represent sea and 'x' cells 
// represent land.  Two cells are connected if they have a 
// point in common, so each cell may connect to at most 8 
// other cells.  An island is defined as a maximal connected 
// group of 'x' cells.  A trip between two islands is defined 
// as a connected group of '.' cells where, for each of the 
// two islands, there is at least one '.' cell in the trip 
// which is connected to a cell in that island.  If there is 
// no such connected group of '.' cells between two islands, 
// then there is no trip between them.  Note that an island 
// can be nested inside another island.
// 
// 
// A tour is a sequence of islands where there is a trip 
// between every pair of consecutive islands in the 
// sequence.  Little Bonnie wants to visit every island 
// exactly once, and she wants to do this using the minimum 
// possible number of tours.  Return the number of tours she 
// will have to take.
// 
// 
// DEFINITION
// Class:MinimumTours
// Method:getMinimumTours
// Parameters:vector <string>
// Returns:int
// Method signature:int getMinimumTours(vector <string> 
// islandMap)
// 
// 
// NOTES
// -It is possible for a tour to have only one island.
// -Bonnie cannot leave the mapped area at any time.
// -It is assumed that Bonnie has another way to travel from 
// the last island of one tour to the first island of another 
// tour, so you don't have to take this into account when 
// solving the problem.
// 
// 
// CONSTRAINTS
// -islandMap will contain between 1 and 50 elements, 
// inclusive.
// -Each element of islandMap will contain between 1 and 50 
// characters, inclusive.
// -Each element of islandMap will contain the same number of 
// characters.
// -Each character in islandMap will be either '.' or 
// lowercase 'x'.
// -There will be at least one island in the map.
// 
// 
// EXAMPLES
// 
// 0)
// {
// "..x..x..x..",
// "..x..x..x..",
// "..x..x..x..",
// "..x..x..x.."
// }
// 
// Returns: 1
// 
// Only one tour is needed. Bonnie can just go from the 
// leftmost island through the middle one to the rightmost 
// island. Or she can choose to go in the reverse way.
// 
// 1)
// {
// "x....x....x",
// ".....x.....",
// ".....x.....",
// ".....x.....",
// "xxxxxxxxxxx",
// ".....x.....",
// ".....x.....",
// ".....x.....",
// "x....x....x"
// }
// 
// Returns: 3
// 
// At least three tours are required to cover the five 
// islands. One possible set of three tours is to go from the 
// small island in the top-left corner through the big cross-
// shaped island to the top-right island, and each of the two 
// other islands makes up a one-island tour.
// 
// 2)
// {
// "x....x....x",
// ".....x.....",
// ".....x.....",
// "....x.x....",
// "xxxx...xxxx",
// "....x.x....",
// ".....x.....",
// ".....x.....",
// "x....x....x"
// }
// 
// Returns: 1
// 
// There is always a trip between any two islands. So only 
// one tour is enough to visit all five islands.
// 
// 3)
// {
// "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
// "x............................x",
// "x..xxxxxxxxxx....xxxxxxxxxx..x",
// "x..x........x....x........x..x",
// "x..x..xxxx..x....x.xxxxxx.x..x",
// "x..x........x....x.x....x.x..x",
// "x..xxxxxxxxxx....x.x.x..x.x..x",
// "x................x.x....x.x..x",
// "x................x.xxxxxx.x..x",
// "x..xxxxxxxxxx....x........x..x",
// "x..x........x....x........x..x",
// "x..x..xxxx..x....x.xxxxxx.x..x",
// "x..x........x....x........x..x",
// "x..xxxxxxxxxx....xxxxxxxxxx..x",
// "x............................x",
// "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
// }
// 
// Returns: 2
// 
// An island can be nested inside another one. And two tours 
// are needed in this example.
// 
// 4)
// {
// "xxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxx",
// "x...........x....x.....................",
// "x.xxxxxxxxx.x....x.xxxxxxxxxxxxxxxxxxx.",
// "x.x.......x.x....x.x.................x.",
// "x.x.xxxxx.x.x....x.x.xxxxxxxxxxx.....x.",
// "x.x...x...x.x....x.x.x..........x....x.",
// "x.x...x...x.x....x.x.x.xxx..xxx...x..x.",
// "x.x.......x.x....x.x.x.x....x..x..x..x.",
// "x.xxxxxxxxx.x....x.x.x.xxx..x..x..x..x.",
// "x...........x....x.x.x.x....x..x..x..x.",
// "xxxxxxxxxxxxx....x.x.x.xxx..xxx...x..x.",
// "x................x.x.x......xx....x..x.",
// "x................x.x.x......x.x...x..x.",
// "x................x.x.x......x..x..x..x.",
// "x................x.x.x...........x...x.",
// "x................x.x.xxxxxxxxxxxx....x.",
// "x................x.x.................x.",
// "x................x.xxxxxxxxxxxxxxxxxxx.",
// "x................x.....................",
// "x................xxxxxxxxxxxxxxxxxxxxxx"
// }
// 
// Returns: 1
// 
// 
// 
// END CUT HERE
#line 174 "MinimumTours.cc"
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

VS is;
int m,n;
VVI mat;

int inb(int x, int y) {
  return x >= 0 && y  >= 0 && x < m && y < n;
}

void color(int x, int y, char ch) {
  if (!inb(x,y)) return;
  if (is[x][y] != 'x') return;
  is[x][y] = ch;
  int dx[] = { 1, 1, 1, -1 , -1 , -1 , 0 , 0 };
  int dy[] = { 1, -1, 0, 1 , -1 , 0 , 1 , -1 };

  fi(8) {
    color(x + dx[i], y + dy[i], ch);
  }
}

void dfs(int x, int y, int c) {
  if (!inb(x,y)) return;
  if (is[x][y] != '.') {
    mat[c][is[x][y] - '0'] = 1;
    mat[is[x][y] - '0'][c] = 1;
    if (is[x][y] != c + '0') return;
  }
  int dx[] = { 1, 1, 1, -1 , -1 , -1 , 0 , 0 };
  int dy[] = { 1, -1, 0, 1 , -1 , 0 , 1 , -1 };

  fi(8) {
    dfs(x + dx[i], y + dy[i], c);
  }
}

    class MinimumTours
        { 
        public: 
        int getMinimumTours(vector <string> islandMap) 
            { 
              is = islandMap;
              m  = is.size();
              n = is[0].size();

              int c = 0;
              fi(m) { 
                fj(n) {
                  if (is[i][j] == 'x') {
                    color(i,j,c + '0');
                  ++c;
                  }
                }
              }

              VI done(c, 0);
              mat.resize(c);
              fi(c)
                mat.resize(c);

              fi(m) {
                fj(n) {
                  if (is[i][j] != '.' && !done[is[i][j] - '0']) {
                    dfs(i,j, is[i][j] - '0');
                  }
                }
              }
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"..x..x..x..",
"..x..x..x..",
"..x..x..x..",
"..x..x..x.."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, getMinimumTours(Arg0)); }
	void test_case_1() { string Arr0[] = {
"x....x....x",
".....x.....",
".....x.....",
".....x.....",
"xxxxxxxxxxx",
".....x.....",
".....x.....",
".....x.....",
"x....x....x"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, getMinimumTours(Arg0)); }
	void test_case_2() { string Arr0[] = {
"x....x....x",
".....x.....",
".....x.....",
"....x.x....",
"xxxx...xxxx",
"....x.x....",
".....x.....",
".....x.....",
"x....x....x"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getMinimumTours(Arg0)); }
	void test_case_3() { string Arr0[] = {
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
"x............................x",
"x..xxxxxxxxxx....xxxxxxxxxx..x",
"x..x........x....x........x..x",
"x..x..xxxx..x....x.xxxxxx.x..x",
"x..x........x....x.x....x.x..x",
"x..xxxxxxxxxx....x.x.x..x.x..x",
"x................x.x....x.x..x",
"x................x.xxxxxx.x..x",
"x..xxxxxxxxxx....x........x..x",
"x..x........x....x........x..x",
"x..x..xxxx..x....x.xxxxxx.x..x",
"x..x........x....x........x..x",
"x..xxxxxxxxxx....xxxxxxxxxx..x",
"x............................x",
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, getMinimumTours(Arg0)); }
	void test_case_4() { string Arr0[] = {
"xxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxx",
"x...........x....x.....................",
"x.xxxxxxxxx.x....x.xxxxxxxxxxxxxxxxxxx.",
"x.x.......x.x....x.x.................x.",
"x.x.xxxxx.x.x....x.x.xxxxxxxxxxx.....x.",
"x.x...x...x.x....x.x.x..........x....x.",
"x.x...x...x.x....x.x.x.xxx..xxx...x..x.",
"x.x.......x.x....x.x.x.x....x..x..x..x.",
"x.xxxxxxxxx.x....x.x.x.xxx..x..x..x..x.",
"x...........x....x.x.x.x....x..x..x..x.",
"xxxxxxxxxxxxx....x.x.x.xxx..xxx...x..x.",
"x................x.x.x......xx....x..x.",
"x................x.x.x......x.x...x..x.",
"x................x.x.x......x..x..x..x.",
"x................x.x.x...........x...x.",
"x................x.x.xxxxxxxxxxxx....x.",
"x................x.x.................x.",
"x................x.xxxxxxxxxxxxxxxxxxx.",
"x................x.....................",
"x................xxxxxxxxxxxxxxxxxxxxxx"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, getMinimumTours(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        MinimumTours ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

