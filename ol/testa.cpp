#include <cstdio>
#include <cstring>

int t;
char str[105];

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		printf("Case #%d: ", ++cas);
		if (strlen(str) < 4) printf("%snanodesu\n", str);
		else {
			int len = strlen(str);
			if (str[len - 1] == 'u' && str[len - 2] == 's' && str[len - 3] == 'e' && str[len - 4] == 'd') {
				for (int i = 0; i < len - 4; i++)
					printf("%c", str[i]);
				printf("nanodesu\n");
			} else {
				printf("%snanodesu\n", str);
			}
		}
	}
	return 0;
}
