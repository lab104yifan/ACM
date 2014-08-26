#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int n;

void print(int n) {
    if (n == 3) {
	printf("3 1 2");
	return;
    }
    if (n % 2) {
	int len = (n - 3) / 2;
	printf("%d %d", n, n - len);
	for (int i = n - 1; i > n - len; i--)
	    printf(" %d %d", i, i - len);
	printf(" 3 1 2");
    }
    else {
	int len = n / 2;
	printf("%d %d", n, n - len);
	for (int i = n - 1; i > n - len; i--)
	    printf(" %d %d", i, i - len);
    }
}

void print2(int n) {
    print(n - 2);
    printf(" %d %d", n - 1, n);
}

void solve() {
    if (n == 1) {
	printf("1 1\n1\n1\n");
	return;
    }
    if (n == 2) {
	printf("1 1\n1 2\n2 1\n");
	return;
    }
    if (n == 3) {
	printf("0 2\n3 1 2\n1 2 3\n");
	return;
    }
    if (n % 2 == 0) {
	if (n / 2 % 2) {
	    printf("1 %d\n", n - 1);
	    print2(n); printf("\n");
	    print2(n - 1);
	    printf(" %d\n", n);
	}
	else {
	    printf("0 %d\n", n);
	    print(n); printf("\n");
	    print(n - 1); printf(" %d\n", n);
	}
    }
    else {
	if ((n + 1) / 2 % 2) {
	    printf("1 %d\n", n);
	    print(n - 2); printf(" %d %d\n", n - 1, n);
	    print(n - 1); printf(" %d\n", n);
	}
	else {
	    printf("0 %d\n", n - 1);
	    print(n); printf("\n");
	    print2(n - 1); printf(" %d\n", n);
	}
    }
}

int main() {
    while (~scanf("%d", &n)) {
	solve();
    }
    return 0;
}
