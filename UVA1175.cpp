#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 1005;
int t, n;

struct People {
	int order[N], now, match;
} man[N], woman[N];

queue<int> Q;

bool gao(int u, int v) {
	if (woman[v].match == -1) {
		woman[v].match = u;
		return true;
	} else if (woman[v].order[woman[v].match] > woman[v].order[u]) {
		man[woman[v].match].now++;
		Q.push(woman[v].match);
		woman[v].match = u;
		return true;
	}
	return false;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			man[i].now = 0;
			for (int j = 0; j < n; j++) {
				scanf("%d", &man[i].order[j]);
				man[i].order[j]--;
			}
			Q.push(i);
		}
		for (int i = 0; i < n; i++) {
			woman[i].match = -1;
			int tmp;
			for (int j = 0; j < n; j++) {
				scanf("%d", &tmp);
				tmp--;
				woman[i].order[tmp] = j;
			}
		}
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			int v = man[u].order[man[u].now];
			if (!gao(u, v)) {
				man[u].now++;
				Q.push(u);
			}
		}
		for (int i = 0; i < n; i++)
			man[woman[i].match].match = i;
		for (int i = 0; i < n; i++)
			printf("%d\n", man[i].match + 1);
		if (t) printf("\n");
	}
	return 0;
}
