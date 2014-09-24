#include <cstdio>
#include <cstring>

char A[35];
int t, n, num[35], ans[35];

bool judge(int s) {
	for (int i = 0; i <= s; i++) {
		if (ans[i] > num[i]) return false;
		else if (ans[i] < num[i]) return true;
	}
	return true;
}

bool check() {
	for (int i = 0; i < n; i++) {
		if (num[i] > ans[i])
			return true;
		else if (num[i] < ans[i]) return false;
	}
	return false;
}

void dfs(int s, int e, int flag1, int flag2, int flag3) {
	if (s > e) {
		if (flag1 == 0 && flag2) return;
		if (check()) {
			for (int i = 0; i < n; i++)
				ans[i] = num[i];
		}
		return;
	}
	int end = A[s] - '0';
	if (flag1) end = 9;
	for (int i = end; i >= 0; i--) {
		if (flag1 == 0 && i < end) flag1 = 1;
		if (!flag3 && i == 0) continue;
		num[s] = i;
		if (!judge(s)) break;
		if (e != n - 1 && num[e + 1] == i)
			dfs(s + 1, e, flag1, flag2, 1);
		for (int j = e; j >= s; j--) {
			num[j] = i;
			if (num[j] > A[j] - '0') flag2 = 1;
			if (num[j] < A[j] - '0') flag2 = 0;
			dfs(s + 1, j - 1, flag1, flag2, 1);
		}
	}
	if (!judge(s)) return;
	if (!flag3) {
		num[s] = 0;
		dfs(s + 1, e, flag1, flag2, flag3);
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%s", A);
		n = strlen(A);
		for (int i = 0; i < n; i++)
			ans[i] = 0;
		dfs(0, n - 1, 0, 1, 0);
		int s = 0;
		while (s < n - 1 && ans[s] == 0) {s++;}
		for (int i = s; i < n; i++)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}
