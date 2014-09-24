#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int N = 100005;
const ull seed = 123;

int t, n, m, st, en;
char str[N];
ull s[8][N], Hp[N], e[N];

int bo = 0;

struct Path {
	int u, dir, pos, end;
	Path() {}
	Path(int u, int dir, int pos, int end) {
		this->u = u;
		this->dir = dir;
		this->pos = pos;
		this->end = end;
	}
	void print() {
		if (dir == 0) {
			for (int i = pos; i <= end; i++) {
				if (bo) printf(" ");
				else bo = 1;
				printf("%d", u * n + i);
			}
		} else {
			for (int i = pos; i <= end; i++) {
				if (bo) printf(" ");
				else bo = 1;
				printf("%d", u * n + (n - i + 1));
			}
		}
	}
} ans[N];

int an;

bool dfs(int u, int dir, int pos, int len, ull hash) {
	ans[an++] = Path(u, dir, pos, n);
	if (len + n - pos + 1 >= m) {
		int tmpl = m - len;
		ull nh = hash + Hp[len] * (s[u * 2 + dir][pos] - s[u * 2 + dir][pos + tmpl] * Hp[tmpl]);
		if (nh == e[1]) {
			ans[an - 1].end = pos + tmpl - 1;
			return true;
		}
		an--;
		return false;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			if (i == u && (j^1) == dir) continue;
			int nl; ull nh;
			nl = len + n - pos + 1;
			nh = hash + Hp[len] * s[u * 2 + dir][pos];
			if (nh != e[1] - e[nl + 1] * Hp[nl]) continue;
			if (dfs(i, j, 1, nl, nh)) return true;
		}
	}
	an--;
	return false;
}

bool solve() {
	an = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 1; k <= n; k++) {
				if (dfs(i, j, k, 0, 0)) return true;
			}
		}
	}
	return false;
}

int main() {
	Hp[0] = 1;
	for (int i = 1; i < N; i++)
		Hp[i] = Hp[i - 1] * seed;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < 4; i++) {
			scanf("%s", str + 1);
			s[i * 2][n + 1] = 0;
			for (int j = n; j >= 1; j--)
				s[i * 2][j] = s[i * 2][j + 1] * seed + str[j];
			s[i * 2 + 1][n + 1] = 0;
			for (int j = n; j >= 1; j--)
				s[i * 2 + 1][j] = s[i * 2 + 1][j + 1] * seed + str[n - j + 1];
		}
		scanf("%s", str + 1);
		e[n + 1] = 0;
		for (int j = m; j >= 1; j--)
			e[j] = e[j + 1] * seed + str[j];
		if (!solve()) printf("No solution!\n");
		else {
			bo = 0;
			for (int i = 0; i < an; i++)
				ans[i].print();
			printf("\n");
		}
	}
	return 0;
}
