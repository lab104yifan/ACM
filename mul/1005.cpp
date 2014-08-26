#include <cstdio>
#include <cstring>

const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int t, n, m;

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &m);
	int flag = 1;
	int ans = 0;
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < m; j++) {
		if (flag) {
		    int cnt = 1;
		    for (int k = 0; k < 4; k++) {
			int xx = i + d[k][0];
			int yy = j + d[k][1];
			if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
			cnt *= 2;
		    }
		    ans += cnt;
		}
		flag ^= 1;
	    }
	}
	printf("%d\n", ans);
    }	
    return 0;
}
