#include <cstdio>
#include <cstring>

const int N = 1005;

int n, a[N], t;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int ans = 0;
		for (int i = 0; i < n - 1; i++) {
			if (a[i] > 1) break;
			ans++;
		}
		printf("%s\n", ans % 2 ? "No" : "Yes");
	}
	return 0;
}
