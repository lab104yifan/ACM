#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int t, n, m, hash[1005];
char str[205];

int A[15][15], inv[11];

void build() {
    n = 0, m = 0;
    int flag = 1;
    memset(hash, -1, sizeof(hash));
    memset(A, 0, sizeof(A));
    int len = strlen(str), i = 0;
    while (i <= len) {
	if (str[i] >= 'A' && str[i] <= 'Z') {
	    int idx = str[i] - 'A' + 1;
	    i++;
	    if (str[i] >= 'a' && str[i] <= 'z') {
		idx = idx * 26 + str[i] - 'a' + 1;
		i++;
	    }
	    if (hash[idx] == -1) 
		hash[idx] = n++;
	    if (str[i] >= '0' && str[i] <= '9') {
		A[hash[idx]][m] += ((A[hash[idx]][m] + flag * (str[i] - '0')) % 11 + 11) % 11;
		i++;
	    }
	    else {
		A[hash[idx]][m] = ((A[hash[idx]][m] + flag) % 11 + 11) % 11;
	    }
	}
	if (str[i] == '=') flag = -1;
	if (str[i] == '+' || str[i] == '=' || str[i] == '\0') {
	    i++; m++;
	}
    }
}

bool gauss() {
    int i = 0, j = 0;
    while (i < n && j < m) {
	int r;
	for (r = i; r < n; r++)
	    if (A[r][j]) break;
	if (r == n) {
	    j++;
	    continue;
	}
	for (int k = j; k <= m; k++) swap(A[i][k], A[r][k]);
	for (int k = 0; k < n; k++) {
	    if (i == k) continue;
	    if (A[k][j]) {
		int tmp = A[k][j] * inv[A[i][j]] % 11;
		for (int x = j; x <= m; x++)
		    A[k][x] = ((A[k][x] - tmp * A[i][x]) % 11 + 11) % 11;
	    }
	}
	j++; i++;
    }
    for (int k = i; k < n; k++)
	if (A[i][k]) return false;
    for (int i = m - 1; i >= 0; i--) {
	if (A[i][i] == 0) {
	    A[i][i] = A[i][m] = 1;
	    for (int j = 0; j < i; j++) {
		A[j][m] = ((A[j][m] - A[j][i]) % 11 + 11) % 11;
		A[j][i] = 0;
	    }
	}
    }
    for (int i = 0; i < m; i++)
	if (A[i][m] == 0) return false;
    for (int i = 0; i < m; i++)
	printf("%d%c", A[i][m] * inv[A[i][i]] % 11, i == m - 1 ? '\n' : ' ');
    return true;
}

void getinv() {
    for (int i = 0; i < 11; i++) {
	int ans = 1;
	for (int j = 0; j < 9; j++)
	    ans = ans * i % 11;
	inv[i] = ans;
    }
}

int main() {
    getinv();
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	build();
	if (!gauss()) printf("IMPOSSIBLE\n");
    }
    return 0;
}
