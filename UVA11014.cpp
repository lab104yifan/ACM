#include <stdio.h>
#include <string.h>

const int N = 200005;
long long n;
long long prime[N];
int pn = 0, vis[N];

long long pow3(long long num) {
    return num * num * num - 1;
}

int count(long long num) {
    int ans = 0;
    for (int i = 0; i < pn && prime[i] <= num; i++) {
	if (!vis[num]) {ans++; break;}
	if (num % prime[i] == 0) {
	    ans++;
	    num /= prime[i];
	    if (num % prime[i] == 0) return -1;
	}
    }
    return ans;
}

long long cal(long long num) {
    int t = count(num);
    if (t == -1) return 0;
    if (t&1) return -pow3((n / 2 / num) * 2 + 1);
    else return pow3((n / 2 / num) * 2 + 1);
}

long long solve() {
    long long ans = pow3(n + 1);
    for (long long i = 2; i <= n; i++)
	ans += cal(i);
    return ans;
}

int main() {
    vis[1] = 1;
    for (long long i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (long long j = i * i; j < N; j += i)
	    vis[j] = 1;
    }
    int cas = 0;
    while (~scanf("%lld", &n) && n) {
	printf("Crystal %d: %lld\n", ++cas, solve());	
    }
    return 0;
}
