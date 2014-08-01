#include <cstdio>
#include <cstring>

typedef long long ll;
int cnt, n;
ll ans;
char c;

int main() {
    while (~scanf("%d%*c", &n)) {
	cnt = 0;
	ans = 1;
	while (cnt < n) {
	    c = getchar();
	    while (c == '\n') {
		cnt++;
		if (cnt == n) break;
		c = getchar();
	    }
	    if (c == '{') {
		ll tmp = 1;
		while (c != '}') {
		    c = getchar();
		    while (c == '\n') {
			cnt++;
			c = getchar();
		    }
		    if (c == '|')
			tmp++;
		}
		if (ans <= 100000)
		    ans *= tmp;
	    }
	    else if (c == '$') {
		ll tmp = 1;
		c = getchar();
		while (c == '\n') {
		    cnt++;
		    c = getchar();
		}
		while (c != '$') {
		    if (c == ' ') {
			tmp++;
		    }
		    else {
			if (ans <= 100000)
			    ans *= tmp;
			tmp = 1;
		    }
		    c = getchar();
		    while (c == '\n') {
			cnt++;
			c = getchar();
		    }
		}
		if (ans <= 100000)
		    ans *= tmp;
	    }
	}
	if (ans <= 100000) printf("%lld\n", ans);
	else printf("doge\n");
    }
    return 0;
}
