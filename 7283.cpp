#include <cstdio>
#include <cstring>

const int N = 2100005;

int t, mi[10];
bool hash[N];
char str[N];

void bui(int len) {
    int n = strlen(str);
    int pre = 0, s = 0;
    for (int i = 0; i < n; i++) {
	s = s * 8 + str[i] - 'A';
	if (i - pre == len) {
	    hash[s] = true;
	    s %= mi[len];
	    pre++;
	}
    }
}

bool find(int now, int sum, int len) {
    if (now == len) {
	if (hash[sum]) return false;
	char ans[10];
        int an = 0;
	for (int i = 0; i < len; i++) {
	    ans[an++] = sum % 8 + 'A';
	    sum /= 8;
	}
	for (int i = an - 1; i >= 0; i--)
	    printf("%c", ans[i]);
	printf("\n");
	return true;
    }
    for (int i = 0; i < 8; i++)
	if (find(now + 1, sum * 8 + i, len)) return true;
    return false;
}

void build() {
    for (int i = 0; i < 7; i++) {
	memset(hash, false, sizeof(hash));
	bui(i);
	if (find(0, 0, i + 1)) return;
    }
}

int main() {
    mi[0] = 1;
    for (int i = 1; i < 8; i++) mi[i] = mi[i - 1] * 8;
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	build();
    }
    return 0;
}
