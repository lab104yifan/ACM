#include <cstdio>
#include <cstring>

const int N = 55;

int t, n, H[N], ans;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &H[i]);
		ans = 0;
		for (int i = 2; i <= n - 1; i++) {
			if (H[i] > H[i - 1] && H[i] > H[i + 1])
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
