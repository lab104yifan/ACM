#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 105;

int n, m, ans[N][N];

struct State {
	int num, id;
} p[N], t[N];

bool cmp(State a, State b) {
	return a.num > b.num;
}

bool judge() {
	for (int i = 1; i <= n; i++) {
		int s = 1;
		for (int j = 1; j <= p[i].num; j++) {
			while (t[s].num == 0 && s <= m) s++;
			if (s > m) return false;
			ans[i][j] = t[s].id;
			t[s++].num--;
		}
	}
	return true;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &p[i].num);
		for (int i = 1; i <= m; i++) {
			scanf("%d", &t[i].num);
			t[i].id = i;
		}
		sort(t + 1, t + m + 1, cmp);
		if (!judge()) printf("0\n");
		else {
			printf("1\n");
			for (int i = 1; i <= n; i++) {
				printf("%d", ans[i][1]);
				for (int j = 2; j <= p[i].num; j++)
					printf(" %d", ans[i][j]);
				printf("\n");
			}
		}
	}
	return 0;
}
