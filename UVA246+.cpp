#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
using namespace std;

int num, zero[8];
vector<deque<int> > piple;
set<vector<deque<int> > > vis;

void init() {
    vis.clear();
    piple.clear();
    memset(zero, 0, sizeof(zero));
    for (int i = 0; i < 8; i++)
	piple.push_back(deque<int>());
    piple[7].push_back(num);
    for (int i = 0; i < 51; i++) {
	scanf("%d", &num);
	piple[7].push_back(num);
    }
    for (int i = 0; i < 7; i++) {
	int now = piple[7].front();
	piple[7].pop_front();
	piple[i].push_back(now);
    }
}

bool can(int x) {
    return (x == 10 || x == 20 || x == 30);
}

bool tra1(int i) {
    int top1 = piple[i].front();
    piple[i].pop_front();
    int sum = top1 + piple[i].front() + piple[i].back();
    if (can(sum)) { 
	piple[7].push_back(top1);
	piple[7].push_back(piple[i].front());
	piple[7].push_back(piple[i].back());
	piple[i].pop_front();
	piple[i].pop_back();
	return true;
    }
    piple[i].push_front(top1);
    return false;
}

bool tra2(int i) {
    int back1 = piple[i].back();
    piple[i].pop_back();
    int sum = back1 + piple[i].front() + piple[i].back();
    if (can(sum)) { 
	piple[7].push_back(piple[i].front());
	piple[7].push_back(piple[i].back());
	piple[7].push_back(back1);
	piple[i].pop_front();
	piple[i].pop_back();
	return true;
    }
    piple[i].push_back(back1);
    return false;
}

bool tra3(int i) {
    int back1 = piple[i].back();
    piple[i].pop_back();
    int back2 = piple[i].back();
    piple[i].pop_back();
    int sum = back1 + back2 + piple[i].back();
    if (can(sum)) { 
	piple[7].push_back(piple[i].back());
	piple[7].push_back(back2);
	piple[7].push_back(back1);
	piple[i].pop_back();
	return true;
    }
    piple[i].push_back(back2);
    piple[i].push_back(back1);
    return false;
}

bool tra(int i) {
    if (piple[i].size() < 3) return false;
    if (tra1(i)) return true;
    if (tra2(i)) return true;
    if (tra3(i)) return true;
    return false;
}

void solve() {
    int i = 0;
    for (int t = 8; ; t++) {
	int now = piple[7].front();
	piple[7].pop_front();
	piple[i].push_back(now);
	while (tra(i));
	if (piple[i].size() == 0)
	    zero[i] = 1;
	i = (i + 1) % 7;
	if (vis.find(piple) != vis.end()) {
	    printf("Draw: %d\n", t);
	    return;
	}
	vis.insert(piple);
	if (piple[7].size() == 0) {
	    printf("Loss: %d\n", t);
	    return;
	}
	if (piple[7].size() == 52) {
	    printf("Win : %d\n", t);
	    return;
	}
	while (zero[i]) i = (i + 1) % 7;
    }
}

int main() {
    while (~scanf("%d", &num) && num) {
	init();
	solve();
    }
    return 0;
}
