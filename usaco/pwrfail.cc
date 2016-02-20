/*
ID:  dhyanes1
LANG: C++
PROG: pwrfail
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <queue>

#define SQR(x) (x) * (x)
using namespace std;

int points[1001][2];
int done[1001][1001];
int odone[1001][1001];
int wdone[1001];
int ddone[1001];
int n;

double dis(int i, int j) {
  double ret = SQR(points[j][0] - points[i][0]);
  ret += SQR(points[j][1] - points[i][1]);
  return sqrt(ret);
}

double dfs(int p) {
  if (p == n - 1) return 0.0;
  if (ddone[p]) return -1.0;

  ddone[p] = 1;
  for(int i = 0; i < n; ++i) {
    if (done[p][i]) {
      double d = dfs(i);
      if (d > 0.0) {
        if (odone[p][i]) return d;

        d += dis(p,i);
        return d;
      }
    }
  }

  return -1.0;
}

struct Q {
  Q(double d,int s,int e) : dist(d), st(s), end(e) { }
  double dist;
  int st;
  int end;

  bool operator<(const Q &a) const {
    return dist > a.dist;
  }
};

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("pwrfail.in","r");
  fout = fopen("pwrfail.out","w");
  int w;
  fscanf(fin, "%d %d", &n, &w);
  double m;
  fscanf(fin, "%lf", &m);

  for(int i = 0; i < n; ++i) {
    fscanf(fin, "%d %d", &points[i][0], &points[i][1]);
  }

  memset(done, 0, sizeof(done));
  memset(odone, 0, sizeof(odone));
  memset(wdone, 0, sizeof(wdone));

  int t;
  for(int i = 0; i < w; ++i) {
    int x,y;
    fscanf(fin, "%d %d", &x, &y);
    odone[x - 1][y - 1]=1;
    odone[y - 1][x - 1]=1;
    done[x - 1][y - 1]=1;
    done[y - 1][x - 1]=1;
    wdone[x - 1] = 1;
    wdone[y - 1] = 1;
    t = x - 1;
  }

  priority_queue<Q, vector<Q> > q;

  for(int i = 0; i < n; ++i) {
    if (!wdone[i]) continue;
    for(int j = 0; j < n; ++j) {
      if (i == j || done[i][j] || wdone[j]) continue;

      double d = dis(i,j);
      if (d <= m)
        q.push(Q(d, i, j));
    }
  }

  while (!q.empty()) {
    const Q &top = q.top();

    if (!wdone[top.end]) {
      wdone[top.end] = 1;
      done[top.st][top.end] = 1;
      done[top.end][top.st] = 1;

      for(int i = 0; i < n; ++i) {
        if (i == top.end || wdone[i]) continue;

        double d = dis(i,top.end);
        if (d <= m)
          q.push(Q(d, top.end, i));
      }
    }
    if (top.end == n - 1) break;
    q.pop();
  }

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      printf("%d ", done[i][j]);
    }
    printf("\n");
  }

  memset(ddone, 0, sizeof(ddone));
  if (!wdone[n-1]) {
    fprintf(fout, "-1\n");
  } else {
    fprintf(fout, "%d\n", int(dfs(t) * 1000.0));
  }


  fclose(fout);
  fclose(fin);
  return 0;
}
