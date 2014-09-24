#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200005;

int t, n, m, l;
int r[N];

int solve() {
	int ans = 0;
	int now = 0;
	int pre = -l;
	int st = 0;
	while (now < m) {
		if (now + l < r[st]) {
			int tmp = now - pre;
			int len = r[st] - now;
			int ci = len / (l + 1) - 1;
			ans += ci * 2;
			now += ci * (l + 1);
			pre = now - tmp;
			ans++;
			pre = now;
			now += (1 + l) - tmp;
		} else {
			while (now + l >= r[st] && st <= n)
				st++;
			pre = now;
			now = r[st - 1];
			ans++;
		}
	}
	return ans;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &l);
		for (int i = 0; i < n; i++)
			scanf("%d", &r[i]);
		sort(r, r + n);
		r[n] = m;
		printf("Case #%d: %d\n", ++cas, solve());
	}
	return 0;
}
