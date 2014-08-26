#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

const int MAXNODE = 1000005;
const int SIGMA_SIZE = 95;

struct Trie {

    int ch[MAXNODE][SIGMA_SIZE];
    vector<int> val[MAXNODE];
    int sz;

    int n;
    char name[105][260];
    char s[260], ss[260];
    int cnt[105];
    int ans[105], an;

    void init() {
	sz = 1; 
	memset(ch[0], 0, sizeof(ch[0]));
	memset(cnt, 0, sizeof(cnt));
    }

    int idx(char c) {return c - 32;}

    void insert(char *str, int v) {
	int n = strlen(str);
	int u = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(str[i]);
	    if (!ch[u][c]) {
		memset(ch[0], 0, sizeof(ch[0]));
		val[sz].clear();
		ch[u][c] = sz++;
	    }
	    u = ch[u][c];
	}
	val[u].push_back(v);
    }

    void handle(char *s) {
	int len = strlen(s);
	int sn = 0;
	int l = 0, r = len - 1;
	while (s[l] == ' ') l++;
	while (s[r] == ' ') r--;
	for (int i = l; i <= r; i++) {
	    ss[sn++] = s[i];
	    while (s[i] == ' ' && s[i + 1] == ' ' && i < r) i++;
	}
	ss[sn] = '\0';
	s = ss;
	printf("%s\n", s);
    }

    void cal(char *str) {
	int n = strlen(str);
	int u = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(str[i]);
	    if (!ch[u][c]) return;
	    u = ch[u][c];
	}
	for (int i = 0; i < val[u].size(); i++)
	    cnt[val[u][i]]++;
    }

    void solve() {
	init();
	for (int i = 0; i < n; i++) {
	    scanf("%s%*c", name[i]);
	    while (gets(s)) {
		if (strcmp(s, "***END***") == 0) break;
		handle(s);
		insert(s, i);
	    }
	}
	while (gets(s)) {
	    if (strcmp(s, "***END***") == 0) break;
	    handle(s);
	    cal(s);
	}

	int Max = 0; an = 0;
	for (int i = 0; i < n; i++) {
	    if (cnt[i] > Max) {
		Max = cnt[i];
		an = 0;
		ans[an++] = i;
	    }
	    else if (cnt[i] == Max) ans[an++] = i;
	}
	printf("%d", an);
	for (int i = 0; i < an; i++)
	    printf(" %s", name[ans[i]]);
	printf("\n");
    }

} gao;

int main() {
    while (~scanf("%d", &gao.n)) {
	gao.solve();
    }
    return 0;
}
