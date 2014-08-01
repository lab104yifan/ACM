#include <cstdio>
#include <cstring>

const int N = 100005;

int x, y, parent[N];

int find(int x) {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}
int main() {
    while (~scanf("%d", &x)) {
	int cnt = 0;
	for (int i = 0; i < N; i++)
	    parent[i] = i;
	while (x != -1) {
	    scanf("%d", &y);
	    x = find(x); y = find(y);
	    if (x == y) cnt++;
	    else parent[x] = y;
	    scanf("%d", &x);
	}
	printf("%d\n", cnt);
    }
    return 0;
}
