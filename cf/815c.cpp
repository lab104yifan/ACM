#include <cstdio>
#include <cstring>

int n, k, d, s[10005];

bool judge() {
    int num = n / k;
    int len = num + (n % k != 0);
    if (len > d) return false;
    int sn = 0;
    for (int i = 0; i < len; i++) {
	for (int j = 0; j < k; j++) {
	    s[sn++] = j + 1;
	    if (sn == n) break;
	}
    }
    for (int i = 0; i < d; i++) {
	for (int j = 0; j < n; j++)
	    printf("%d%c", s[j], j == n - 1 ? '\n' : ' ');
	int len = i * k;
	int sb = i + 1;
	for (int j = 0; j < k; j++) {
	    s[len] = (s[len] + sb);
	    if (s[len] > k) s[len] %= k;
	    len++;
	}
    }
    return true;
}

int main() {
    scanf("%d%d%d", &n, &k, &d);
    if (!judge()) printf("-1\n");
    return 0;
}
