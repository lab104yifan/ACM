#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 66666;

int n, p, num[N], mi[20], have[20][N];

int main() {
    mi[0] = 1;
    for (int i = 1; i <= 16; i++)
	mi[i] = mi[i - 1] * 2;
    int cas = 0;
    while (~scanf("%d", &n) && n != -1) {
	memset(num, 0, sizeof(num));
	memset(have, 0, sizeof(have));
	while (n--) {
	    scanf("%d", &p);
	    num[p]++;
	}
	for (int i = 0; i < 16; i++) {
	    for (int j = 0; j < mi[i]; j++) {
		int up = (mi[16] - j) / mi[i] * mi[i] + j;
		if (up == mi[16]) up -= mi[i];
		for (int k = up; k >= j; k -= mi[i])
		    have[i][k] = have[i][k + mi[i]] + num[k];
	    }
	}
	int sum = 0, d;
	ll ans = 0;
	char c[10];
	while (~scanf("%s", c)) {
	    if (c[0] == 'E') break;
	    scanf("%d", &d);
	    if (c[0] == 'Q') {
		if (d >= 16) continue;
		int x = sum % mi[d];
		x = mi[d] - x;
		printf("%d %d %d\n", d, x, have[d][x]);
		ans += have[d][x];
	    }
	    if (c[0] == 'C') {
		sum = (sum + d) % mi[16];
	    }
	}
	printf("Case %d: %lld\n", ++cas, ans);
    }
    return 0;
}
