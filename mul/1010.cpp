#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Player {
    int rank[15];
} p1, p2;

int t, hash[205], cnt[(1<<20)], vis[20];
char a[25], b[25];

int bitcount(int x) {
    int ans = 0;
    while (x) {
	ans += (x&1);
	x >>= 1;
    }
    return ans;
}

void add(int num, Player &p) {
    if (num == 2) {
	if (vis[14] && vis[15]) {
	    p.rank[7] = 14;
	    return;
	}
    }
    if (num == 5) {
	int a = 0, b = 0;
	for (int i = 15; i >= 1; i--) {
	    if (vis[i] == 3) a = i;
	    if (vis[i] == 2) b = i;
	}
	if (a && b) {
	    p.rank[5] = max(p.rank[5], a);
	}
	return;
    }
    for (int i = 15; i >= 1; i--) {
	if (num == 4 && vis[i] == 4) {
	    p.rank[7] = max(p.rank[7], i);
	    return;
	}
	if (num == 4 && vis[i] == 3) {
	    p.rank[4] = max(p.rank[4], i);
	    return;
	}
	if (num == 6 && vis[i] == 4) {
	    p.rank[6] = max(p.rank[6], i);
	    return;
	}
	if (vis[i] == num) {
	    p.rank[num] = max(p.rank[num], i);
	    return;
	}
    }
}

void build(char *a, Player &p) {
    memset(p.rank, 0, sizeof(p.rank));
    int n = strlen(a);
    int maxs = (1<<n);
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < maxs; i++) {
	if (cnt[i] > 6) continue;
	memset(vis, 0, sizeof(vis));
	for (int j = 0; j < n; j++) {
	    if (i&(1<<j)) {
		vis[hash[a[j]]]++;
	    }
	}
	add(cnt[i], p);
    }
}

bool solve() {
    int n = strlen(a);
    if (n == 4) {
	if (p1.rank[7]) return true;
    }
    if (n <= 6) {
	if (p1.rank[n]) return true;
    }
    if (p1.rank[7] && p2.rank[7]) return p1.rank[7] > p2.rank[7];
    if (p1.rank[7] && !p2.rank[7]) return true;
    if (!p1.rank[7] && p2.rank[7]) return false;
    for (int i = 1; i < 7; i++) {
	if (p1.rank[i] > p2.rank[i]) return true;
    }
    return false;
}

int main() {
    for (int i = 0; i < (1<<20); i++)
	cnt[i] = bitcount(i);
    for (int i = 3; i <= 9; i++)
	hash[i + '0'] = i - 2;
    hash['T'] = 8; hash['J'] = 9; hash['Q'] = 10; hash['K'] = 11;
    hash['A'] = 12; hash['2'] = 13; hash['X'] = 14; hash['Y'] = 15;
    scanf("%d", &t);
    while (t--) {
	scanf("%s%s", a, b);
	build(a, p1);
	build(b, p2);
	if (solve()) printf("Yes\n");
	else printf("No\n");
    }
    return 0;
}
