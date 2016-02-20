#include <cstdio>
#include <algorithm>

using namespace std;

int arr[805][805];
int out[805];
int final[805];

int main(void) {
  int cases;
  scanf("%d", &cases);
  for (int c = 0; c < cases; ++c) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%d", &arr[i][j]);
      }
      out[i] = 1;
    }

    for (int j = 0; j < n; ++j) {
      int c = -1;
      for (int i = j; i < n; ++i) {
        if (arr[i][j] == 1) {
          c = i;
          break;
        }
      }

      if (c != -1) {
        for (int i = 0; i < n; ++i) {
          swap(arr[j][i], arr[c][i]);
        }
        swap(out[j], out[c]);
      }

      for (int i = j + 1; i < n; ++i) {
        if (arr[i][j] == 0) continue;
        for (int k = 0; k < n; ++k) {
          arr[i][k] ^= arr[j][k];
        }
        out[i] ^= out[j];
      }
    }

//    for (int i = 0; i < n; ++i) {
//      for (int j = 0; j < n; ++j) {
//        printf(" %d", arr[i][j]);
//      }
//      printf("\n");
//    }

    for (int i = n-1; i >= 0; --i) {
      final[i] = out[i];
      for (int k = i + 1; k < n; ++k) {
        final[i] ^= arr[i][k] * final[k];
      }
    }

//    printf("%d", out[0]);
//    for (int i = 1; i < n; ++i) {
//      printf(" %d", out[i]);
//    }
//    printf("\n");

    printf("%d", final[0]);
    for (int i = 1; i < n; ++i) {
      printf(" %d", final[i]);
    }
    printf("\n");
  }
  return 0;
}
