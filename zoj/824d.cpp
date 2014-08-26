#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 55;
const int d[8][2] = {{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};

typedef pair<int, int> pii;

int t;
int n, m, f, k;
int g[N][N];
int gg[N][N];
char str[55];
vector<pii> go[1005];

void solve() {
    for (int ti = 1; ti <= f; ti++) {
	memset(gg, 0, sizeof(gg));
	for (int i = 1; i <= n; i++) {
	    for (int j = 1; j <= m; j++) {
		if (g[i][j] == 1) {
		    for (int k = 0; k < 8; k++) {
			int xx = i + d[k][0];
			int yy = j + d[k][1];
			if (xx <= 0 || xx > n || yy <= 0 || yy > m) continue;
			gg[xx][yy]++;
		    }
		}
	    }
	}

	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		if (g[i][j] == 2) continue;
		else if (g[i][j] == 0) {
		    if (gg[i][j] == 3) g[i][j] = 1;
		}
		else {
		    if (gg[i][j] < 2 || gg[i][j] > 3) g[i][j] = 0;
		}
	    }
	for (int i = 0; i < go[ti].size(); i++) {
	    g[go[ti][i].first][go[ti][i].second] = 2;
	}
    }
    for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
	    if (g[i][j] == 2) printf("X");
	    else printf("%d", g[i][j]);
	}
	printf("\n");
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d%d%d", &n, &m, &f, &k);
	for (int i = 1; i <= f; i++)
	    go[i].clear();
	for (int i = 1; i <= n; i++) {
	    scanf("%s", str + 1);
	    for (int j = 1; j <= m; j++) {
		g[i][j] = str[j] - '0';
	    }
	}
	int ti, x, y;
	while (k--) {
	    scanf("%d%d%d", &ti, &x, &y);
	    go[ti].push_back(make_pair(x, y));
	}
	solve();
    }
    return 0;
}
