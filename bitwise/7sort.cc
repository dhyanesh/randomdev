#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main(void) {
  int c;
  scanf("%d", &c);
  vector<pair<int,int> > arr;
  for (int cc = 0; cc < c; ++cc) {
    int n;
    scanf("%d", &n);
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i].first);
      arr[i].second = i + 1;
    }
    sort(arr.begin(), arr.end());
    printf("%d", arr[0].second);
    for (int i = 1; i < n; ++i) {
      printf(" %d", arr[i].second);
    }
    printf("\n");
  }
  return 0;
}
