// BEGIN CUT HERE
// PROBLEM STATEMENT
// There is a NxN maze where each cell contains either a wall 
// or empty space.  You are currently in the top-left cell at 
// coordinates (0, 0) and your goal is to reach the bottom-
// right cell at coordinates (N-1, N-1) making as few turns 
// as possible.  You can choose any of the four cardinal 
// directions as your starting direction.  Then, from each 
// cell, you can either move forward one cell in your current 
// direction or turn left or right by 90 degrees.  You can 
// only walk into empty cells, not walls.
// 
// You are given ints M, X0, Y0, A, B, C and D. Generate 
// lists X and Y, each of length M, using the following 
// recursive definitions:
// X[0] = X0 MOD P 
// X[i] = (X[i-1]*A+B) MOD P (note that X[i-1]*A+B may 
// overflow a 32-bit integer)
// 
// Y[0] = Y0 MOD P 
// Y[i] = (Y[i-1]*C+D) MOD P (note that Y[i-1]*C+D may 
// overflow a 32-bit integer) 
// 
// Cell (x, y) of the maze contains a wall if and only if it 
// is neither the top-left cell nor the bottom-right cell and 
// there exists a value of i between 0 and M-1, inclusive, 
// such that x=X[i] MOD N and y=Y[i] MOD N.  Return the 
// minimum number of turns you must make to reach the bottom-
// right cell of this maze, or return -1 if it is impossible.
// 
// 
// DEFINITION
// Class:DoNotTurn
// Method:minimumTurns
// Parameters:int, int, int, int, int, int, int, int, int
// Returns:int
// Method signature:int minimumTurns(int N, int X0, int A, 
// int B, int Y0, int C, int D, int P, int M)
// 
// 
// NOTES
// -In the statement, "A MOD B" represents the remainder of 
// integer division of A by B. For example, 14 MOD 5 = 4 and 
// 20 MOD 4 = 0.
// -The author's solution does not depend on any properties 
// of the pseudorandom generator. It would solve any input of 
// allowed size within the given limits.
// 
// 
// CONSTRAINTS
// -N will be between 2 and 500, inclusive. 
// -M will be between 0 and 1,000,000, inclusive. 
// -X0, Y0, A, B, C and D will each be between 0 and 
// 1,000,000, inclusive.
// -P will be between 1 and 1,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// 0
// 0
// 1
// 0
// 0
// 1
// 10
// 2
// 
// Returns: 1
// 
// There are no walls, so you will have to make only one turn.
// 
// 1)
// 3
// 0
// 1
// 1
// 1
// 1
// 0
// 3
// 3
// 
// Returns: -1
// 
// The maze in this case looks as follows ('#' denotes a 
// wall, '.' denotes an empty cell):
// 
// .#.
// .#.
// .#.
// 
// The target is unreachable.
// 
// 2)
// 3
// 0
// 1
// 1
// 1
// 1
// 1
// 3
// 3
// 
// Returns: 3
// 
// The maze in this case looks as follows ('#' denotes a 
// wall, '.' denotes an empty cell):
// 
// .#.
// ..#
// #..
// 
// There is only one possible path and it requires 3 turns.
// 
// 3)
// 10
// 911111
// 845499
// 866249
// 688029
// 742197
// 312197
// 384409
// 40
// 
// Returns: 12
// 
// The maze and the optimal path in it are given below ('#' 
// denotes a wall, '.' denotes an empty cell, the path is 
// illustrated using 'p' characters):
// 
// pp##..#..#
// #pp..###..
// .#p#.....#
// ##p...#.#.
// .#p.##.#..
// ##p##.#...
// #pp####...
// pp#.#...#.
// p#pppp#...
// ppp##ppppp
// 
// 
// 4)
// 5
// 23
// 2
// 3
// 35
// 5
// 7
// 9
// 3
// 
// Returns: 2
// 
// The maze in this case looks as follows ('#' denotes a 
// wall, '.' denotes an empty cell):
// 
// ...#.
// .....
// ...#.
// .....
// ..#..
// 
// 
// 5)
// 2
// 0
// 0
// 0
// 0
// 0
// 0
// 1
// 0
// 
// Returns: 1
// 
// 
// 
// END CUT HERE
#line 188 "DoNotTurn.cc"
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
#include <queue>   
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

          int done[501][501][3][3];
    class DoNotTurn
        { 
          struct V {
            int x, y, xd, yd, dist;

            bool operator<(const V &oth) const {
              return dist > oth.dist;
            }
          };

        public: 
          bool iswall(int x, int y, set<pair<int,int> > &vals, int N) {
            if (x == 0 && y == 0) return false;
            if (x == N - 1 && y == N - 1) return false;
            pair<int,int> p(x,y);
            return vals.find(p) != vals.end();
          }

          bool inb(int x, int y, int n) {
            return x>=0 && y >=0 && x<n && y<n;
          }

        int minimumTurns(int N, ll X0, ll A, ll B, ll Y0, ll C, ll D, ll P, int M) { 

          VI x(M); VI y(M);

          x[0] = X0 % P;
          f(i,1,M) {
            x[i] = (x[i-1]*A+B) % P;
          }
          y[0] = Y0 % P;
          f(i,1,M) {
            y[i] = (y[i-1]*C+D) % P;
          }

          set<pair<int,int> > vals;
          fi(M) {
            vals.insert(make_pair(x[i] % N,y[i] % N));
          }

          fi(N) fj(N) f(k,0,3) f(m,0,3) done[i][j][k][m] = -1;
          priority_queue<V> bfs;
          V s;
          s.x = 0;
          s.y = 0;
          s.xd = 1;
          s.yd = 1;
          s.dist = 0;
          bfs.push(s);
          int dirx[] = {1, -1, 0, 0 };
          int diry[] = {0, 0, 1, -1 };

          while (!bfs.empty()) {
            V top = bfs.top();
            bfs.pop();
            if (top.x == N -1 && top.y == N -1 ) return top.dist;
            if (done[top.x][top.y][top.xd][top.yd] < 0) {
              done[top.x][top.y][top.xd][top.yd] = 1;

              fi(4) {
                int nx = top.x + dirx[i];
                int ny = top.y + diry[i];
                if (!inb(nx, ny, N)) {
                  continue;
                }
                if (iswall(nx, ny, vals, N)) {
                  continue;
                }

                int pdx = top.xd - 1;
                int pdy = top.yd - 1;

                int dist = top.dist;
                if (pdx != dirx[i] && pdy != diry[i] && (pdx != 0 || pdy != 0)) {
                  ++dist;
                }

                V n;
                n.x = nx;
                n.y = ny;
                n.xd = dirx[i] + 1;
                n.yd = diry[i] + 1;
                n.dist = dist;
                bfs.push(n);
              }
            }
          }

          return -1;
        } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 1; int Arg4 = 0; int Arg5 = 0; int Arg6 = 1; int Arg7 = 10; int Arg8 = 2; int Arg9 = 1; verify_case(0, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 0; int Arg7 = 3; int Arg8 = 3; int Arg9 = -1; verify_case(1, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 1; int Arg7 = 3; int Arg8 = 3; int Arg9 = 3; verify_case(2, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 911111; int Arg2 = 845499; int Arg3 = 866249; int Arg4 = 688029; int Arg5 = 742197; int Arg6 = 312197; int Arg7 = 384409; int Arg8 = 40; int Arg9 = 12; verify_case(3, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 23; int Arg2 = 2; int Arg3 = 3; int Arg4 = 35; int Arg5 = 5; int Arg6 = 7; int Arg7 = 9; int Arg8 = 3; int Arg9 = 2; verify_case(4, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_5() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1; int Arg8 = 0; int Arg9 = 1; verify_case(5, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        DoNotTurn ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    

