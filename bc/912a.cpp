#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int t, a, b, c;

int main() {
	scanf("%d", &t);
	while (t--) {
		int ans = 0;
		scanf("%d%d%d", &a, &b, &c);
		for (int i = 1; a * i < c; i++) {
			int bs = c - a * i;
			if (bs % b) continue;
			int tmp = bs / b;
			if (tmp <= 0) continue;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
