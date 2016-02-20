/*
ID:  dhyanes1
LANG: C++
PROG: bones
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int arr[101];

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("bones.in","r");
  fout = fopen("bones.out","w");
  int s[3];
  fscanf(fin, "%d %d %d", &s[0], &s[1], &s[2]);
/*  memset(arr1, 0, sizeof(arr1));
  memset(arr2, 0, sizeof(arr1));
  arr1[0] = 1;
  arr2[0] = 1;

  int *curr = arr1;
  int *prev = arr2;
  for(int i = 0; i < 3; ++i) {
    memset(curr, 0, sizeof(arr1));
    for(int j = 1; j <= s[i]; ++j) {
      for(int k = 100; k >= j; k--) {
        curr[k] += prev[k] + prev[k-j];
      }
    }
    swap(curr, prev);
  }
  for(int i = 0; i <= 50; ++i) {
    printf("%d ", prev[i]);
  }
  */

  memset(arr, 0, sizeof(arr));
  for(int i = 1; i <= s[0]; ++i) {
    for(int j = 1; j <= s[1]; ++j) {
      for(int k = 1; k <= s[2]; ++k) {
        arr[i+j+k]++;
      }
    }
  }

  int max = 0;
  int p = 0;
  for(int i = 0; i < 101; ++i) {
    if (arr[i] > max) {
      max = arr[i];
      p = i;
    }
  }
  fprintf(fout, "%d\n", p);
  fclose(fout);
  fclose(fin);
  return 0;
}
