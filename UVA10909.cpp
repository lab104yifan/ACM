#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2000001;

int bit[N], tmp[N], lucky[N], vis[N], tot;

int lowbit(int x) {
    return (x&(-x));
}

void add(int x, int v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int n;

int find(int x) {
    int ans = 0, num = 0;
    for (int i = 20; i >= 0; i--) {
	ans += (1<<i);
	if (ans >= N || num + bit[ans] >= x)
	    ans -= (1<<i);
	else num += bit[ans];
    }
    return ans + 1;
}

void solve(int n) {
    if (n % 2 == 0) {
	int i = upper_bound(lucky + 1, lucky + tot + 1,  n / 2) - lucky - 1;
	for (; i >= 1; i--) {
	    if (vis[n - lucky[i]]) {
		printf("%d is the sum of %d and %d.\n", n, lucky[i], n - lucky[i]);
		return;
	    }
	}
    }
    printf("%d is not the sum of two luckies!\n", n);
}

int main() {
    tot = 2000000;
    for (int i = 1; i <= tot; i += 2)
	add(i, 1);
    tot /= 2;
    for (int i = 2; ; i++) {
	int len = find(i);
	if (tot < len) break;
	for (int j = len; j <= tot; j += len)
	    tmp[j] = find(j);
	for (int j = len; j <= tot; j += len)
	    add(tmp[j], -1);
	tot = tot - tot / len;
    }
    for (int i = 1; i <= tot; i++) {
	lucky[i] = find(i);
	vis[lucky[i]] = 1;
    }
    while (~scanf("%d", &n)) {
	solve(n);
    }
    return 0;
}
