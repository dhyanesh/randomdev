// BEGIN CUT HERE
// PROBLEM STATEMENT
// You've been given the blueprint for a trainyard which was 
// laid out on a grid.  Some grid cells have East-West track 
// segments (marked with '-'), some have North-South track 
// segments (marked with '|'), and others are intersections 
// (marked with '+').  Cells with no track are marked with a 
// '.' character. A train may enter an intersection square 
// from any direction and may leave in any direction.  Trains 
// may enter a North-South track segment from either the 
// North or South, and must exit the square moving in the 
// same direction.  Thus if a train enters a North-South 
// segment from the South, it must leave to the North.  East-
// West tracks work the same way, except with directions East 
// and West.  Squares without track may not be entered, and 
// the train may not leave the area covered by the grid.  The 
// train always occupies a single grid location, and each 
// square moved requires one unit of fuel.
//  
// The train's starting location is marked on the map with an 
// 'S' character.  Trains may exit this location going any 
// direction.  Given the trainyard map in layout and the fuel 
// available in fuel, you want to determine how many grid 
// squares may be reached.  You do not need to construct one 
// route that reaches all these squares; rather, you are 
// determining which squares could be reached using any legal 
// route beginning at the 'S' location.  A legal route may 
// use some, all, or none of the fuel.  Return the number of 
// distinct grid squares that can be reached, including the 
// initial 'S' location.
// 
// 
// DEFINITION
// Class:Trainyard
// Method:reachableSquares
// Parameters:vector <string>, int
// Returns:int
// Method signature:int reachableSquares(vector <string> 
// layout, int fuel)
// 
// 
// CONSTRAINTS
// -layout will contain between 1 and 10 elements, inclusive.
// -Each element of layout will contain between 1 and 10 
// characters, inclusive.
// -Each element of layout will contain the same number of 
// characters.
// -Each element of layout will contain only the characters 
// '-','|','+','.', and 'S'.
// -layout will contain exactly one 'S' character.
// -fuel will be between 1 and 10, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {
// ".-....",
// "-S---.",
// "......"}
// 2
// 
// Returns: 4
// 
// The train can reach the initial 'S', as well as one square 
// to the West.  It could also reach two squares to the East 
// (but not the third, as there's only 2 units of fuel). It 
// can't move North to start, as it can't enter an East-West 
// segment from the South.
// 
// 1)
// {
// "..+-+.",
// "..|.|.",
// "S-+-+."}
// 10
// 
// Returns: 10
// 
// All 9 of the track segments are reachable, plus 1 for the 
// 'S' square.  Be sure not to count squares twice!
// 
// 2)
// {
// "-....-",
// "|....+",
// "+-S++|",
// "|.|..|",
// "..+-++"}
// 8
// 
// Returns: 15
// 
// All of the track segments are reachable except for the two 
// at the North end that seem to be oriented the wrong way.
// 
// 3)
// {
// ".|...",
// "-+S+|",
// ".|..."}
// 5
// 
// Returns: 6
// 
// The track segment on the far East side is not reachable - 
// as you can't enter a North-South segment from the West.
// 
// END CUT HERE
#line 111 "Trainyard.cpp"
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

int done[20][20];
int m,n;

bool inb(int x, int y) {
	return x>=0 && x < m && y >=0 && y <n;
}

    class Trainyard
        { 
        public: 
        int reachableSquares(vector <string> l, int fuel) 
            { 
							memset(done, 0xff, sizeof(done));
							queue<pair<int, int> > bfs;
							m = l.size();
							n = l[0].size();
							pair<int, int > st;
							fi(l.size())
								fj(n) {
									if (l[i][j] == 'S') {
										st.first = i;
										st.second = j;
										done[i][j] = fuel;
										break;
									}
								}

							bfs.push(st);

							while (!bfs.empty()) {
								pair<int, int> curr = bfs.front();
								bfs.pop();

								int x = curr.first;
								int y = curr.second;

								if (done[x][y] == 0) continue;

								if (l[curr.first][curr.second] == 'S' ||
										l[curr.first][curr.second] == '+') {
									int dx[] = {1,-1,0,0};
									int dy[] = {0,0,1,-1};
									fi(2) {
										if (!inb(x+dx[i], y+dy[i]) ||
												l[x+dx[i]][y+dy[i]] == '-' ||
												l[x+dx[i]][y+dy[i]] == '.') continue;

										if (done[x+dx[i]][y+dy[i]] < 0) {
											bfs.push(make_pair(x+dx[i], y + dy[i]));
											done[x+dx[i]][y+dy[i]] = done[x][y] - 1;
										}
									}
									f(i,2,4){
										if (!inb(x+dx[i], y+dy[i]) ||
												l[x+dx[i]][y+dy[i]] == '|' ||
												l[x+dx[i]][y+dy[i]] == '.') continue;

										if (done[x+dx[i]][y+dy[i]] < 0) {
											bfs.push(make_pair(x+dx[i], y + dy[i]));
											done[x+dx[i]][y+dy[i]] = done[x][y] - 1;
										}
									}
								} else if (l[x][y] == '|') {
									for(int i = -1; i <= 1; i+=2) {
										if (!inb(x+i, y) ||
												l[x+i][y] == '-'||
												l[x+i][y] == '.') continue;

										if (done[x+i][y] < 0) {
											bfs.push(make_pair(x+i, y ));
											done[x+i][y] = done[x][y] - 1;
										}
									}
								} else {
									for(int i = -1; i <= 1; i+=2) {
										if (!inb(x, y + i) ||
												l[x][y+i] == '|'||
												l[x][y+i] == '.') continue;

										if (done[x][y + i] < 0) {
											bfs.push(make_pair(x, y+i ));
											done[x][y+i] = done[x][y] - 1;
										}
									}
								}

							}

							int ret = 0;
							fi(m) {
								fj(n) {
								if (done[i][j]>=0)
									ret++;
								}
							}
							return ret;	
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
".-....",
"-S---.",
"......"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; verify_case(0, Arg2, reachableSquares(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {
"..+-+.",
"..|.|.",
"S-+-+."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 10; verify_case(1, Arg2, reachableSquares(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {
"-....-",
"|....+",
"+-S++|",
"|.|..|",
"..+-++"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 15; verify_case(2, Arg2, reachableSquares(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {
".|...",
"-+S+|",
".|..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 6; verify_case(3, Arg2, reachableSquares(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Trainyard ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

