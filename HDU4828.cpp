#include <stdio.h>
#include <string.h>

const int N = 1000005;
const long long MOD = 1000000007;

long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a == 0 && b == 0) return -1;
    if(b == 0){x = 1; y = 0; return a;}
    long long d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long mod_reverse(long long a, long long n)
{
    long long x,y;
    long long d = extend_gcd(a, n, x, y);
    if(d == 1) return (x % n + n) % n;
    else return -1;
}

int t, n;
long long Catalan[N];


int main() {
    Catalan[1] = Catalan[2] = 1;
    for (int i = 3; i < N; i++) {
	long long tmp = mod_reverse((long long) i, MOD);
	Catalan[i] = Catalan[i - 1] * (4 * i - 6) % MOD * tmp % MOD;
    }
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	printf("Case #%d:\n", ++cas);
	printf("%lld\n", Catalan[n + 1]);

    }
    return 0;
}
