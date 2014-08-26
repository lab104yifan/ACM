#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200005;
const int M = 10005;

int t, n, num[N], cnt[M];

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	    scanf("%d", &num[i]);
	int q, l, r;
	scanf("%d", &q);
	while (q--) {
	    scanf("%d%d", &l, &r);
	    if (r - l + 1 >= 10000) {
		printf("0\n");
		continue;
	    }
	    memset(cnt, 0, sizeof(cnt));
	    int flag = 1, Max = 0;
	    for (int i = l; i <= r; i++) {
		cnt[num[i]]++;
		Max = max(Max, num[i]);
		if (cnt[num[i]] == 2) {
		    printf("0\n");
		    flag = 0;
		    break;
		}
	    }
	    if (flag) {
		int pre = -1;
		int ans = 10000;
		for (int i = 1; i <= Max; i++) {
		    if (cnt[i]) {
			if (pre != -1)
			    ans = min(ans, i - pre);
			pre = i;
		    }
		}
		printf("%d\n", ans);
	    }
	}
    }
    return 0;
}
