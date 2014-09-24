#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, cur, d;

int main() {
	int cas = 0;
	while (~scanf("%d%d%d", &n, &cur, &d)) {
		printf("Case #%d: ", ++cas);
		int l = max(1, cur - d);
		if (cur == 1) printf("[<<]");
		else printf("(<<)");
		if (l != 1) printf("[...]");
		for (int i = l; i < cur; i++)
			printf("(%d)", i);
		printf("[%d]", cur);
		int r = min(n, cur + d);
		for (int i = cur + 1; i <= r; i++)
			printf("(%d)", i);
		if (r != n) printf("[...]");
		if (cur == n) printf("[>>]");
		else printf("(>>)");
		printf("\n");
	}
	return 0;
}
