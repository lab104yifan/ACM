#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main() {
	printf("50000\n");
	for (int i = 0; i < 50000; i++) {
		printf("%d%c", rand() % 10000000 + 1, i == 50000 - 1 ? '\n' : ' ');
	}
	return 0;
}
