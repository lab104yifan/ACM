#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 35;
int n;
int a[N][N], b[N][N];

int solve() {
    int ans[4];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	    if (b[i][j] == a[i][j]) ans[0]++;
	    if (b[j][n - i - 1] == a[i][j]) ans[1]++;
	    if (b[n - i - 1][n - j - 1] == a[i][j]) ans[2]++;
	    if (b[n - j - 1][i] == a[i][j]) ans[3]++;
	}
    }
    int Max = 0;
    for (int i = 0; i < 4; i++)
	Max = max(Max, ans[i]);
    return Max;
}

int main() {
    while (~scanf("%d", &n) && n) {
	for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
		scanf("%d", &a[i][j]);
	for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
		scanf("%d", &b[i][j]);
	printf("%d\n", solve());
    }
    return 0;
}
