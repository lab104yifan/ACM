#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int t, n, du[15], ans[15], tmp[15], tn;
char str[105];
vector<int> g[15];
queue<int> Q;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%s", &n, str);
		int sn = 0;
		while (!Q.empty()) Q.pop();
		for (int i = 0; i <= n; i++) {
			du[i] = 0;
			g[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				if (str[sn] == '+') {
					g[i - 1].push_back(j);
					du[j]++;
				}
				else if (str[sn] == '-') {
					g[j].push_back(i - 1);
					du[i - 1]++;
				}
				sn++;
			}
		}
		for (int i = 0; i <= n; i++)
			if (du[i] == 0) Q.push(i);
		int cnt = -10;
		while (!Q.empty()) {
			tn = 0;
			while (!Q.empty()) {
				tmp[tn] = Q.front();
				ans[tmp[tn]] = cnt;
				tn++;
				Q.pop();
			}
			for (int i = 0; i < tn; i++) {
				int u = tmp[i];
				for (int j = 0; j < g[u].size(); j++) {
					du[g[u][j]]--;
					if (du[g[u][j]] == 0)
						Q.push(g[u][j]);
				}
			}
			cnt++;
		}
		for (int i = 1; i <= n; i++) {
			printf("%d%c", ans[i] - ans[0] - (ans[i - 1] - ans[0]), i == n ? '\n' : ' ');
		}
	}
	return 0;
}
