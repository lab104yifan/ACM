#include <cstdio>
#include <cstring>

char a[30], b[30];
int now;

void solve(int l, int r) {
    if (l >= r) return;
    char ans = a[now];
    for (int i = l; i < r; i++) {
	if (b[i] == a[now]) {
	    now++;
	    solve(l, i);
	    solve(i + 1, r);
	    break;
	}
    }
    printf("%c", ans);
}

int main() {
    while (~scanf("%s%s", a, b)) {
	now = 0;
	solve(0, strlen(b));
	printf("\n");
    }
    return 0;
}
