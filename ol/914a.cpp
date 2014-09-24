#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

string str;

int main() {
	while (getline(cin, str)) {
		int n = str.length();
		for (int i = 0; i < n; i++) {
			if (i <= n - 6 && str[i] == 'i' && str[i + 1] == 'P' && str[i + 2] == 'h' && str[i + 3] == 'o' && str[i + 4] == 'n' && str[i + 5] == 'e') printf("MAI MAI MAI!\n");
			else if (i <= n - 5 && str[i] == 'A' && str[i + 1] == 'p' && str[i + 2] == 'p' && str[i + 3] == 'l' && str[i + 4] == 'e')
				printf("MAI MAI MAI!\n");
			else if (i <= n - 4 && str[i] == 'i' && str[i + 1] == 'P' && str[i + 2] == 'o' && str[i + 3] == 'd')
				printf("MAI MAI MAI!\n");
			else if (i <= n - 4 && str[i] == 'i' && str[i + 1] == 'P' && str[i + 2] == 'a' && str[i + 3] == 'd')
				printf("MAI MAI MAI!\n");
			else if (i <= n - 4 && str[i] == 'S' && str[i + 1] == 'o' && str[i + 2] == 'n' && str[i + 3] == 'y')
				printf("SONY DAFA IS GOOD!\n");
		}
	}
	return 0;
}
