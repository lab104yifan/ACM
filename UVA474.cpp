#include <cstdio>
#include <cstring>

const int N = 1000001;
const double eps = 1e-9;
int n;
struct Ans {
    double a;
    int b;
} ans[N];

void build() {
    ans[1].a = 5; ans[1].b = 1;
    for (int i = 2; i < N; i++) {
	ans[i].a = ans[i - 1].a * 0.5;
	ans[i].b = ans[i - 1].b;
	if (ans[i].a < 1.0) {
	    ans[i].a *= 10;
	    ans[i].b++;
	}
    }
}

int main() {
    build();
    while (~scanf("%d", &n)) {
	printf("2^-%d = %.3lfe-%d\n", n, ans[n].a, ans[n].b);
    }
    return 0;
}
