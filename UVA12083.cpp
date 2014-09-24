#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

const int N = 505;

struct People {
	int h;
	string music, sport;
	People() {}
	People(int h, string music, string sport) {
		this->h = h;
		this->music = music;
		this->sport = sport;
	}
}boy[N], girl[N];

vector<int> g[N];

int bn, gn;

int T, n;

bool judge(People a, People b) {
	if (abs(a.h - b.h) <= 40 && a.music == b.music && a.sport != b.sport) return true;
	return false;
}

int match[N], vis[N];

bool dfs(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int hungary() {
	int ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < bn; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		int h; bn = gn = 0;
		string sex, music, sport;
		for (int i = 0; i < n; i++) {
			cin >> h >> sex >> music >> sport;
			if (sex == "M") boy[bn++] = People(h, music, sport);
			else girl[gn++] = People(h, music, sport);
		}
		for (int i = 0; i < bn; i++) {
			g[i].clear();
			for (int j = 0; j < gn; j++) {
				if (judge(boy[i], girl[j]))
					g[i].push_back(j);
			}
		}
		printf("%d\n", n - hungary());
	}
	return 0;
}
