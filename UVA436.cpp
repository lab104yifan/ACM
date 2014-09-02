#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
using namespace std;

const int N = 35;

int n;
double g[N][N];
map<string, int> hash;

int main() {
	int cas = 0;
	while (~scanf("%d", &n) && n) {
		string a, b;
		hash.clear();
		for (int i = 1; i <= n; i++) {
			cin >> a;
			hash[a] = i;
		}
		int m;
		double f;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) g[i][j] = 1.0;
				else g[i][j] = 0;
			}
		}
		scanf("%d", &m);
		while (m--) {
			cin >> a >> f >> b;
			int u = hash[a], v = hash[b];
			g[u][v] = f;
		}
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					g[i][j] = max(g[i][j], g[i][k] * g[k][j]);
			}
		}
		printf("Case %d: ", ++cas);
		int flag = 1;
		for (int i = 1; i <= n; i++) {
			if (g[i][i] > 1.0) {
				printf("Yes\n");
				flag = 0;
				break;
			}
		}
		if (flag) printf("No\n");
	}
	return 0;
}
