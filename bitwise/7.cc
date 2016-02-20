#include <cstdio>
#include <cstring>

int arr[1000005];
int out[1000005];
int free[1005];

int main(void) {
  int c;
  scanf("%d", &c);
  for (int cc = 0; cc < c; ++cc) {
    memset(out, 0, sizeof(out));
    memset(free, 0, sizeof(free));
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);

      bool placed = false;
      int c = arr[i];
      for (int j = arr[i]; j < n; ++j) {
        if (out[j] == 0) {
          out[j] = i + 1;
          placed = true;
          free[j / 1000]++;
          break;
        }
        if (j % 1000 == 0) { c = j; break; }
      }
      if (placed) continue;

      int st = c / 1000;

      for(int j = st; j < 1005; ++j) {
        if (free[j] < 1000) {
          for (int k = j * 1000; ; ++k) {
            if (out[k] == 0) {
              out[k] = i + 1;
              placed = true;
              break;
            }
          }
          free[j]++;
          break;
        }
      }
    }
    printf("%d", out[0]);
    for (int i = 1; i < n; ++i) {
      printf(" %d", out[i]);
    }
    printf("\n");
  }
  return 0;
}
