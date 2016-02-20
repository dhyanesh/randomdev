/*
ID:  dhyanes1
LANG: C++
PROG: cleanup
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;

vector<int> cows;
map<pair<int, int>, int > memo;

int go(int st, int curr) {
  pair<int,int> t(st,curr);
  map<pair<int,int>, int>::const_iterator itr = memo.find(t);
  if (itr != memo.end()) {
    return itr->second;
  }
  int &ret = memo[t];

  set<int> no;
  for(int i = st; i < curr; ++i) {
    no.insert(cows[i]);
  }
  int ti = no.size() * no.size();

  if (curr == cows.size()) {
    ret = ti;
    return ret;
  }

  ret = go(curr, curr + 1) + ti;
  ret = min(ret, go(st, curr + 1));

  return ret;
}

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("cleanup.in","r");
  fout = fopen("cleanup.out","w");

  int n,m;
  fscanf(fin, "%d %d", &n, &m);
  cows.resize(n);
  memo.clear();
  for (int i = 0; i < n; ++i) {
    fscanf(fin, "%d", &cows[i]);
  }

  fprintf(fout, "%d\n", go(0, 1));

  fclose(fout);
  fclose(fin);
  return 0;
}
