#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

const int MAXLEN = 1005;

struct Suffix {

    int s[MAXLEN];
    int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
    int rank[MAXLEN], height[MAXLEN];

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

    void init(string str) {
	n = 0;
	for (int i = 0; i < str.length(); i++) if (str[i] != ' ')
	    s[n++] = str[i] - 'A' + 1;
	s[n] = '\0';
    }

    void solve() {
	build_sa(27);
	getHeight();
	int len = 1;
	while (1) {
	    int ans = 1;
	    for (int i = 1; i <= n; i++) {
		if (n - sa[i] < len) continue;
		int cnt = 1;
		while (i < n && height[i + 1] >= len) {
		    i++;
		    cnt++;
		}
		ans = max(ans, cnt);
	    }
	    if (ans == 1) break;
	    printf("%d\n", ans);
	    len++;
	}
	printf("\n");
    }
} gao;

string str;

int main() {
    while (getline(cin, str) && str != "") {
	gao.init(str);
	gao.solve();
    }
    return 0;
}
