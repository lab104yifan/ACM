#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 15;
const int MOD = 10000007;

int n, m;

struct mat {
	ll v[N][N];
	mat() {memset(v, 0, sizeof(v));}
	mat operator * (mat c) {
		mat ans;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					ans.v[i][j] = (ans.v[i][j] + v[i][k] * c.v[k][j] % MOD) % MOD;
		return ans;
	}
};

mat pow_mod(mat x, int k) {
	mat ans;
	for (int i = 0; i < n; i++)
		ans.v[i][i] = 1;
	while (k) {
		if (k&1) ans = ans * x;
		x = x * x;
		k >>= 1;
	}
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		mat A;
		A.v[0][0] = 1;
		A.v[1][0] = 1; A.v[1][1] = 10;
		n += 2;
		for (int i = 2; i < n; i++) {
			for (int j = 1; j <= i; j++)
				A.v[i][j] = 1;
		}
		A = pow_mod(A, m);
		ll ans = 0;
		ll tmp[N];
		tmp[0] = 3; tmp[1] = 233;
		for (int i = 2; i < n; i++)
			scanf("%I64d", &tmp[i]);
		for (int i = 0; i < n; i++)
			ans = (ans + tmp[i] * A.v[n - 1][i] % MOD) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}
