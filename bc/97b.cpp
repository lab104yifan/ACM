#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

typedef long long ll;

ll n, m;

struct mat {
	ll v[2][2];
	mat() {memset(v, 0, sizeof(v));}
	mat operator * (mat c) {
		mat ans;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					ans.v[i][j] = (ans.v[i][j] + v[i][k] * c.v[k][j]) % m;
				}
			}
		}
		return ans;
	}
};

mat pow_mod(mat A, ll k) {
	mat ans;
	for (int i = 0; i < 2; i++) ans.v[i][i] = 1;
	while (k) {
		if (k&1) ans = ans * A;
		A = A * A;
		k >>= 1;
	}
	return ans;
}

int main() {
	while (cin >> n >> m) {
		mat A;
		A.v[0][0] = 4; A.v[0][1] = 1;
		A.v[1][0] = 0; A.v[1][1] = 1;
		A = pow_mod(A, (n + 1) / 2);
		ll ans = A.v[0][1];
		ans %= m;
		if (n % 2 == 0) ans = ans * 2 % m;
		cout << ans << endl;
	}
	return 0;
}
