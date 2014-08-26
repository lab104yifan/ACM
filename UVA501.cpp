#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int N = 30005;

int t, m, q, vis[N], num[N];

void solve() {
    priority_queue<int> a;
    priority_queue<int, vector<int>, greater<int> > b;
    for (int i = 1; i <= m; i++) {
	a.push(num[i]);
	b.push(a.top());
	a.pop();
	while (vis[i]--) {
	    printf("%d\n", b.top());
	    a.push(b.top());
	    b.pop();
	}
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &m, &q);
	for (int i = 1; i <= m; i++)
	    scanf("%d", &num[i]);
	memset(vis, 0, sizeof(vis));
	while (q--) {
	    scanf("%d", &num[0]);
	    vis[num[0]]++;
	}
	solve();
	if (t) printf("\n");
    }
    return 0;
}
