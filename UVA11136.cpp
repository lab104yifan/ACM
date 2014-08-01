#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

int n, k, v;
multiset<int> save;

int main() {
    while (~scanf("%d", &n) && n) {
	save.clear();
	long long ans = 0;
	for (int i = 0; i < n; i++) {
	    scanf("%d", &k);
	    for (int j = 0; j < k; j++) {
		scanf("%d", &v);
		save.insert(v);
	    }
	    ans += (*(--save.end()) - *save.begin());
	    save.erase(save.begin());
	    save.erase(--save.end());
	}
	printf("%lld\n", ans);
    }
    return 0;
}
