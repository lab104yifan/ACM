#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

const int MAXNODE = 11000;
const int SIGMA_SIZE = 26;

struct AutoMac {

	int ch[MAXNODE][SIGMA_SIZE];
	int val[MAXNODE];
	int next[MAXNODE];
	int last[MAXNODE];
	int sz;

	void init() {
		sz = 1; 
		memset(ch[0], 0, sizeof(ch[0]));
	}

	int idx(char c) {
		return c - 'a';
	}

	void insert(char *str, int v) {
		int n = strlen(str);
		int u = 0;
		for (int i = 0; i < n; i++) {
			int c = idx(str[i]);
			if (!ch[u][c]) {
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	void getnext() {
		queue<int> Q;
		next[0] = 0;	
		for (int c = 0; c < SIGMA_SIZE; c++) {
			int u = ch[0][c];
			if (u) {next[u] = 0; Q.push(u); last[u] = 0;}
		}

		while (!Q.empty()) {
			int r = Q.front(); Q.pop();
			for (int c = 0; c < SIGMA_SIZE; c++) {
				int u = ch[r][c];
				if (!u) {
					ch[r][c] = ch[next[r]][c];
					continue;
				}
				Q.push(u);
				int v = next[r];
				while (v && !ch[v][c]) v = next[v];
				next[u] = ch[v][c];
				last[u] = val[next[u]] ? next[u] : last[next[u]];
			}
		}
	}

	void print(int i, int j) {
		if (j) {
			//printf("%d: %d\n", i, val[j]);
			print(i, last[j]);
		}
	}

	void find(char *T) {
		int n = strlen(T);
		int j = 0;
		for (int i = 0; i < n; i++) {
			int c = idx(T[i]);
			j = ch[j][c];
			if (val[j]) print(i, j);
			else if (last[j]) print(i, last[j]);
		}
	}
};
