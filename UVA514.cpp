#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int N = 1005;

int n, a[N];

int main() {
    while (~scanf("%d", &n) && n) {
	while (~scanf("%d", &a[0]) && a[0]) {
	    for (int i = 1; i < n; i++)
		scanf("%d", &a[i]);
	    int now = 0;
	    stack<int> s;
	    for (int i = 1; i <= n; i++) {
		s.push(i);
		if (i > a[now]) break;
		while (!s.empty() && s.top() == a[now]) {
		    s.pop();
		    now++;
		}
	    }
	    if (s.empty()) printf("Yes\n");
	    else printf("No\n");
	}
	printf("\n");
    }
    return 0;
}
