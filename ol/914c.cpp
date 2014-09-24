#include <cstdio>
#include <cstring>

const int N = 100005;

int n, a[N], ans[N];
int cnt[N];

int count(int x) {
	if (x == 0) return 1;
	int ans = 0;
	while (x) {
		ans++;
		x >>= 1;
	}
	return ans;
}

void dfs(int n) {
	if (n <= 0) return;
	int tmp = (n^cnt[n]);
	for (int i = n; i >= tmp; i--) {
		ans[i] = n + tmp - i;
	}
	dfs(tmp - 1);
}

int main() {
	for (int i = 0; i < N; i++)
		cnt[i] = ((1<<count(i)) - 1);
	while (~scanf("%d", &n)) {
		for (int i = 0; i <= n; i++)
			scanf("%d", &a[i]);
		memset(ans, 0, sizeof(ans));
		dfs(n);
		long long out = 0;
		for (int i = 0; i <= n; i++)
			out += (long long)(a[i]^ans[a[i]]);
		printf("%I64d\n", out);
		for (int i = 0; i <= n; i++)
			printf("%d%c", ans[a[i]], i == n ? '\n' : ' ');
	}
	return 0;
}
