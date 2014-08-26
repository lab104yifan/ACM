#include <cstdio>
#include <cstring>


char str[260];
int hash[555555], save[260], sn;

bool check() {
    sn = 0;
    int n = strlen(str);
    for (int i = 1; i < n - 1; i++) {
	if (str[i - 1] == str[i + 1]) {
	    int num = (str[i - 1] - 'A' + 1) * 27 * 27 + (str[i] - 'A' + 1) * 27 + str[i + 1] - 'A' + 1;
	    if (!hash[num]) {
		hash[num] = 1;
		save[sn++] = num;
	    }
	    continue;
	}
	if (str[i] == str[i + 1] && str[i - 1] == str[i + 2]) {
	    int num = (str[i - 1] - 'A' + 1) * 27 * 27 * 27 + (str[i] - 'A' + 1) * 27 * 27 + (str[i + 1] - 'A' + 1) * 27 + str[i + 2] - 'A' + 1;
	    if (!hash[num]) {
		hash[num] = 1;
		save[sn++] = num;
	    }
	}
    }
    for (int i = 0; i < sn; i++)
	hash[save[i]] = 0;
    return sn >= 2;
}

int main() {
    while (~scanf("%s", str))
	if (check())
	    printf("%s\n", str);
    return 0;
}
