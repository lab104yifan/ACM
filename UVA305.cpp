#include <cstdio>
#include <cstring>

int k, ans[15];

bool judge(int num, int k) {
    int now = 0;
    for (int i = num * 2; i > num; i--) {
	now = (now - 1 + k) % i;
	if (now < num) return false;
    }
    return true;
}

int solve(int k) {
    for (int i = k + 1; ;i++) {
	if (judge(k, i)) 
	    return i;
    }
    return -1;
}

int main() {
    for (int i = 1; i < 14; i++)
	ans[i] = solve(i);
    while (~scanf("%d", &k) && k) {
	printf("%d\n", ans[k]);
    }
    return 0;
}
