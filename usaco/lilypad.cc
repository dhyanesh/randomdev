/*
ID:  dhyanes1
LANG: C++
PROG: lilypad
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

typedef unsigned long long ull;

using namespace std;

int m,n;
int ex,ey;
int grid[35][35];

pair<int, ull> memo[35][35];

bool inb(int x, int y) {
	return x>=0 && y>=0 && x<m && y<n && grid[x][y] != 2;
}

pair<int, ull> go(int x, int y) {
	pair<int, ull> &ret = memo[x][y];
	if (ret.first >= -2) return ret;
	if (x == ex && y == ey) {
		ret.first = 0;
		ret.second = 1;
		return ret;
	}
	ret.first = -2;
	ret.second = 0;
	int dx[] = { 1, -1, 1, -1, 2, -2, 2, -2 };
	int dy[] = { 2, 2, -2, -2, 1, 1, -1, -1};
	int minnum = 1<<30;
	int mincou = 0;
	for(int i = 0; i < 8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!inb(nx,ny)) continue;

		pair<int, ull> t = go(nx, ny);
		if (t.first >= 0) {
			if (minnum == t.first) {
				mincou += t.second;
			}
			if (t.first < minnum) {
				minnum = t.first;
				mincou = t.second;
			}
		}
	}

	if (minnum == 1<<30) { 
		ret.first = -1;
		return ret;
	}

	ret.first = minnum;
	ret.second = mincou;

	if (grid[x][y] == 0) {
		ret.first++;
	}

	return ret;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("lilypad.in","r");
  fout = fopen("lilypad.out","w");
	memset(grid, 0, sizeof(grid));
	fscanf(fin, "%d %d", &m, &n);
	int sx,sy;
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			fscanf(fin, "%d", &grid[i][j]);
			if (grid[i][j] == 3) {
				sx = i; sy = j;
			}
			if (grid[i][j] == 4) {
				ex = i; ey = j;
			}
		}
	}
	for(int i = 0; i < 35; ++i) {
		for(int j = 0; j < 35; ++j) {
			memo[i][j].first = -3;
			memo[i][j].second  =  0;
		}
	}
	pair<int, ull> ans = go(sx, sy);
	fprintf(fout, "%d\n", ans.first);
	if (ans.first != -1) {
		fprintf(fout, "%llu\n", ans.second);
	}
  fclose(fout);
  fclose(fin);
  return 0;
}
