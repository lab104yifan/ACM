#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef int ll;

const int N = 20005;

int t, n, v, x;
char str[N];
map<int, int> hash;

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	v = -1;
	n = strlen(str);
	for (int i = 0; i < n; i++) {
	    if (str[i] == '?') {
		v = i;
		break;
	    }
	}
	int ans = 0;
	if (v == -1) {
	    x = 0;
	    hash.clear();
	    hash[0]++;
	    for (int i = 0; i < n; i++) {
		x ^= (1<<(str[i] - 'a'));
		ans += hash[x];
		hash[x]++;
	    }
	    printf("%d\n", ans);
	    continue;
	}
	else {
	    hash.clear();
	    ans = 0;
	    x = 0;
	    hash[0]++;
	    for (int i = 0; i < v; i++) {
		x ^= (1<<(str[i] - 'a'));
		ans += hash[x];
		hash[x]++;
	    }
	    hash.clear();
	    x = 0;
	    hash[0]++;
	    for (int i = v + 1; i < n; i++) {
		x ^= (1<<(str[i] - 'a'));
		ans += hash[x];
		hash[x]++;
	    }
	    hash.clear();
	    x = 0;
	    hash[0]++;
	    for (int i = v + 1; i < n; i++) {
		x ^= (1<<(str[i] - 'a'));
		hash[x]++;
	    }
	    x = 0;
	    if (hash.count(x))
		ans += hash[x];
	    for (int j = 0; j < 26; j++) {
		if (hash.count(x^(1<<j)))
		    ans += hash[x^(1<<j)];
	    }
	    for (int i = v - 1; i >= 0; i--) {
		x ^= (1<<(str[i] - 'a'));
		if (hash.count(x))
		    ans += hash[x];
		for (int j = 0; j < 26; j++) {
		    if (hash.count(x^(1<<j))) {
			ans += hash[x^(1<<j)];
		    }
		}
	    }
	}
	printf("%d\n", ans);
    }
    return 0;
}
