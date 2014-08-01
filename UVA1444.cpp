#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 1000005;

int t, R, L, n, blo[N], zero[N], value[N], can[N], g[N];

void build() {
    scanf("%d", &n);
    int zn = 0, now = 0;
    memset(value, -1, sizeof(value));
    for (int i = 0; i < n; i++) {
	scanf("%d", &blo[i]);
	if (blo[i] == 0) {
	    zero[zn++] = i;
	    can[now]++;
	    now++;
	}
	else {
	    now += blo[i];
	    int k = min(zn, blo[i]);
	    for (int j = 1; j <= k; j++) {
		value[now - j] = i - zero[zn - j] - j + 1;
		can[now - j]++;
		g[now - j] += value[now - j];
	    }
	}
    }
    reverse(blo, blo + n);
    zn = 0; now--;
    for (int i = 0; i < n; i++) {
	if (blo[i] == 0) {
	    zero[zn++] = i;
	    now--;
	}
	else {
	    now -= blo[i];
	    int k = min(zn, blo[i]);
	    for (int j = 1; j <= k; j++) {
		if (value[now + j] == -1) {
		    value[now + j] = i - zero[zn - j] - j + 1;
		    g[now + j] += value[now + j];
		    can[now + j]++;
		}
		else {
		    int tmp = i - zero[zn - j] - j + 1;
		    g[now + j] += min(0, tmp - value[now + j]);
		}
	    }
	}
    }
}

void solve() {
    int an = 0, Min = INF;
    for (int i = 0; i < L; i++) {
	if (can[i] != R) continue;
	if (Min > g[i]) {
	    Min = g[i];
	    an = 0;
	    value[an++] = i;
	}
	else if (Min == g[i]) {
	    value[an++] = i;
	}
    }
    printf("%d\n", Min);
    for (int i = 0; i < an; i++)
	printf("%d ", value[i]);
    printf("\n");
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &R, &L);
	memset(can, 0, sizeof(can));
	memset(g, 0, sizeof(g));
	for (int i = 0; i < R; i++)
	    build();
	solve();
    }
    return 0;
}
