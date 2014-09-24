#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 505;

int t, c, d, n;

struct People {
	int a, b;
	People() {}
	People(int a, int b) {
		this->a = a;
		this->b = b;
	}
} cat[N], dog[N];

int cn, dn;
vector<int> g[N];

char A[105], B[105];

int match[N], vis[N];

bool dfs(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int hungary() {
	int ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < cn; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &c, &d, &n);
		for (int i = 0; i < n; i++) g[i].clear();
		cn = 0; dn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s%s", A, B);
			int aa, bb;
			sscanf(A + 1, "%d", &aa);
			sscanf(B + 1, "%d", &bb);
			if (A[0] == 'C') cat[cn++] = People(aa, bb);
			else dog[dn++] = People(aa, bb);
		}
		for (int i = 0; i < cn; i++)
			for (int j = 0; j < dn; j++) {
				if (cat[i].b == dog[j].a || cat[i].a == dog[j].b)
					g[i].push_back(j);
			}
		printf("%d\n", n - hungary());
	}
	return 0;
}
