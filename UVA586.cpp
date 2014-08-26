#include <cstdio>
#include <cstring>

int t, ans[15];
char c[10], str[105];

void dfs(int x, int k) {
    int sum = 0;
    while (~scanf("%s", c)) {
	if (c[0] == 'E') {
	    ans[k] += x * sum;
	    return;
	}
	int num;
	scanf("%s", str);
	if (c[0] == 'L') {
	    if (str[0] == 'n')
		dfs(x, k + 1);
	    else {
		sscanf(str, "%d", &num);
		dfs(x * num, k);
	    }
	}
	else {
	    sscanf(str, "%d", &num);
	    sum += num;
	}
    }
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%s", c);
	memset(ans, 0, sizeof(ans));
	dfs(1, 0);
	printf("Program #%d\n", ++cas);
	printf("Runtime = ");
	int bo = 0;
	int flag = 1;
	for (int i = 10; i > 0; i--) {
	    if (!ans[i]) continue;
	    flag = 0;
	    if (bo++) printf("+");
	    if (ans[i] != 1) printf("%d*", ans[i]);
	    if (i == 1) printf("n");
	    else printf("n^%d", i);
	}
	if (ans[0]) {
	    flag = 0;
	    if (bo++) printf("+");
	    printf("%d", ans[0]);
	}
	if (flag) printf("0");
	printf("\n\n");
    }
    return 0;
}
