/*
ID:  dhyanes1
LANG: C++
PROG: rotation
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int gr[1003][2];

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("rotation.in","r");
  fout = fopen("rotation.out","w");
  int n;
  fscanf(fin, "%d", &n);
  for(int i = 0; i < n - 1; ++i) {
    int x,y,dir;
    fscanf(fin, "%d %d %d", &x, &y, &dir);
    gr[x][0] = y;
    gr[x][1] = 1 - dir;
  }
  int d = 1;
  int p = 1;

  while (p != n) {
    d ^= gr[p][1];
    p = gr[p][0];
  }

  fprintf(fout, "%d\n", d);

  fclose(fout);
  fclose(fin);
  return 0;
}
