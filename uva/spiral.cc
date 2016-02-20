#include <cstdio>
#include <cstdlib>
#include <cmath>

typedef long long ll;

void get(ll no, ll co[]) {
	ll n = sqrt(double(no));

	if (!(n & 1)) ++n;

	if (n * n < no) {
		n += 2;
	}

	co[0] = co[1] = (n - 1) / 2;
	if (n * n == no) {
		return;
	}

	int d = n * n - no;

	int dx[] = { -1,0,1,0 };
	int dy[] = { 0,-1,0,1 };

	int pos = 0;
	for (int i = 0 ;i < 4; ++i) {
		if (d > n - 1) {
			co[0] += dx[i] * (n - 1);
			co[1] += dy[i] * (n - 1);
			d -= n - 1;
		} else { pos = i; break; }
	}

	co[0] += dx[pos] * d;
	co[1] += dy[pos] * d;
}

ll getn(ll x, ll y) {
	ll m = llabs(x) > llabs(y) ? llabs(x) : llabs(y);

	ll ret = (2 * m + 1) * (2 * m + 1);
	ll co[] = { m , m };

	int dx[] = { -1,0,1,0 };
	int dy[] = { 0,-1,0,1 };
	int chx = false;

	for (int i = 0 ;i < 4; ++i) {
		if (chx) {
			if (co[0] == x) {  break; }
		} else if (co[1] == y) {  break; }

		ret -= 2 * m;
		co[0] += dx[i] * 2 * m;
		co[1] += dy[i] * 2 * m;

		chx = !chx;
	}

	ret -= llabs(x - co[0]) + llabs(y - co[1]);

	return ret;
}

int main(void) {
	ll n;
	ll co[2];
	while (scanf("%lld", &n) == 1)	 {
		get(n, co);
		for (int j = 1; j >= -1; --j) {
			for (int i = -1; i <= 1; ++i) {
				printf("%lld;", getn(co[0] + i, co[1] + j));
			}
			printf("\n");
		}
	}
	return 0;
}
