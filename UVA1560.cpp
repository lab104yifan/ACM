#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int d[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int N = 6;
int t, g[N][N], tmp[N][N], out[N][N];

bool judge(int s) {
    memset(out, 0, sizeof(out));
    for (int i = 0; i < 5; i++)
	for (int j = 0; j < 6; j++)
	    tmp[i][j] = g[i][j];
    for (int i = 0; i < 6; i++) {
	if (s&(1<<i)) {
	    out[0][i] = 1;
	    for (int j = 0; j < 5; j++) {
		int xx = d[j][0];
		int yy = i + d[j][1];
		if (xx < 0 || yy < 0 || xx >= 5 || yy >= 6) continue;
		tmp[xx][yy] = (!tmp[xx][yy]);
	    }
	}
    }
    for (int i = 1; i < 5; i++) {
	for (int j = 0; j < 6; j++) {
	    if (tmp[i - 1][j]) {
		out[i][j] = 1;
		for (int k = 0; k < 5; k++) {
		    int xx = i + d[k][0];
		    int yy = j + d[k][1];
		    if (xx < 0 || yy < 0 || xx >= 5 || yy >= 6) continue;
		    tmp[xx][yy] = (!tmp[xx][yy]);
		}
	    }
	}
    }
    for (int i = 0; i < 6; i++)
	if (tmp[4][i]) return false;
    return true;
}

void solve() {
    for (int i = 0; i < (1<<6); i++)
	if (judge(i)) return;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	for (int i = 0; i < 5; i++)
	    for (int j = 0; j < 6; j++)
		scanf("%d", &g[i][j]);
	solve();
	printf("PUZZLE #%d\n", ++cas);
	for (int i = 0; i < 5; i++) {
	    for (int j = 0; j < 5; j++)
		printf("%d ", out[i][j]);
	    printf("%d\n", out[i][5]);
	}
    }
    return 0;
}
