#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1005;

int r, c, n, left[N], right[N], S[N], T[N];
vector<int> g[N];

bool dfs(int u) {
	S[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (T[v]) continue;
		T[v] = 1;
		if (!left[v] || dfs(left[v])) {
			left[v] = u;
			right[u] = v;
			return true;
		}
	}
	return false;
}

int hungary() {
	int sum = 0;
	memset(left, 0, sizeof(left));
	memset(right, 0, sizeof(right));
	for (int i = 1; i <= r; i++) {
		memset(S, 0, sizeof(S));
		memset(T, 0, sizeof(T));
		if (dfs(i)) sum++;
	}
	return sum;
}

void print() {
	memset(S, 0, sizeof(S));
	memset(T, 0, sizeof(T));
	for (int i = 1; i <= r; i++) {
		if (!right[i])
			dfs(i);
	}
	for (int i = 1; i <= r; i++)
		if (!S[i]) printf(" r%d", i);
	for (int i = 1; i <= c; i++)
		if (T[i]) printf(" c%d", i);
	printf("\n");
}

int main() {
	while (~scanf("%d%d%d", &r, &c, &n) && n) {
		for (int i = 1; i <= r; i++)
			g[i].clear();
		int x, y;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
		}
		printf("%d", hungary());
		print();
	}
	return 0;
}
