#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int N = 100005;

typedef pair<string, int> pii;

pii str[N];
int save[N];

int t, n, height[N], rank[N];

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
	cin >> str[i].first;
	save[i] = str[i].first.length();
	str[i].second = i;
    }
    sort(str, str + n);
    for (int i = 0; i < n; i++) {
	rank[str[i].second] = i;
	if (i == 0) continue;
	int len = min(str[i - 1].first.length(), str[i].first.length());
	int j;
	for (j = 0; j < len; j++) {
	    if (str[i - 1].first[j] != str[i].first[j])
		break;
	}
	height[i] = j;
    }
}

int best[N * 10][20];

void initRMQ() {
    for (int i = 0; i < n; i++) best[i][0] = height[i];
    for (int j = 1; (1<<j) <= n; j++)
	for (int i = 0; i + (1<<j) - 1 < n; i++)
	    best[i][j] = min(best[i][j - 1], best[i + (1<<(j - 1))][j - 1]);
}

int lcp(int L, int R) {
    L--; R--;
    if (L == R) return save[L];
    L = rank[L]; R = rank[R];
    if (L > R) swap(L, R);
    L++;
    int k = 0;
    while ((1<<(k + 1)) <= R - L + 1) k++;
    return min(best[L][k], best[R - (1<<k) + 1][k]);
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	init();
	initRMQ();
	int q, l, r;
	scanf("%d", &q);
	printf("Case %d:\n", ++cas);
	while (q--) {
	    scanf("%d%d", &l, &r);
	    printf("%d\n", lcp(l, r));
	}
    }
    return 0;
}
