#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10005;
int t, n, vis[N];

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int w;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			scanf("%d", &w);
			int s = 10000 - (100 - w) * (100 - w);
			vis[s]++;
		}
		int Max = 0;
		for (int i = 1; i <= 10000; i++)
			Max = max(vis[i], Max);
		int cnt = 0;
		for (int i = 1; i <= 10000; i++)
			if (Max == vis[i]) cnt++;
		printf("Case #%d:\n", ++cas);
		if (cnt != 1 && cnt * Max == n) printf("Bad Mushroom\n");
		else {
			int bo = 0;
			for (int i = 1; i <= 10000; i++) {
				if (Max == vis[i]) {
					if (bo) printf(" ");
					else bo = 1;
					printf("%d", i);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
