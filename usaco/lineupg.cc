/*
ID:  dhyanes1
LANG: C++
PROG: lineupg
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int mini[1000];
int maxi[1000];
int arr[50005];

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("lineupg.in","r");
  fout = fopen("lineupg.out","w");
  int  n,q;
  fscanf(fin, "%d %d", &n, &q);
  int min = 1<<30;
  int max = 0;
  int lim = sqrt(1.0*n);
  int co;
  for(co = 0; co < n; co++) {
    fscanf(fin, "%d", &arr[co]);
    if (co%lim == 0) {
      mini[co/lim] = min;
      min = 1<<30;
      maxi[co/lim] = max;
      max = 0;
    }
    min <?= arr[co];
    max >?= arr[co];
  }
  if (co%lim == 0) {
    mini[co/lim] = min;
    min = 1<<30;
    maxi[co/lim] = max;
    max = 0;
  }
  for(int co = 0; co < q; co++) {
    int a,b;
    fscanf(fin, "%d %d", &a, &b);
    a--;b--;
    int min = arr[a];
    int max = arr[a];
    for (int i = a; i <= b; ) {
      if (i%lim == 0 && i+lim-1<=b) {
	i+=lim;
	min <?= mini[i/lim];
	max >?= maxi[i/lim];
      } else {
	min <?= arr[i];
	max >?= arr[i];
	++i;
      }
    } 
    fprintf(fout, "%d\n", max - min);
  }
  fclose(fout);
  fclose(fin);
  return 0;
}
