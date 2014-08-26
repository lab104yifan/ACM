#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000005;

char str[N];
int n, up[N], down[N], lup[N], ldown[N];

bool init() {
    up[n - 1] = down[n - 1] = 1;
    int cnt = 0;
    for (int i = n - 2; i >= 0; i--) {
	if (str[i] == ')') {
	    up[i] = up[i + 1] + 1;
	    down[i] = down[i + 1] + 1;
	}
	else if (str[i] == '(') {
	    up[i] = up[i + 1] - 1;
	    down[i] = down[i + 1] - 1;
	    if (down[i] < 0) {
		if (cnt == 0) return false;
		cnt--;
		if (up[i] == down[i]) up[i] = 1;
		down[i] = 1;
	    }
	}
	else {
	    up[i] = up[i + 1] + 1;
	    down[i] = down[i + 1] - 1;
	    if (down[i + 1] > 0 || cnt > 0) {
		down[i] = down[i + 1] - 1;
		if (down[i] < 0) {
		    down[i] = 1;
		    cnt--;
		}
	    }
	    else down[i] = down[i + 1] + 1;
	    cnt++;
	}
    }
    return (down[0] == 0);
}

void solve() {
    n = strlen(str);
    
    if (!init()) {
	printf("None\n");
	return;
    }
    lup[0] = ldown[9] = 1;
    for (int i = 1; i < n - 1; i++) {
	if (str[i] == '(') {
	    lup[i] = lup[i - 1] + 1;
	    ldown[i] = ldown[i - 1] + 1;
	}
	else if (str[i] == ')') {
	    ldown[i] = ldown[i - 1] - 1;
	    lup[i] = lup[i - 1] - 1;
	    if (ldown[i] < 0) {
		if (lup[i] == ldown[i]) lup[i] = 1;
		ldown[i] = 1;
	    }
	}
	else {
	    int flag = 0;
	    lup[i] = lup[i - 1] + 1;
	    ldown[i] = ldown[i - 1] - 1;
	    if (ldown[i] < 0) ldown[i] = 1;
	    int u, d;
	    u = lup[i - 1] + 1;
	    d = ldown[i - 1] + 1;
	    if (u >= down[i + 1] && d <= up[i + 1])
		flag++;
	    u = max(0, lup[i - 1] - 1);
	    d = max(0, ldown[i - 1] - 1);
	    if (u >= down[i + 1] && d <= up[i + 1])
		flag++;
	    if (flag == 2) {
		printf("Many\n");
		return;
	    }
	}
    }
    printf("Unique\n");
}

int main() {
    while (~scanf("%s", str)) {
	solve();
    }
    return 0;
}
