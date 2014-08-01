#include <cstdio>
#include <cstring>

const int MOD = 20071027;
const int N = 300005;

char str[N], word[105];
int S, sz;

struct Node {
    int next[26], val;
} node[N];

void insert(char *str) {
    int len = strlen(str);
    int u = 0;
    for (int i = 0; i < len; i++) {
	int v = str[i] - 'a';
	if (node[u].next[v])
	    u = node[u].next[v];
	else {
	    node[u].next[v] = sz++;
	    u = node[u].next[v];
	    node[u].val = 0;
	    memset(node[u].next, 0, sizeof(node[u].next));
	}
    }
    node[u].val = 1;
}

void init() {
    sz = 1;
    memset(node[0].next, 0, sizeof(node[0].next));
    node[0].val = 0;
}

int dp[N];

void find(int i) {
    int u = 0;
    dp[i] = 0;
    for (int j = i; str[j]; j++) {
	int v = str[j] - 'a';
	if (!node[u].next[v]) return;
       	u = node[u].next[v];
	if (node[u].val) dp[i] = (dp[i] + dp[j + 1]) % MOD;
    }
}

int main() {
    int cas = 0;
    while (~scanf("%s", str)) {
	scanf("%d", &S);
	init();
	while (S--) {
	    scanf("%s", word);
	    insert(word);
	}
	int len = strlen(str);
	dp[len] = 1;
	for (int i = len - 1; i >= 0; i--)
	    find(i);
	printf("Case %d: %d\n", ++cas, dp[0]);
    }
    return 0;
}
