#line 133 "LandAndSea.cpp"
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

int num[55][55];
VS se;
int m,n;

int limx[2505][2];
int limy[2505][2];

bool inb(int i, int j) {
	return i >= 0 && i < m && j>=0 && j < n;
}

void dfs(int x, int y, int curr) {

	if (num[x][y] != -1 || se[x][y] != 'x')
		return;

	num[x][y] = curr;
	limx[curr][0] <?= x;
	limx[curr][1] >?= x;
	limy[curr][0] <?= y;
	limy[curr][1] >?= y;

	int dx[] = { 1, 1, -1, -1, 1, -1, 0, 0 };
	int dy[] = { 1, -1, -1, 1, 0, 0, 1, -1 };

	fi(8) {
		if (inb(x + dx[i], y + dy[i])) 
			dfs(x + dx[i], y + dy[i], curr);
	}
}

int par[2505];

int done[55][55];

int level[2505];

bool inside(int i, int j) {
	return limx[i][0] >= limx[j][0] &&
		limx[i][1] <= limx[j][1] &&
		limy[i][0] >= limy[j][0] &&
		limy[j][1] <= limy[j][1];
}

    class LandAndSea
        { 
        public: 
        vector <int> howManyIslands(vector <string> seaMap) 
            { 
							memset(num, 0xff, sizeof(num));
							memset(limx, 0xff, sizeof(limx));
							memset(limy, 0xff, sizeof(limy));

							se = seaMap;
							m = se.size();
							n = se[0].size();

							map<int, pair<int,int> > st;
							int curr = 1;
							fi(m) 
								fj(n) {
									if (num[i][j] == -1 && se[i][j] == 'x') {
										st[curr] = make_pair(i,j);
										limx[curr][0] = i;
										limx[curr][1] = i;
										limy[curr][0] = j;
										limy[curr][1] = j;
										dfs(i,j, curr);
										curr++;
									}
								}

							if (curr == 1) return vector<int>();

							memset(par, 0xff, sizeof(par));

							f(i, 1,curr) {
								memset(done, 0, sizeof(done));
								queue<pair<int, int> > bfs;
								done[st[i].first][st[i].second] = 1;
								bfs.push(make_pair(st[i].first, st[i].second));

								int dx[] = { 1, -1, 0, 0 };
								int dy[] = { 0, 0, 1, -1 };

								int pa = -1;
								while (!bfs.empty()) {
									pair<int,int> te = bfs.front();
									bfs.pop();

									bool out = false;
									fj(4) {
										int nx = te.first + dx[j];
										int ny =te.second + dy[j];

										if (done[nx][ny]) continue;

										if (!inb(nx, ny)){
											out = true;
											break;
										}
										if (se[nx][ny] == '.' || num[nx][ny] == i) {
											done[nx][ny] = 1;
											bfs.push(make_pair(nx,ny));
										} else if (inside(i, num[nx][ny])) {
											pa = num[nx][ny];
										}
									}

									if (out) {
										pa = -1;
										break;
									}
								}
								par[i] = pa;
							}

							memset(level, 0, sizeof(level));

							f(i,1,curr) {
								int pa = par[i];
								int lev = 0;
								while (pa != -1) {
									level[pa] >?= lev + 1;
									pa = par[pa];
									lev++;
								}
							}
							
							int max = 0;
							f(i,1,curr) {
								max >?= level[i];
							}

							vector<int> ret(max + 1, 0);

							f(i,1,curr) {
								ret[level[i]]++;
							}

							return ret;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
