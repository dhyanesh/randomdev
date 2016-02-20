/*
ID:  dhyanes1
LANG: C++
PROG: cgame
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

int arr[50005][2];
int n;

struct mem {
	mem(int _p, int _x, int _y) : p(_p), x(_x), y(_y) { }
	int p,x,y;
};

map<mem, int> dist;

int go(int pos, int x, int y) {
	if (pos == n) {
		return abs(x) + abs(y);
	}
	mem t(pos,x,y);
	if (dist.count(t) > 0) return dist[t];

	int &ret = dist(t);

	return ret;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("cgame.in","r");
  fout = fopen("cgame.out","w");
	int cas;
	dist.clear();
	fscanf(fin, "%d %d", &cas, &n);
	for (int i = 0; i < n; ++i) {
		fscanf(fin, "%d %d", &arr[i][0], &arr[i][1]);
	}
	int d = go(1, 0, 0);
	assert(d == 0);
  fclose(fout);
  fclose(fin);
  return 0;
}
