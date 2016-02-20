/*
ID:  dhyanes1
LANG: C++
PROG: newbarn
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct point {
	int x,y;
};

int n;
point pts[10005];

int findx(int x) {
	int ret = 0;
	for(int i = 0; i < n; ++i) {
		ret += abs(x - pts[i].x);
	}

	return ret;
}

int findy(int y) {
	int ret = 0;
	for(int i = 0; i < n; ++i) {
		ret += abs(y - pts[i].y);
	}

	return ret;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("newbarn.in","r");
  fout = fopen("newbarn.out","w");
	fscanf(fin, "%d", &n);
	int sumx = 0, sumy = 0;
	set<pair<int, int> > points;
	for(int i = 0; i < n; ++i) {
		fscanf(fin, "%d %d", &pts[i].x, &pts[i].y);
		sumx += pts[i].x;
		sumy += pts[i].y;
		points.insert(make_pair(pts[i].x, pts[i].y));
	}
	int basex = sumx / n;
	int basey = sumy / n;
	int dx[] = { 0, 1, 1, -1, -1, 0, 0, 1, -1};
	int dy[] = { 0, 0, -1, 1, 0, 1, -1, 1, -1 };
	int best = 1<<30;
	int count = 0;
	for(int i = 0; i < 9; ++i) {
		int x = basex + dx[i];
		int y = basey + dy[i];
		if (points.find(make_pair(x, y)) != points.end()) {
			continue;
		}
		int ans = findx(x) + findy(y);
		if (ans == best) {
			count++;
		}
		if (ans < best) {
			best = ans;
			count = 1;
		}
	}
	fprintf(fout, "%d %d\n", best, count);
  fclose(fout);
  fclose(fin);
  return 0;
}
