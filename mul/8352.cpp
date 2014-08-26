#include <cstdio>
#include <cstring>
#include <string>
#include <bitset>
using namespace std;

const int N = 805;
int n, num;
bitset<800> row[N][2], col[N][2];

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 0; i < n; i++) {
	    row[i][0].reset();
	    row[i][1].reset();
	    col[i][0].reset();
	    col[i][1].reset();
	    for (int j = 0; j < n; j++) {
		scanf("%d", &num);
		if (num % 3 == 1)
		    row[i][0].set(j, 1);
		if (num % 3 == 2)
		    row[i][1].set(j, 1);
	    }
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		scanf("%d", &num);
		if (num % 3 == 1)
		    col[j][0].set(i, 1);
		if (num % 3 == 2)
		    col[j][1].set(i, 1);
	    }
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		int ans = 0;
		ans += (row[i][0]&col[j][0]).count();
		ans += 2 * (row[i][1]&col[j][0]).count() + 2 * (row[i][0]&col[j][1]).count();
		ans += (row[i][1]&col[j][1]).count();
		printf("%d%c", ans % 3, j == n - 1 ? '\n' : ' ');
	    }
	}
    }
    return 0;
}
