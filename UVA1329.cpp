#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 20005;

int t, n, parent[N], d[N];

int find(int x) {
    if (x == parent[x]) return x;
    int px = find(parent[x]);
    d[x] += d[parent[x]];
    return parent[x] = px;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
	    parent[i] = i; d[i] = 0;
	}
	char q[5];
	int a, b;
	while (~scanf("%s", q)) {
	    if (q[0] == 'O') break;
	    if (q[0] == 'E') {
		scanf("%d", &a);
		find(a);
		printf("%d\n", d[a]);
	    }
	    if (q[0] == 'I') {
		scanf("%d%d", &a, &b);
		int pa = find(a);
		int pb = find(b);
		parent[a] = b;
		d[a] = abs(a - b) % 1000;
	    }
	}
    }
    return 0;
}
