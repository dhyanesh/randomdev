/*
ID:  dhyanes1
LANG: C++
PROG: ride
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int main(void)
{
  FILE *fin,*fout;
  fin=fopen("ride.in","r");
  fout = fopen("ride.out","w");
	char buf1[20], buf2[20];
	fscanf(fin, "%s\n", buf1);
	fscanf(fin, "%s\n", buf2);
	long long a = 1;
	char *ptr = buf1;
	while (*ptr != '\0') {
		a = (a * (*ptr - 'A' + 1)) % 47;
		ptr++;
	}
	long long b = 1;
	ptr = buf2;
	while (*ptr != '\0') {
		b = (b * (*ptr - 'A' + 1)) % 47;
		ptr++;
	}
	if (a == b) {
		fprintf(fout, "GO\n");
	} else {
		fprintf(fout, "STAY\n");
	}
  fclose(fout);
  fclose(fin);
  return 0;
}
