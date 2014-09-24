#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXLEN = 100005;

struct Suffix {

	char str[MAXLEN];
	int s[MAXLEN];
	int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
	int rank[MAXLEN], height[MAXLEN];
	ll sum[MAXLEN];

	void build_sa(int m) {
		n++;
		int i, *x = t, *y = t2;
		for (i = 0; i < m; i++) c[i] = 0;
		for (i = 0; i < n; i++) c[x[i] = s[i]]++;
		for (i = 1; i < m; i++) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
		for (int k = 1; k <= n; k <<= 1) {
			int p = 0;
			for (i = n - k; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
			for (i = 0; i < m; i++) c[i] = 0;
			for (i = 0; i < n; i++) c[x[y[i]]]++;
			for (i = 0; i < m; i++) c[i] += c[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for (i = 1; i < n; i++)
				x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
			if (p >= n) break;
			m = p;
		}
		n--;
	}

	void getHeight() {
		int i, j, k = 0;
		for (i = 1; i <= n; i++) rank[sa[i]] = i;
		for (i = 0; i < n; i++) {
			if (k) k--;
			int j = sa[rank[i] - 1];
			while (s[i + k] == s[j + k]) k++;
			height[rank[i]] = k;
		}
	}

	void getsum() {
		for (int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + n - sa[i] - height[i];
	}

	void init() {
		n = strlen(str);
		for (int i = 0; i < n; i++)
			s[i] = str[i] - 'a' + 1;
		s[n] = 0;
		build_sa(27);
		getHeight();
		getsum();
	}

	void query(ll &ls, ll &rs, ll k) {
		int u = lower_bound(sum + 1, sum + n + 1, k) - sum;
		if (u == n + 1) {
			ls = 0; rs = 0;
			printf("%I64d %I64d\n", ls, rs);
			return;
		}
		int len = k - sum[u - 1] + height[u];
		int st = sa[u];
		for (int i = u; i > 1; i--) {
			if (height[i] < len) break;
			st = min(st, sa[i - 1]);
		}
		for (int i = u + 1; i <= n; i++) {
			if (height[i] < len) break;
			st = min(st, sa[i]);
		}
		ls = st + 1; rs = st + len;
		printf("%I64d %I64d\n", ls, rs);
	}

	void solve() {
		init();
		ll l = 0, r = 0, v;
		int q;
		scanf("%d", &q);
		while (q--) {
			scanf("%I64d", &v);
			ll k = (l^r^v) + 1;
			query(l, r, k);
		}
	}
} gao;


int main() {
	while (~scanf("%s", gao.str)) {
		gao.solve();
	}
	return 0;
}
