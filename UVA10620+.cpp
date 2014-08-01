#include <stdio.h>
#include <string.h>

long long s, x, y, dx, dy;

bool judge(long long x, long long y) {
    return (x % s && y % s && (x / s + y / s) % 2);
}

int main() {
    while (~scanf("%lld%lld%lld%lld%lld", &s, &x, &y, &dx, &dy) && s) {
	int i;
	for (i = 0; i < 2 * s; i++) {
	     if (judge(x, y)) {
		 printf("After %d jumps the flea lands at (%lld, %lld).\n",i,x,y);
		 break;
	     }
	     x += dx; y += dy;
	}
	if (i == 2 * s) printf("The flea cannot escape from black squares.\n");
    }
    return 0;
}
