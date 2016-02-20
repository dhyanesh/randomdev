/*
ID:  dhyanes1
LANG: C++
PROG: csort
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

int arr[10005];
int sarr[10005];
map<int, int> rev;
map<int, int> should;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("csort.in","r");
  fout = fopen("csort.out","w");
	int n;
	fscanf(fin, "%d", &n);
	for(int i = 0; i < n; ++i) {
		fscanf(fin, "%d", &arr[i]);
		rev[arr[i]] = i;
		sarr[i] = arr[i];
	}
	sort(sarr, sarr + n);
	for(int i = 0; i < n; ++i) {
		should[sarr[i]] = i;
	}
	int cost = 0;
	for(int i = 0; i < n; ++i) {
		if (arr[i] == sarr[i]) {
			continue;
		}
		int val = sarr[rev[arr[i]]];
		list<int> cycle;
		cycle.push_back(val);

		while (val != arr[i]) {
			val = sarr[rev[val]];
			cycle.push_back(val);
		}

		while (cycle.size() > 1) {
			list<int>::iterator itr =
				max_element(cycle.begin(), cycle.end());
			int a = rev[*itr];
			int b = should[*itr];
			cost += arr[a] + arr[b];
			rev[arr[a]] = b;
			rev[arr[b]] = a;
			swap(arr[a], arr[b]);
			cycle.erase(itr);
		}
	}
	fprintf(fout, "%d\n", cost);
  fclose(fout);
  fclose(fin);
  return 0;
}
