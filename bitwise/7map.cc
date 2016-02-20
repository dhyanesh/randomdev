#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;


int main(void) {
  int c;
  scanf("%d", &c);
  for (int cc = 0; cc < c; ++cc) {
    int n;
    scanf("%d", &n);
    vector<vector<int> > out(n + 1);
    for (int i = 0; i < n; ++i) {
      int no;
      scanf("%d", &no);
      out[no].push_back(i + 1);
    }
    int i;
    vector<int>::iterator itr;
    bool f = false;
    for (i = 0; i < n; ++i) {
      for (itr = out[i].begin(); itr != out[i].end(); ++itr) {
        if (!f) {
          printf("%d", *itr);
        } else {
          printf(" %d", *itr);
        }
        f = true;
      }
    }
    printf("\n");
  }
  return 0;
}
