/*
ID:  dhyanes1
LANG: C++
PROG: money
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int arr[50];
long long dp[10005];

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("money.in","r");
  fout = fopen("money.out","w");
	int n,v;
	fscanf(fin, "%d %d", &v, &n);
	for (int i = 0; i < v; ++i) {
		fscanf(fin, "%d", &arr[i]);
	}
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;	
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j <= n - arr[i]; ++j) {
			dp[j + arr[i]] += dp[j];
		}
	}
	fprintf(fout, "%lld\n", dp[n]);
  fclose(fout);
  fclose(fin);
  return 0;
}
