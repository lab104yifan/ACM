#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k, l, r, a[25], save[25], have[25], v[205], Max, vis[205];

void calmax(int num, int sum) {
    vis[sum] = 1;
    if (num == k) return;
    calmax(num + 1, sum ^ save[num]);
    calmax(num + 1, sum);
}

bool Maxcal() {
    memset(vis, 0, sizeof(vis));
    calmax(0, 0);
    for (int i = l; i <= r; i++)
	if (!vis[i]) return false;
    return true;
}

void cal() {
    if (!Maxcal()) return;
    for (int i = 0; i < k; i++)
	have[i] = save[i];
    do {
	memset(v, 0, sizeof(v));
	for (int i = 0; i < k; i++) {
	    int ans = 0;
	    for (int j = i; j < k + i; j++) {
		ans ^= have[(j % k)];
		v[ans] = 1;
	    }
	}
	for (int i = l; i <= l + k * k; i++)
	    if (!v[i]) {
		r = max(r, i - 1);
		break;
	    }
    } while(next_permutation(have + 1, have + k));
}

void dfs(int now, int num) {
    if (num == k) {
	cal();
	return;
    }
    for (int i = now; i < n; i++) {
	save[num] = a[i];
	dfs(i + 1, num + 1);
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &k, &l)) {
	for (int i = 0; i < n; i++)
	    scanf("%d", &a[i]);
	sort(a, a + n);
	r = l - 1;
	dfs(0, 0);
	if (r < l) printf("0\n");
	else printf("%d\n", r);
    }
    return 0;
}
