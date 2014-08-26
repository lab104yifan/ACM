#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200005;

int t, p[N * 2], n, len;
char str[N], s[N * 2];

void manachar() {
    len = 2;
    s[0] = '@'; s[1] = '#';
    for (int i = 0; i < n; i++) {
	s[len++] = str[i];
	s[len++] = '#';
    }
    s[len] = '\0';
    int mx = 0, id;
    for (int i = 1; i < len; i++) {
	if (mx > i) p[i] = min(p[2 * id - i], mx - i);
	else p[i] = 1;
	while (s[i + p[i]] == s[i - p[i]]) p[i]++;
	if (i + p[i] > mx) {
	    id = i;
	    mx = i + p[i];
	}
    }
}

int judge() {
    int need = 0;
    for (int i = 2; i < len - 1; i++) {
	if ((p[i] - 1) / 2 == need) {
	    int l = i + p[i] - 1;
	    int r = len - 1;
	    int mid = (l + r) / 2;
	    int lneed = need * 2;
	    if (s[i] != '#') lneed++;
	    int rneed = n - lneed;
	    if (rneed && rneed == p[mid] - 1) return 0;
	}
	if (s[i] != '#') need++;
    }
    if (p[len / 2] - 1 == n) return 1;
    return 2;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	n = strlen(str);
	manachar();
	if (judge() == 0) printf("alindrome\n");
	else if (judge() == 1) printf("palindrome\n");
	else printf("simple\n");
    }
    return 0;
}
