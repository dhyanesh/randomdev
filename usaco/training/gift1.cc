/*
ID:  dhyanes1
LANG: C++
PROG: gift1
*/
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;

char p[15][15];

map<string, pair<int, set<string> > > money;
map<string, int> final;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("gift1.in","r");
  fout = fopen("gift1.out","w");
	int n;
	fscanf(fin, "%d\n", &n);
	for (int i = 0; i < n; ++i) {
		fscanf(fin, "%s\n", p[i]);
	}
	char temp[30];
	while (fscanf(fin, "%s\n", temp) == 1) {
		int a, no;
		fscanf(fin, "%d %d\n", &a, &no);
		pair<int, set<string> > &to_insert = money[string(temp)];
		to_insert.first = a;
		for (int i = 0; i < no; ++i) {
			char tem[30];
			fscanf(fin, "%s\n", tem);
			to_insert.second.insert(tem);
		}
	}
	map<string, pair<int, set<string> > >::iterator itr;
	for (itr = money.begin(); itr != money.end(); ++itr) {
		if (itr->second.first == 0) continue;
		set<string>::iterator itr2;
		for (itr2 = itr->second.second.begin();
				itr2 != itr->second.second.end(); ++itr2) {
			final[string(*itr2)] += itr->second.first / itr->second.second.size();
		}
		final[string(itr->first)] += itr->second.first % itr->second.second.size();
	}
	for (int i = 0; i < n; ++i) {
		fprintf(fout, "%s %d\n", p[i], final[string(p[i])] - money[string(p[i])].first);
	}
  fclose(fout);
  fclose(fin);
  return 0;
}
