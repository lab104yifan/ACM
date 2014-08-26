#include <cstdio>
#include <cstring>

typedef unsigned long long ll;
const int N = 155;
const ll MOD = (1ULL<<32);

int n;

struct Mat {
    ll v[N][N];

    Mat() {
	memset(v, 0, sizeof(v));
    }

    void init() {
	memset(v, 0, sizeof(v));
    }

    void init_one() {
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++)
	    v[i][i] = 1;
    }

    Mat operator * (Mat c) {
	Mat ans;
	for (int k = 0; k < n; k++) {
	    for (int i = 0; i < n; i++) {
		if (!v[i][k]) continue;
		for (int j = 0; j < n; j++)
		    ans.v[i][j] = (ans.v[i][j] + v[i][k] * c.v[k][j] % MOD) % MOD;
	    }
	}
	return ans;
    }
} B;

Mat pow_mod(Mat x, int k) {
    Mat ans;
    ans.init_one();
    while (k) {
	if (k&1) ans = ans * x;
	x = x * x;
	k >>= 1;
    }
    return ans;
}

ll dp[40][10], A[N];
int t, b, s, m;

void init() {
    scanf("%d%d", &b, &s);
    m = (b - 1) * (b - 1);
    n = m  * b;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < b; i++)
	dp[0][i] = 1;
    for (int i = 1; i <= m; i++) {
	for (int j = 0; j < b; j++) {
	    for (int k = 0; k < b; k++) {
		if (k == j) continue;
		int tmp = (k - j) * (k - j);
		if (i - tmp < 0) continue;
		dp[i][j] = (dp[i][j] + dp[i - tmp][k]) % MOD;
	    }
	}
    }
}

void build() {
    B.init();
    for (int i = b; i < n; i++)
	B.v[i][i - b] = 1;
    for (int i = 1; i <= m; i++) {
	for (int j = 0; j < b; j++) {
	    for (int k = 0; k < b; k++) {
		if (j == k) continue;
		if (i + (k - j) * (k - j) == m + 1) {
		    B.v[(i - 1) * b + j][n - b + k] = 1;
		}
	    }
	}
    }
}

ll solve() {
    ll ans = 0;
    if (s <= m) {
	for (int i = 1; i < b; i++)
	    ans = (ans + dp[s][i]) % MOD;
	return ans;
    }
    for (int i = 1; i <= m; i++) {
	for (int j = 0; j < b; j++)
	    A[(i - 1) * b + j] = dp[i][j];
    }
    build();
    B = pow_mod(B, s - m);
    for (int i = n - b + 1; i < n; i++) {
	for (int j = 0; j < n; j++)
	    ans = (ans + A[j] * B.v[j][i] % MOD) % MOD;
    }
    return ans;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	init();
	printf("Case %d: %llu\n", ++cas, solve());
    }
    return 0;
}
