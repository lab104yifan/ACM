#include <cstdio>
#include <cstring>

const int N = 100005;
int t, n, m, a[32], s[N];
typedef long long ll;

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		ll ans = 0;
		memset(a, 0, sizeof(a));
		scanf("%d%d", &n, &m);
		int l = 0, num;
		for (int i = 0; i < n; i++) {
			scanf("%d", &s[i]);
			int cnt = 0;
			num = s[i];
			while (num) {
				if (num&1)
					a[cnt]++;
				num /= 2;
				cnt++;
			}
			int tmp = 0;
			for (int j = 30; j >= 0; j--)
				tmp = tmp * 2 + (a[j] != 0);
			if (tmp >= m) {
				while (1) {
					num = s[l];
					int cnt = 0;
					while (num) {
						if (num&1)
							a[cnt]--;
						num /= 2;
						cnt++;
					}
					int tmp = 0;
					for (int j = 30; j >= 0; j--)
						tmp = tmp * 2 + (a[j] != 0);
					l++;
					if (tmp < m) {
						ans += (i - l + 1);
						break;
					}
				}
			} else ans += (i - l + 1);
		}
		printf("Case #%d: %I64d\n", ++cas, ans);
	}
	return 0;
}
