/*
ID:  dhyanes1
LANG: C++
PROG: paint2
*/
#include <cstdio>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

int loc[100005][2];
bool pos[105][105];
int n,k;

bool inb(int x, int y) {
	return x >= 0 && y >=0 && x < n && y < n;
}

bool ok(int x1, int y1, int x2, int y2) {
	if (x1 == x2 || y1 == y2) {
		return true;
	}

	if (abs(x1 - x2) == abs(y1 - y2)) return true;

	return false;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("paint2.in","r");
  fout = fopen("paint2.out","w");
	fscanf(fin, "%d %d", &n, &k);
	memset(pos, 0, sizeof(pos));
	for (int i = 0; i < k; ++i) {
		fscanf(fin, "%d %d", &loc[i][0], &loc[i][1]);
		loc[i][0]--;
		loc[i][1]--;
	}
	list<pair<int, int> > pts;
	int dx[] = { 1, 1, 1, -1, -1, -1, 0, 0} ;
	int dy[] = { 1, -1, 0, -1, 1, 0, 1, -1} ;
	pts.push_back(make_pair(loc[0][0], loc[0][1]));
	for (int i = 0; i < 8; ++i) {
		int nx = loc[0][0];
		int ny = loc[0][1];
		while (1) {
			nx += dx[i];
			ny += dy[i];
			if (!inb(nx, ny)) break;
			pts.push_back(make_pair(nx, ny));
		}
	}
	for (int i = 1; i < k; ++i) {
		for(list<pair<int, int> >::iterator itr = pts.begin();
				itr != pts.end(); ) {
			if (!ok(loc[i][0], loc[i][1], itr->first, itr->second)) {
				itr = pts.erase(itr);
			} else ++itr;
		}
	}
	fprintf(fout, "%d\n", pts.size());
  fclose(fout);
  fclose(fin);
  return 0;
}
