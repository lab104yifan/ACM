#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 205;
const int M = 20005;

map<string, int> hash;
string a, b;
int hn;

int get(string a) {
	if (!hash.count(a)) hash[a] = hn++;
	return hash[a];
}

struct Edge {
	int u, v, val;
	void read() {
		cin >> a >> b >> val;
		u = get(a); v = get(b);
	}
} e[M];

bool cmp(Edge a, Edge b) {
	return a.val > b.val;
}

int n, m, parent[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

int main() {
	int cas = 0;
	while (~scanf("%d%d", &n, &m) && n || m) {
		string a, b, val;
		hash.clear(); hn = 1;
		for (int i = 1; i <= n; i++) parent[i] = i;
		for (int i = 0; i < m; i++) e[i].read();
		sort(e, e + m, cmp);
		cin >> a >> b;
		int ss = get(a), ee = get(b);
		for (int i = 0; i < m; i++) {
			int pu = find(e[i].u);
			int pv = find(e[i].v);
			if (pu != pv) {
				parent[pu] = pv;
				if (find(ss) == find(ee)) {
					printf("Scenario #%d\n", ++cas);
					printf("%d tons\n\n", e[i].val);
					break;
				}
			}
		}
	}
	return 0;
}
