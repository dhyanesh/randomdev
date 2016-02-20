/*
ID:  dhyanes1
LANG: C++
PROG: psolve
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int after[305];
int before[305];
int m,p;

int memo[305][1005];

int go(int pos, int spend) {
  if (spend < 0) {
    return 1<<20;
  }
  if (pos == p) {
    return 1;
  }
  int &min = memo[pos][spend];
  if (min > 0) {
    return min;
  }
  min = 1<<20;
  int sum_b = 0;
  int sum_a = 0;
  if (spend < m) {
    min <?= go(pos, m) + 1;
  }
  for(int i = pos; i < p; ++i) {
    sum_b += before[i];
    sum_a += after[i];
    if (spend < sum_b || m < sum_a) {
      break;
    }
    min <?= go(i + 1, m - sum_a) + 1;
  }

  return min;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("psolve.in","r");
  fout = fopen("psolve.out","w");
  fscanf(fin, "%d %d", &m, &p);
  for (int co = 0; co < p; ++co) {
    fscanf(fin, "%d %d", &before[co], &after[co]);
  }
  memset(memo, 0xff, sizeof(memo));
  fprintf(fout, "%d\n", go(0, m) + 1);
  fclose(fout);
  fclose(fin);
  return 0;
}
