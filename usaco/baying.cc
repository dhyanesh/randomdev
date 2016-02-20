/*
ID:  dhyanes1
LANG: C++
PROG: baying
*/
#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>

typedef unsigned long long ull;

using namespace std;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("baying.in","r");
  fout = fopen("baying.out","w");

  ull c,n;
  fscanf(fin, "%llu %llu", &c,&n);
  ull a1,b1,d1;
  fscanf(fin, "%llu %llu %llu", &a1, &b1, &d1);
  ull a2,b2,d2;
  fscanf(fin, "%llu %llu %llu", &a2, &b2, &d2);

  priority_queue<ull, vector<ull>, greater<ull> > q;
  q.push(c);
  ull count = 1;
  ull prev = 0;
  while (true) {
    ull top = q.top();
    q.pop();
    if (top == prev) continue;
    prev = top;
    if (count == n) {
      fprintf(fout, "%llu\n", top);
      break;
    }
    ull nc = a1 * top / d1 + b1;
    q.push(nc);
    nc = a2 * top / d2 + b2;
    q.push(nc);
    ++count;
  }

  fclose(fout);
  fclose(fin);
  return 0;
}
