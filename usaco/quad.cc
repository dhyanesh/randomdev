/*
ID:  dhyanes1
LANG: C++
PROG: quad
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int ways[2505][4];
int n;

int go(int sum, int cuts) {
  int ret = 0;
  int lim = n / 2 + n % 2;
  for(int i = 1; i < lim; ++i) {
    for(int j = 1; j < lim; ++j) {
      int t = n - i - j;

      int kmi = t - lim + 1;
      if (kmi < 1) kmi = 1;
      if (kmi >= lim) continue;

      int kma = t - 1;
      if (kma < 1) continue;
      if (kma >= lim) kma = lim - 1;

      ret += kma - kmi + 1;
    }
  }

  return ret;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("quad.in","r");
  fout = fopen("quad.out","w");
  memset(ways, 0xff, sizeof(ways));
  fscanf(fin, "%d", &n);
  fprintf(fout, "%d\n", go(0, 0));
  fclose(fout);
  fclose(fin);
  return 0;
}
