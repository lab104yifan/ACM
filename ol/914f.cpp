#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int rot[4][6] = { {4, 3, 1, 2, 5, 6},
						{3, 4, 2, 1, 5, 6},
						{6, 5, 3, 4, 1, 2},
						{5, 6, 3, 4, 2, 1}};

struct Dice {
	int v[6];
	int hash() {
		int ans = 0;
		for (int i = 0; i < 6; i++)
			ans = ans * 6 + v[i];
		return ans;
	}
};

Dice rotate(const int *type, Dice a) {
	Dice b;
	for (int i = 0; i < 6; i++)
		b.v[type[i] - 1] = a.v[i];
	return b;
}

int vis[55555];
int main() {
	Dice st, ed;
	while (~scanf("%d", &st.v[0])) {
		for (int i = 1; i < 6; i++)
			scanf("%d", &st.v[i]);
		for (int i = 0; i < 6; i++)
			scanf("%d", &ed.v[i]);
		queue<Dice> Q;
		Q.push(st);
		memset(vis, 0, sizeof(vis));
		vis[st.hash()] = 0;
		int flag = 1;
		while (!Q.empty()) {
			Dice u = Q.front();
			Q.pop();
			if (u.hash() == ed.hash()) {
				printf("%d\n", vis[ed.hash()]);
				flag = 0;
				break;
			}
			for (int i = 0; i < 4; i++) {
				Dice v = rotate(rot[i], u);
				if (vis[v.hash()]) continue;
				Q.push(v);
				vis[v.hash()] = vis[u.hash()] + 1;
			}
		}
		if (flag) printf("-1\n");
	}
	return 0;
}
