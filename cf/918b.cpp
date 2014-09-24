#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

const int N = 100005;
const int INF = 0x3f3f3f3f;
int n, m;
string str[N];
typedef pair<long long, long long> pii;
map<string, vector<string> > g;
map<string, pii> dp;
map<string ,int> vis;

int cal(string& str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] - 'A' + 'a';
	}
	int ans = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == 'r') ans++;
	dp[str].first = ans;
	dp[str].second = str.length();
	return ans;
}

pii dfs(string u) {
	vis[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		string v = g[u][i];
		dp[u] = min(dp[u], dp[v]);
		if (!vis[v])
			dfs(v);
		dp[u] = min(dp[u], dp[v]);
	}
	return dp[u];
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		cin >> str[i];
		cal(str[i]);
	}
	scanf("%d", &m);
	string u, v;
	while (m--) {
		cin >> u >> v;
		cal(u);
		cal(v);
		g[u].push_back(v);
	}
	long long ans1 = 0, ans2 = 0;
	for (int i = 0; i < n; i++) {
		dfs(str[i]);
		ans1 += dp[str[i]].first;
		ans2 += dp[str[i]].second;
	}
	printf("%lld %lld\n", ans1, ans2);
	return 0;
}
