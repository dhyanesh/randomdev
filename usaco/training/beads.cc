/*
ID:  dhyanes1
LANG: C++
PROG: beads
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("beads.in","r");
  fout = fopen("beads.out","w");
	int n;
	fscanf(fin, "%d\n", &n);
	char beads[400];
	fscanf(fin, "%s\n", beads);
	int max = 0;
	for (int i = 0; i < n; ++i) {
		char ch = beads[i];
		int co = 1;
		if (ch != 'w') {
			for (int j = (i + 1) %n; j != i; j = (j+1)%n) {
				if (beads[j] == ch || beads[j] == 'w') co++; else break;
			}
		} else {
			ch = 'r';
			int to = 1;
			for (int j = (i + 1 )%n; j != i; j = (j+1)%n) {
				if (beads[j] == ch || beads[j] == 'w') to++; else break;
			}
			co  = to;
			ch = 'b';
			to = 1;
			for (int j = (i + 1)%n; j != i; j = (j+1)%n) {
				if (beads[j] == ch || beads[j] == 'w') to++; else break;
			}
			co >?= to;
		}
		int j = (i - 1 + n) % n;
		ch = beads[j];
		if (ch != 'w') {
			for (; j != i; j = (j - 1 + n) %n) {
				if (beads[j] == ch || beads[j] == 'w') co++; else break;
			}
		} else {
			ch = 'r';
			int to1 = 0;
			for (; j != i; j = (j - 1 + n) %n) {
				if (beads[j] == ch || beads[j] == 'w') to1++; else break;
			}
			ch = 'b';
			int to2 = 0;
			j = (i - 1 + n) % n;
			for (; j != i; j = (j - 1 + n) %n) {
				if (beads[j] == ch || beads[j] == 'w') to2++; else break;
			}
			co += to1>to2?to1:to2;

		}
		max >?= co;
	}
	fprintf(fout, "%d\n", max<n?max:n);
  fclose(fout);
  fclose(fin);
  return 0;
}
