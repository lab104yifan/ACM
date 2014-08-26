#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1005;

int t, ans[N], n, l, r, m, next[N];
char str[N], s[N];

void getnext() {
    next[0] = next[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; i++) {
	while (j && s[i - 1] != s[j]) j = next[j];
	if (s[i - 1] == s[j]) j++;
	next[i] = j;
    }
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	memset(ans, 0, sizeof(ans));
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++) {
	    m = 0;
	    for (int j = i; j < n; j++)
		s[m++] = str[j];
	    getnext();
	    for (int j = 1; j <= m; j++) {
		int tmp = j;
		while (tmp) {
		    if (j % (j - next[tmp]) == 0) {
			int ti = j / (j - next[tmp]);
			ans[ti] = max(ans[ti], j);
		    }
		    tmp = next[tmp];
		}
	    }
	}
	printf("Case #%d:", ++cas);
	for (int i = 1; i <= n; i++)
	    printf(" %d", ans[i]);
	printf("\n");
    }
    return 0;
}
