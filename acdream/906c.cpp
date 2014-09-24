#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;
const int MOD = 1000000007;
typedef long long ll;

int t, n, a[N], b[N];

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &b[i]);
		sort(a, a + n);
		sort(b, b + n);
		int ans = 1;
		int l = 0;
		for (int i = 0; i < n; i++) {
			while (l < n && b[i] >= a[l]) l++;
			ans = (ll)ans * (l - i) % MOD;
		}
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
}
