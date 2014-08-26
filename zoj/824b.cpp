#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10005;

int n;
vector<int> g[N];

int dfs(int u) {
    int sz = g[u].size();
    vector<int> save;
    for (int i = 0; i < sz; i++)
	save.push_back(dfs(g[u][i]));
    sort(save.begin(), save.end());
    sz = save.size();
    int cnt = 0;
    int ans = 1;
    for (int i = sz - 1; i >= 0; i--) {
	if (i != sz - 1 && save[i] != save[i + 1]) break;
	ans = save[i] + cnt;
	cnt++;
    }
    return ans;
}

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 1; i <= n; i++)
	    g[i].clear();
	int v;
	for (int i = 2; i <= n; i++) {
	    scanf("%d", &v);
	    g[v].push_back(i);
	}
	printf("%d\n", dfs(1));
    }
    return 0;
}
