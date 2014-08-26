#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1005;

int n, a[N], b[N], id[N], Min;

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	Min = 1000;
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &a[i]);
	    Min = min(Min, a[i]);
	    b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
	    id[b[i]] = i;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
	    if (a[i]) {
		int cnt = 0;
		int sum = a[i];
		int now = id[a[i]];
		int tmp = a[i];
		a[i] = 0;
		while (a[now]) {
		    cnt++;
		    sum += a[now];
		    tmp = min(tmp, a[now]);
		    int save = now;
		    now = id[a[now]];
		    a[save] = 0;
		}
		ans += min(sum + tmp * cnt - tmp, sum + 2 * (tmp + Min) + Min * cnt - tmp);
	    }
	}
	printf("Case %d: %d\n\n", ++cas, ans);
    }
    return 0;
}
