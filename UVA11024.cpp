#include <cstdio>
#include <cstring>

int t, s[2][2], p[2][2];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 2; i++)
				scanf("%d", &s[k][i]);
			for (int i = 0; i < 2; i++)
				scanf("%d", &p[k][i]);
		}
		int P = p[0][0];
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				P = gcd(P, p[i][j]);
		int sum = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (i == j) sum -= P - s[i][j];
				else sum += P - s[i][j];
			}
		}
		printf("%s\n", sum % P == 0 ? "Yes" : "No");
	}
	return 0;
}
