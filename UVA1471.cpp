#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 200005;

int t, n, a[N], left[N], right[N], Min[N];

void init() {
    scanf("%d", &n);
    left[0] = 1; right[n - 1] = 1;
    for (int i = 0; i < n; i++) {
	scanf("%d", &a[i]);
	if (i) {
	    left[i] = 1;
	    if (a[i] > a[i - 1]) left[i] += left[i - 1];
	}
    }
    for (int i = n - 2; i >= 0; i--) {
	right[i] = 1;
	if (a[i] < a[i + 1]) right[i] += right[i + 1];
    }
}

int solve() {
    int ans = 0;
    memset(Min, INF, sizeof(Min));
    for (int i = 0; i < n; i++) {
	int len = lower_bound(Min + 1, Min + 1 + n, a[i]) - Min;
	ans = max(ans, right[i] + len - 1);
	Min[left[i]] = min(Min[left[i]], a[i]);
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	init();
	printf("%d\n", solve());
    }
    return 0;
}
