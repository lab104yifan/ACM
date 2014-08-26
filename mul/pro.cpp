#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

int mi[100];
int main() {
    mi[0] = 1;
    for (int i = 1; i < 20; i++)
	mi[i] = mi[i - 1] * 2;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
	int n = rand() % 100 + 1;
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
	    int tmp = rand() % 25;
	    if (tmp >= 12) {
		tmp = rand() % 2049;
		printf("%d", tmp);
	    }
	    else printf("%d", mi[tmp]);
	    printf("%c", i == n - 1 ? '\n' : ' ');
	}
    }
    printf("0\n");
    return 0;
}
