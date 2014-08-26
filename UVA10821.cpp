#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, h;

void dfs(int s, int n, int h) {
    if (h == 0 || n == 0) return;
    int tmp = max(0, n - (1<<(h - 1)));
    printf(" %d", s + tmp + 1);
    dfs(s, tmp, h - 1);
    dfs(s + tmp + 1, n - tmp - 1, h - 1);
}

int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &h) && n || h) {
	printf("Case %d:", ++cas);
	if ((1<<h) - 1 < n) {
	    printf(" Impossible.\n");
	    continue;
	}
	dfs(0, n, h);
	printf("\n");
    }
    return 0;
}
