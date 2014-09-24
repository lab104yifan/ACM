#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long ll;

int t, a, b, k, s;
vector<int> save;

int pow_mod(int x, int k, int mod) {
	int ans = 1;
	while (k) {
		if (k&1) ans = (ll)ans * x % mod;
		x = (ll)x * x % mod;
		k >>= 1;
	}
	return ans;
}

bool mlrb(int x) {
	if (x == 1 || x == 0) return false;
	for (int i = 0; i < 15; i++) {
		int a = rand() % (x - 1) + 1;
		if (pow_mod(a, x - 1, x) != 1) return false;
	}
	return true;
}

const int N = 10000005;
const int M = 100005;

int prime[M], pn = 0, vis[N];

void getprime() {
	for (int i = 2; i < M; i++) {
		if (vis[i]) continue;
		prime[pn++] = i;
		for (ll j = (ll)i * i; j < M; j += i)
			vis[j] = 1;
	}
}

int main() {
	getprime();
	int now = 0;
	for (int i = 0; i < M; i++) {
		if (prime[now] == i) {
			now++;
			continue;
		}
		vis[i] = 0;
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d%d", &a, &b, &k, &s);
		save.clear();
		for (int i = 0; i < pn; i++) {
			if (prime[i] > b) break;
			int tmp = a / prime[i] * prime[i];
			if (tmp < a) tmp += prime[i];
			if (prime[i] == tmp) tmp += prime[i];
			for (int j = tmp; j <= b; j += prime[i]) {
				vis[j - a] = 1;
			}
		}
		for (int i = a; i <= b; i++) {
			if (vis[i - a]) continue;
			save.push_back(i);
		}
		/*for (int i = a; i <= b; i++) {
			if (mlrb(i))
				save.push_back(i);
		}*/
		int n = save.size();
		if (n == 0) {
			printf("0\n");
			continue;
		}
		int pre = 0;
		int cnt = 0;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			cnt++;
			if (cnt >= k || save[i] - save[pre] >= s) {
				if (cnt == k && save[i] - save[pre] == s) ans++;
				while (cnt >= k || save[i] - save[pre] >= s) {
					pre++;
					cnt--;
				}
			}
		}
		printf("%d\n", ans);
		int now = 0;
		for (int i = a; i <= b; i++) {
			if (i == save[now]) {
				now++;
				continue;
			}
			vis[i - a] = 0;
		}
	}
	return 0;
}
