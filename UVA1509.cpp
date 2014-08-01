#include <cstdio>
#include <cstring>

const int N = 305;
int t, k, n, m, v[N], len[N];
char a[60], b[60];
char hash[N][5];

bool dfs(int nnow, int mnow) {
    if (n * 3 < m) return false;
    if (nnow == n && mnow == m) return true;
    if (nnow == n || mnow == m) return false;
    if (v[a[nnow]]) {
	if (len[a[nnow]] <= m - mnow) {
	    if (strncmp(hash[a[nnow]], b + mnow, len[a[nnow]]) == 0) {
		if (dfs(nnow + 1, mnow + len[a[nnow]]))
		    return true;
	    }
	}
    }
    else {
	len[a[nnow]] = 0;
	for (int i = mnow; i < m && i < mnow + k; i++) {
	    hash[a[nnow]][len[a[nnow]]++] = b[i];
	    hash[a[nnow]][len[a[nnow]]] = '\0';
	    v[a[nnow]] = 1;
	    if (dfs(nnow + 1, i + 1)) return true;
	    v[a[nnow]] = 0;
	}
    }
    return false;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	memset(v, 0, sizeof(v));
	scanf("%d%s%s", &k, a, b);
	n = strlen(a); m = strlen(b);
	printf("%d\n", dfs(0, 0) ? 1 : 0);
    }
    return 0;
}
