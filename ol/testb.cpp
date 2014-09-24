#include <cstdio>
#include <cstring>

int t;
int n, m;
const char out[10] = "aababb";

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &m, &n);
		printf("Case #%d: ", ++cas);
		if (m == 1) {
			for (int i = 0; i < n; i++)
				printf("a");
			printf("\n");
		} else if (m == 2) {
			if (n == 1) printf("a\n");
			else if (n == 2) printf("ab\n");
			else if (n == 3) printf("aab\n");
			else if (n == 4) printf("aabb\n");
			else if (n == 5) printf("aaaba\n");
			else if (n == 6) printf("aaabab\n");
			else if (n == 7) printf("aaababb\n");
			else if (n == 8) printf("aaababbb\n");
			else {
				n -= 2;
				printf("aa");
				int ci = n / 6;
				int yu = n % 6;
				for (int i = 0; i < ci; i++)
					printf("%s", out);
				if (yu <= 4) {
					for (int i = 0; i < yu; i++)
						printf("a");
				} else {
					for (int i = 0; i < yu; i++)
						printf("%c", out[i]);
				}
				printf("\n");
			}
		} 
		else {
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				printf("%c", 'a' + cnt);
				cnt = (cnt + 1) % 3;
			}
			printf("\n");
		}
	}
	return 0;
}
