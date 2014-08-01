#include <cstdio>
#include <cstring>
#include <cmath>

long long k, p;

int main() {
    while (~scanf("%lld%lld", &k, &p)) {
	if (k / (p - 1) % 2) printf("YES\n");
	else printf("NO\n");
    }
    return 0;
}
