#include <cstdio>
#include <cstdlib>

using namespace std;

int arr[10005][2];
int p[10005];

int main(void) {
  int ca;
  scanf("%d", &ca);
  for (int c = 0; c < ca; ++ca) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i][0], &arr[i][1]);
    }

    if (n == 2) {
      printf("%d %d %d %d\n", arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
      continue;
    }

    long double m = () / :wq
      ;

    for (int i = 0; i < n; ++i) {
      p[i] = i;
    }

    for (int i = 0; i < n; ++i) {
      swap(p[i], p[i + random() % (n - i - 1)]);
    }

    for (int i = 0; i < n; ++i) {

    }

  }
  return 0;
}
