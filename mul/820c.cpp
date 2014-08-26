#include <cstdio>
#include <cstring>

const int N = 1005;
const int M = 10;
int n, m;

int A[N][M], B[M][N], C[M][M], CC[N][N];
int ans[M][M];

void tra() {
    memset(CC, 0, sizeof(CC));
    for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
        CC[i][j] = 0;
        for (int k = 0; k < m; k++) {
        CC[i][j] = (CC[i][j] + C[i][k] * C[k][j]) % 6;
        }
    }
    }
    for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++)
        C[i][j] = CC[i][j];
}

void mul() {
    for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
        CC[i][j] = 0;
        for (int k = 0; k < m; k++) {
        CC[i][j] = (CC[i][j] + ans[i][k] * C[k][j]) % 6;
        }
    }
    }
    for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++)
        ans[i][j] = CC[i][j];
}

void pow_mod(int k) {
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < m; i++)
    ans[i][i] = 1;
    while (k) {
    if (k&1) mul();
    tra();
    k >>= 1;
    }
}

void init() {
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%d", &A[i][j]);
    for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
        scanf("%d", &B[i][j]);
}

int solve() {
    for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
        C[i][j] = 0;
        for (int k = 0; k < n; k++) {
        C[i][j] = (C[i][j] + B[i][k] * A[k][j]) % 6;
        }
    }
    }

    pow_mod(n * n - 1);

    for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
        C[i][j] = ans[i][j];
    }
    }

    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        CC[i][j] = 0;
        for (int k = 0; k < m; k++) {
        CC[i][j] = (CC[i][j] + A[i][k] * C[k][j]) % 6;
        }
    }
    }
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        A[i][j] = CC[i][j];
    int ans = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int k = 0; k < m; k++) {
        sum = (sum + A[i][k] * B[k][j]) % 6;
        }
        ans += sum;
    }
    }
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m) && n || m) {
    init();
    printf("%d\n", solve());
    }
    return 0;
}
