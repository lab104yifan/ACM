#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXLEN = 222222;

struct Suffix {

    int s[MAXLEN];
    int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
    int rank[MAXLEN], height[MAXLEN];
    int best[MAXLEN][20];

    int g, len;
    char str[MAXLEN];

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

    void initRMQ() {
	for (int i = 0; i < n; i++) best[i][0] = height[i + 1];
	for (int j = 1; (1<<j) <= n; j++)
	    for (int i = 0; i + (1<<j) - 1 < n; i++)
		best[i][j] = min(best[i][j - 1], best[i + (1<<(j - 1))][j - 1]);
    }

    int lcp(int L, int R) {
	L = rank[L] - 1; R = rank[R] - 1;
	if (L > R) swap(L, R);
	L++;
	int k = 0;
	while ((1<<(k + 1)) <= R - L + 1) k++;
	return min(best[L][k], best[R - (1<<k) + 1][k]);
    }

    void init() {
	n = 0;
	len = strlen(str);
	for (int i = 0; i < len; i++)
	    s[n++] = str[i] - 'a' + 1;
	s[n++] = 27;
	for (int i = len - 1; i >= 0; i--)
	    s[n++] = str[i] - 'a' + 1;
	s[n] = 0;
    }

    int solve() {
	init();
	build_sa(28);
	getHeight();
	initRMQ();
	int ans = 1;
	for (int i = 1; i < len - 1; i++) {
	    int l = n - i, r = i;
	    ans = max(ans, lcp(l, r) * 2);
	    r++;
	    ans = max(ans, lcp(l, r) * 2 + 1);
	}
	return ans;
    }

} gao;

int main() {
    while(~scanf("%s", gao.str)) {
	printf("%d\n", gao.solve());
    }
    return 0;
}
