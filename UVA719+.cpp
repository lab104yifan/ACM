#include <cstdio>
#include <cstring>

const int N = 20005;
typedef unsigned long long ull;

const ull X = 123;

int t, n;
ull H[N], Hp[N];
char str[N];

void gethash() {
    H[n] = 0;
    for (int i = n - 1; i >= 0; i--)
	H[i] = H[i + 1] * X + str[i] - 'a';
}

int solve() {
    for (int i = 0; i < n; i++) {
    
    }
}

int main() {
    Hp[0] = 1;
    for (int i = 1; i < N; i++)
	Hp[i] = Hp[i - 1] * X;
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++)
	    str[i + n] = str[i];
	n *= 2;
	gethash();
	n /= 2;
	printf("%d\n", solve());
    }
    return 0;
}
