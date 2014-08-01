#include <cstdio>
#include <cstring>

const int N = 1005;
const int MAXN = 4000005;

int n;
char str[N];
long long ans;

struct Node {
    char c;
    int val;
} node[MAXN];

int first[MAXN], next[MAXN], sz;

void init() {
    ans = 0;
    sz = 1;
    first[0] = 0; next[0] = 0; node[0].val = 0;
}

void insert(char *str) {
    int u = 0, len = strlen(str);
    for (int i = 0; i <= len; i++) {
	bool flag = true;
	int v, tmp;
	for (v = first[u]; v; v = next[v]) {
	    if (node[v].c == str[i]) {
		tmp = v;
		flag = false;
		ans += node[v].val * 2;
	    }
	    else ans += node[v].val;
	}
	if (flag) {
	    v = sz++;
	    node[v].c = str[i];
	    node[v].val = 0;
	    first[v] = 0;
	    next[v] = first[u];
	    first[u] = v;
	}
	else v = tmp;
	u = v;
	node[u].val++;
    }
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	init();
	while (n--) {
	    scanf("%s", str);
	    insert(str);
	}
	printf("Case %d: %lld\n", ++cas, ans);
    }
    return 0;
}
