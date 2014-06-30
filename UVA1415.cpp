#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 20005;
int t, a, b, prime[N], pn = 0, vis[N];

bool judge() {
    if (a == 0) {
	int m = sqrt(m);
	for (int i = 0; i <= m; i++) {
	    double t = sqrt((b - i * i) * 1.0 / 2);
	    if (ceil(t) == floor(t)) return true;
	}
	return false;
    }
    int tmp = a * a + 2 * b * b;
    for (int i = 0; i < pn && prime[i] < tmp; i++)
	if (tmp % prime[i] == 0) return false;
    return true;
}

int main() {
    vis[1] = 1;
    for (int i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (int j = i * i; j < N; j += i) {
	    vis[j] = 1;
	}
    }
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &a, &b);
	printf("%s\n", judge()?"Yes":"No");
    }
    return 0;
}
