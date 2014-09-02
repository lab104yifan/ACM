#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 5005;

int n, m, vis[N], Q[N], from[N], ans[N];
vector<int> s;

void print(int u) {
	if (u == -1) return;
	print(from[u]);
	printf("%d", ans[u]);
}

int main() {
	while (~scanf("%d", &n)) {
		scanf("%d", &m);
		s.clear();
		int num;
		memset(vis, 0, sizeof(vis));
		int head = 0, rear = 0;
		while (m--) {
			scanf("%d", &num);
			s.push_back(num);
		}
		sort(s.begin(), s.end());
		if (n == 0) {
			printf("0\n");
			continue;
		}
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 0) continue;
			int tmp = s[i] % n;
			ans[rear] = s[i];
			from[rear] = -1;
			Q[rear++] = tmp;
			vis[tmp] = 1;
		}
		int flag = 1;
		while (head < rear) {
			int u = Q[head];
			if (u == 0) {
				print(head);
				flag = 0;
				printf("\n");
				break;
			}
			for (int i = 0; i < s.size(); i++) {
				int tmp = (u * 10 + s[i]) % n;
				if (!vis[tmp]) {
					vis[tmp] = 1;
					Q[rear] = tmp;
					ans[rear] = s[i];
					from[rear++] = head;
				}
			}
			head++;
		}
		if (flag) printf("0\n");
	}
	return 0;
}
