#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1005;
int T, n, t, k, m;

struct Person {
    int t, p, num, ans;
} p[N];

int main() {
    scanf("%d", &T);
    while (T--) {
	scanf("%d%d%d%d", &n, &t, &k, &m);
	for (int i = 0; i < m; i++) {
	    int a, b;
	    scanf("%d:%d%d%d", &a, &b, &p[i].p, &p[i].num);
	    p[i].t = a * 60 + b;
	}
	int ti = p[0].t, i = 0;
	while (1) {
	    if (p[i].num == 0) {
		i++;
		if (i == m) break;
		continue;
	    }
	    if (i == m) break;
	    ti = max(ti, p[i].t);
	    int st = ti;
	    int pz = p[i].p;
	    int have = k;
	    while (have < p[i].num) {
		p[i].num -= have;
		ti += t;
	    }
	    have -= p[i].num;
	    p[i].num = 0;
	    st = ti;
	    ti += t;
	    p[i].ans = ti;
	    for (int j = i + 1; p[j].t <= st && j < m && have; j++) {
		if (p[j].p != pz) continue;
		if (p[j].num == 0) continue;
		if (p[j].num > have) {
		    p[j].num -= have;
		    have = 0;
		}
		else {
		    have -= p[j].num;
		    p[j].ans = ti;
		    p[j].num = 0;
		}
	    }
	}
	for (int i = 0; i < m; i++)
	    printf("%02d:%02d\n", p[i].ans / 60 % 24, p[i].ans % 60);
	if (T) printf("\n");
    }
    return 0;
}
