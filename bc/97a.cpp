#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

typedef long long ll;
ll num[105];
set<ll> save;

int n;
int main() {
	while (~scanf("%d", &n)) {
		save.clear();
		for (int i = 0; i < n; i++) {
			scanf("%I64d", &num[i]);
			for (int j = 0; j < i; j++) {
				save.insert(num[i] + num[j]);
			}
		}
		ll ans = 0;
		for (set<ll>::iterator it = save.begin(); it != save.end(); it++) {
			ans += *it;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
