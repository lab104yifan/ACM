#include <cstdio>
#include <cstring>

int main() {
    for (int i = 1; i <= 1000; i++) {
	int ans = 0;
	for (int b = 2; b < i; b++) {
	    int num = i;
	    int flag = 1;
	    while (num) {
		if (num % b < 3 || num % b > 6) {
		    flag = 0;
		    break;
		}
		num /= b;
	    }
	    if (flag) {
		ans++;
	    }
	}
	printf("%d: %d\n", i, ans);
    }
    return 0;
}
