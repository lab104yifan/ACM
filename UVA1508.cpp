#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 5;
int t, n, k, a[N], s[(1<<N) + 5];

void build() {
    for (int i = 0; i < (1<<5); i++) {
	int sum = 0;
	for (int j = 0; j < 5; j++) {
	    if (i&(1<<j))
		sum += a[j];
	}
	s[i] = max(s[i], sum);
    }
}

int dfs(int st, int d) {
    if (d == k) {
	if (st != 0) return -INF;
	return 0;
    }
    int ans = 0;
    for (int i = st; i; i = (i - 1)&st)
	ans = max(ans, dfs(st^i, d + 1) + s[i]);
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &k);
	k = min(k, 5);
	memset(s, 0, sizeof(s));
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < 5; j++)
		scanf("%d", &a[j]);
	    build();
	}
	printf("%d\n", dfs((1<<5) - 1, 0));
    }
    return 0;
}
