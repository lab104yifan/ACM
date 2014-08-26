#include <cstdio>
#include <cstring>
using namespace std;

const int MAXNODE = 3000005;
const int SIGMA_SIZE = 26;

int n, m, ti;
char str[15];

struct Trie {

    int ch[MAXNODE][SIGMA_SIZE];
    int val[MAXNODE];
    int vis[MAXNODE];
    int sz;

    void init() {
	sz = 1; 
	memset(ch[0], 0, sizeof(ch[0]));
    }

    int idx(char c) {return c - 'a';}

    void insert(char *str, int v) {
	int n = strlen(str);
	int u = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(str[i]);
	    if (!ch[u][c]) {
		memset(ch[sz], 0, sizeof(ch[sz]));
		val[sz] = 0;
		ch[u][c] = sz++;
	    }
	    u = ch[u][c];
	    val[u] += v;
	}
    }

    void dfs(int u, int len, int use) {
	if (len == n) {
	    vis[u] = 2;
	    return;
	}
	if (vis[u] == 0)
	    vis[u] = 1;
	if (use < ti)
	    dfs(u, len + 1, use + 1);
	for (int i = 0; i < SIGMA_SIZE; i++) {
	    if (!ch[u][i]) continue;
	    if (idx(str[len]) == i) dfs(ch[u][i], len + 1, use);
	    else if (use < ti) dfs(ch[u][i], len + 1, use + 1);
	    if (use < ti) dfs(ch[u][i], len, use + 1);
	}
    }

    int cal(int u) {
	if (vis[u] == 2)
	    return val[u];
	int ans = 0;
	for (int i = 0; i < SIGMA_SIZE; i++) {
	    if (!ch[u][i]) continue;
	    if (vis[ch[u][i]])
		ans += cal(ch[u][i]);
	}
	return ans;
    }

    void clr(int u) {
	for (int i = 0; i < SIGMA_SIZE; i++) {
	    if (!ch[u][i]) continue;
	    if (vis[ch[u][i]]) clr(ch[u][i]);
	}
	vis[u] = 0;
    }

    void solve() {
	init();
	for (int i = 0; i < n; i++) {
	    scanf("%s", str);
	    insert(str, 1);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
	    scanf("%s%d", str, &ti);
	    n = strlen(str);
	    dfs(0, 0, 0);
	    printf("%d\n", cal(0));
	    clr(0);
	}
    }

} gao;

int main() {
    while (~scanf("%d", &n)) {
	gao.solve();
    }
    return 0;
}
