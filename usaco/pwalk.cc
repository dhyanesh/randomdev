/*
ID:  dhyanes1
LANG: C++
PROG: pwalk
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

using namespace std;

vector<pair<int, int> > gr[1001];
int len[1001][1001];

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("pwalk.in","r");
  fout = fopen("pwalk.out","w");
  int n,q;
  fscanf(fin, "%d %d", &n, &q);
  memset(len, 0xff, sizeof(len));
  for(int i = 0; i < n - 1; ++i) {
    int a,b,l;
    fscanf(fin, "%d %d %d", &a, &b, &l);
    gr[a].push_back(make_pair(b,l));
    gr[b].push_back(make_pair(a,l));
  }

  for(int i = 0; i < q; ++i) {
    int x,y;
    fscanf(fin, "%d %d", &x, &y);

    if (len[x][y] >= 0) {
      fprintf(fout, "%d\n", len[x][y]);
      continue;
    }

    queue<pair<int, int> > bfs;
    bfs.push(make_pair(x, 0));
    while (!bfs.empty()) {
      pair<int, int> top = bfs.front();
      bfs.pop();
      len[x][top.first] = top.second;
      len[top.first][x] = top.second;
      if (top.first == y) {
        break;
      }

      for(int i = 0; i < gr[top.first].size(); ++i) {
        bfs.push(make_pair(gr[top.first][i].first,
                           top.second + gr[top.first][i].second));
      }
    }

    fprintf(fout, "%d\n", len[x][y]);
  }

  fclose(fout);
  fclose(fin);
  return 0;
}
