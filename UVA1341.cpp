#include <stdio.h>
#include <string.h>

const int INF = 0x3f3f3f3f;
const int N = 66666;
int n, num[2], vis[N], ans, save[N];
struct Queue {
    int mod, pre, num, len;
    Queue(){}
    Queue(int mod, int pre, int num, int len) {
	this->mod = mod;
	this->pre = pre;
	this->num = num;
	this->len = len;
    }
} q[N * 2];

void out(int now, int d) {
    if (now == -1) return;
    out(q[now].pre, d - 1);
    save[d] = q[now].num;
}

int judge(int now, int d) {
    if (now == -1) return 0;
    int tmp = judge(q[now].pre, d - 1);
    if (tmp != 0) return tmp;
    if (save[d] == q[now].num) return 0;
    else if (q[now].num < save[d]) return -1;
    else return 1;
}

void bfs() {
    int head = 0, tail = 0;
    if (num[0] != 0) {
	q[tail++] = Queue(num[0] % n, -1, num[0], 1);
	vis[num[0] % n] = 1;
    }
    if (num[1] != -1 && num[1] != 0) {
	q[tail++] = Queue(num[1] % n, -1, num[1], 1);
	vis[num[1] % n] = 1;
    }
    while (head < tail) {
	Queue now = q[head];
	if (now.len > ans) return;
	if (now.mod == 0) {
	    if (now.len <= ans) {
		if (now.len != ans || judge(head, ans - 1) < 0) {
		    ans = now.len;
		    out(head, ans - 1);
		}
	    }
	}
	Queue next;
	for (int i = 0; i < 2; i++) {
	    if (num[i] == -1) continue;
	    next = Queue((now.mod * 10 + num[i]) % n, head, num[i], now.len + 1);
	    if (vis[next.mod]) continue;
	    vis[next.mod] = 1;
	    q[tail++] = next;
	}
	head++;
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
	ans = INF;
	for (int i = 1; i < 10; i++) {
	    num[0] = i; num[1] = -1;
	    memset(vis, 0, sizeof(vis));
	    bfs();
	}
	if (ans == INF) {
	    for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
		    num[0] = i; num[1] = j;
		    memset(vis, 0, sizeof(vis));
		    bfs();
		}
	    }
	}
	for (int i = 0; i < ans; i++)
	    printf("%d", save[i]);
	printf("\n");
    }
    return 0;
}
