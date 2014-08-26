#include <cstdio>
#include <cstring>

const int N = 105;

int t, dp[2][N][15][15];

char L[N], R[N];

void solve(int ff, int *str) {
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
	int tmp = str[i] - '0';
	for (int j = 0; j < tmp; j++) {
	    for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
		    if (i % 2 == 0) {
			dp[ff][i][(x + j) % 9][y] = (dp[ff][i][(x + j) % 9][y] + dp[ff][i - 1][x][y]) % 9;
		    }
		    else {
			dp[ff][i][x][(y + j) % 9] = (dp[ff][i][x][(y + j) % 9] + dp[ff][i - 1][x][y]) % 9;
		    }
		}
	    }
	}
	dp[ff][i][(x + tmp) % 9][y] = dp[ff][i][(x + tmp) % 9][y] + 
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scnaf("%s%s", L, R);
	solve(0, L);
	solve(1, R);
    }
    return 0;
}
