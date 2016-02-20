/*
ID:  dhyanes1
LANG: C++
PROG: hotel
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("hotel.in","r");
  fout = fopen("hotel.out","w");
	map<int,set<int> > free;
	int n,m;
	fscanf(fin, "%d %d", &n ,&m);
	for (int i = 0; i < m; ++i) {
		int type;
		fscanf(fin, "%d", &type);
		int no, st;
		if (type == 1) {
			fscanf(fin, "%d", &no);
			st = 1;
		} else {
			fscanf(fin, "%d %d", &st, &no);
		}
	}
  fclose(fout);
  fclose(fin);
  return 0;
}
