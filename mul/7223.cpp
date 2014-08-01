#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef __int64 ll;
const int N = 1444;
const int M = 105;
int n, m;
ll mac[N][M], task[N][M], used[N];

int main() {
    while (~scanf("%d%d", &n, &m)) {
	int x, y;
	memset(mac, 0, sizeof(mac));
	memset(task, 0, sizeof(task));
	memset(used, 0, sizeof(used));
	for (int i = 0; i < n; i++) {
	    scanf("%d%d", &x, &y);
	    mac[x][y]++;
	}
	for (int i = 0; i < m; i++) {
	    scanf("%d%d", &x, &y);
	    task[x][y]++;
	}
	for (int i = 0; i <= 100; i++) {
	    for (int j = 1439; j > 0; j--) {
		mac[j][i] += mac[j + 1][i];
	    }
	}
	ll num = 0;
	ll ans = 0;
	for (ll i = 1439; i > 0; i--) {
	    for (ll j = 100; j >= 0; j--) {
		if (!task[i][j]) continue;
		for (ll k = j; k <= 100; k++) {
		    if (task[i][j] > mac[i][k] - used[k]) {
			num += mac[i][k] - used[k];
			ans += (mac[i][k] - used[k]) * (i * 500 + j * 2);
			task[i][j] -= (mac[i][k] - used[k]);
			used[k] = mac[i][k];
		    }
		    else {
			num += task[i][j];
			ans += task[i][j] * (i * 500 + j * 2);
			used[k] += task[i][j];
			task[i][j] = 0;
			break;
		    }
		}
	    }
	}
	printf("%I64d %I64d\n", num, ans);
    }
    return 0;
}
