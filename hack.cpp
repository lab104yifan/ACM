#include <cstdio>

int main() {
    printf("100000 100000\n");
    for (int i = 1; i < 100000; i++)
	printf("%d ", i);
    printf("100000\n");
    for (int i = 0; i < 100000; i++)
	printf("%d\n", 1);
    return 0;
}
