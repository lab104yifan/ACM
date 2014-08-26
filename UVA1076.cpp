#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

typedef long long ll;
const int MAXNODE = 105;
const int SIGMA_SIZE = 26;
const int N = 30;
const int M = (1<<10) + 5;

int n, m;

struct AutoMac {
    
    int ch[MAXNODE][SIGMA_SIZE];
    int val[MAXNODE];
    int next[MAXNODE];
    int last[MAXNODE];
    ll dp[MAXNODE][N][M];
    int out[N];

    int sz;
    
    void init() {
	sz = 1; 
	memset(ch[0], 0, sizeof(ch[0]));
    }

    int idx(char c) {
	return c - 'a';
    }

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
	}
	val[u] |= (1<<v);
    }

    void getnext() {
	queue<int> Q;
	next[0] = 0;	
	for (int c = 0; c < SIGMA_SIZE; c++) {
	    int u = ch[0][c];
	    if (u) {next[u] = 0; Q.push(u); last[u] = 0;}
	}

	while (!Q.empty()) {
	    int r = Q.front(); Q.pop();
	    for (int c = 0; c < SIGMA_SIZE; c++) {
		int u = ch[r][c];
		if (!u) {
		    ch[r][c] = ch[next[r]][c];
		    continue;
		}
		Q.push(u);
		int v = next[r];
		while (v && !ch[v][c]) v = next[v];
		next[u] = ch[v][c];
		val[u] |= val[next[u]];
		//last[u] = val[next[u]] ? next[u] : last[next[u]];
	    }
	}
    }

    /*
    void print(int i, int j) {
	if (j) {
	    //printf("%d: %d\n", i, val[j]);
	    print(i, last[j]);
	}
    }

    void find(char *T) {
	int n = strlen(T);
	int j = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(T[i]);
	    j = ch[j][c];
	    if (val[j]) print(i, j);
	    else if (last[j]) print(i, last[j]);
	}
    }*/
    
    ll dfs(int now, int len, int st) {
	ll &ans = dp[now][len][st];
	if (ans != -1) return ans;
	ans = 0;
	if (len == n) {
	    if (st == (1<<m) - 1) return ans = 1;
	    return ans = 0;
	}
	for (int i = 0; i < SIGMA_SIZE; i++)
	    ans += dfs(ch[now][i], len + 1, st|val[ch[now][i]]);
	return ans;
    }

    void print(int now, int len, int st) {
	if (len == n) {
	    for (int i = 0; i < len ;i++)
		printf("%c", out[i] + 'a');
	    printf("\n");
	    return;
	}
	for (int i = 0; i < SIGMA_SIZE; i++) {
	    if (dp[ch[now][i]][len + 1][st|val[ch[now][i]]] > 0) {
		out[len] = i;
		print(ch[now][i], len + 1, st|val[ch[now][i]]);
	    }
	}
    }

    void solve() {
	char str[15];
	for (int i = 0; i < m; i++) {
	    scanf("%s", str);
	    insert(str, i);
	}
	getnext();
	memset(dp, -1, sizeof(dp));
	ll ans = dfs(0, 0, 0);
	printf("%lld suspects\n", ans);
	if (ans <= 42)
	    print(0, 0, 0);
    }

} gao;


int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &m) && n || m) {
	printf("Case %d: ", ++cas);
	gao.init();
	gao.solve();
    }
    return 0;
}
