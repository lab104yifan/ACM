#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

const int N = 105;
const ull x = 123;

char str[N];
ull H[N], Hp[N];
int n;

void gethash() {
    n = strlen(str);
    H[n] = 0;
    for (int i = n - 1; i >= 0; i--)
	H[i] = H[i + 1] * x + str[i] - 'a';
}

void solve() {
    int ans = n + 1;
    for (int l = 1; l <= n; l++) {
	set<ull> vis;
	int cnt = 0;
	for (int i = 0; i < n - l + 1; i++) {
	    ull tmp = H[i] - H[i + l] * Hp[l];
	    if (vis.find(tmp) == vis.end()) {
		vis.insert(tmp);
		cnt++;
	    }
	    if (cnt > l + 1) {
		ans = min(ans, i + l);
		break;
	    }
	}
    }
    if (ans != n + 1) printf("NO:%d\n", ans);
    else printf("YES\n");
}

int main() {
    Hp[0] = 1;
    for (int i = 1; i < N; i++)
	Hp[i] = Hp[i - 1] * x;
    while (gets(str) != NULL) {
	gethash();
	solve();
    }
    return 0;
}
