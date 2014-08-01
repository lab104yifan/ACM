#include <cstdio>
#include <cstring>

const int N = 1005;
int t, n, col, red[N], black[N];

int main() {
    scanf("%d", &t);
    while (t--) {
	memset(red, 0, sizeof(red));
	memset(black, 0, sizeof(black));
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
	    for (int j = 0; j < n - 1 - i; j++) {
		scanf("%d", &col);
		if (col) {
		    red[i]++;
		    red[i + j + 1]++;
		}
		else {
		    black[i]++;
		    black[i + j + 1]++;
		}
	    }
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
	    sum += black[i] * red[i];
	sum /= 2;
	printf("%d\n", n * (n - 1) * (n - 2) / 6 - sum);
    }
    return 0;
}
