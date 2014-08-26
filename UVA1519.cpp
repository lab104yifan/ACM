#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXNODE = 400005;
const int SIGMA_SIZE = 26;

struct Trie {
    int ch[MAXNODE][SIGMA_SIZE];
    int cnt[SIGMA_SIZE];
    int sz;

    void init() {
	sz = 1;
	memset(ch[0], 0, sizeof(ch[0]));
	memset(cnt, 0, sizeof(cnt));
    }

    int idx(char c) {
	return c - 'a';
    }

    void insert(char *s) {
	int n = strlen(s);
	int u = 0, v;
	for (int i = 0; i < n; i++) {
	    int c = idx(s[i]);
	    if (!ch[u][c]) {
		memset(ch[sz], 0, sizeof(ch[sz]));
		ch[u][c] = sz++;
		if (i) cnt[c]++;
	    }
	    u = ch[u][c];
	}
    }
}pre, suf;

typedef long long ll;
int n, vis[26];
char str[45];

int main() {
    while (~scanf("%d", &n)) {
	pre.init(); suf.init();
	memset(vis, 0, sizeof(vis));
	while (n--) {
	    scanf("%s", str);
	    if (strlen(str) == 1)
		vis[str[0] - 'a'] = 1;
	    pre.insert(str);
	    reverse(str, str + strlen(str));
	    suf.insert(str);
	}
	ll ans = (ll)(pre.sz - 1) * (suf.sz - 1);
	for (int i = 0; i < 26; i++)
	    ans -= (ll)pre.cnt[i] * suf.cnt[i] - vis[i];
	printf("%lld\n", ans);
    }
    return 0;
}
