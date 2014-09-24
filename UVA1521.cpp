#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10005;

int vis[N], prime[N], pn = 0;

void getprime() {
	for (int i = 2; i < N; i++) {
		if (vis[i]) continue;
		prime[pn++] = i;
		for (int j = i * i; j < N; j += i)
			vis[j] = 1;
	}
}

int n;

int main() {
	getprime();
	while (~scanf("%d", &n)) {
		int ans = 0, head = 0, rear = pn - 1;
		while (prime[rear] > n) rear--;
		while (head <= rear) {
			int p = prime[rear];
			while (p * prime[head] <= n) p *= prime[head++];
			ans++;
			rear--;
		}
		printf("%d\n", ans);
	}
	return 0;
}
