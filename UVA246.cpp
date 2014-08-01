#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <set>
using namespace std;

queue<int> deck;
list<deque<int> > piple;
set<list<deque<int> > > vis;
int num;

void init() {
    vis.clear();
    piple.clear();
    while (!deck.empty()) deck.pop();
    deck.push(num);
    for (int i = 0; i < 51; i++) {
	scanf("%d", &num);
	deck.push(num);
    }
    for (int i = 0; i < 7; i++)
	piple.insert(piple.end(), deque<int>());
}

bool can(int x) {
    if (x == 10 || x == 20 || x == 30) return true;
    return false;
}

bool tra1(list<deque<int> >::iterator one) {
    int tmp = one->front();
    one->pop_front();
    int sum = one->front() + one->back() + tmp;
    if (can(sum)) {
	deck.push(tmp);
	deck.push(one->front());
	one->pop_front();
	deck.push(one->back());
	one->pop_back();
	return true;
    }
    one->push_front(tmp);
    return false;
}

bool tra2(list<deque<int> >::iterator one) {
    int tmp = one->back();
    one->pop_back();
    int sum = one->front() + one->back() + tmp;
    if (can(sum)) {
	deck.push(one->front());
	one->pop_front();
	deck.push(one->back());
	one->pop_back();
	deck.push(tmp);
	return true;
    }
    one->push_back(tmp);
    return false;
}

bool tra3(list<deque<int> >::iterator one) {
    int tmp1 = one->back();
    one->pop_back();
    int tmp2 = one->back();
    one->pop_back();
    int sum = one->back() + tmp1 + tmp2;
    if (can(sum)) {
	deck.push(one->back());
	deck.push(tmp2);
	deck.push(tmp1);
	one->pop_back();
	return true;
    }
    one->push_back(tmp2);
    one->push_back(tmp1);
    return false;
}

bool tra(list<deque<int> >::iterator one) {
    if (one->size() < 3) return false;
    if (tra1(one)) return true;
    if (tra2(one)) return true;
    if (tra3(one)) return true;
    return false;
}

void solve() {
    list<deque<int> >::iterator it = piple.begin();
    for (int t = 0; ; t++) {
	if (vis.find(piple) != vis.end()) {
	    printf("Draw: %d\n", t);
	    return;
	}
	vis.insert(piple);
	if (deck.size() == 0) {
	    printf("Win : %d\n", t);
	    return;
	}
	if (deck.empty()) {
	    printf("Loss: %d\n", t);
	    return;
	}
	int now = deck.front(); deck.pop();
	it->push_back(now);
	while (tra(it))
	if (it->size() == 0) {
	    it = piple.erase(it);
	}
	else it++;
	if (it == piple.end()) it = piple.begin();
    }
}

int main() {
    while (~scanf("%d", &num) && num) {
	init();
	solve();
    }
    return 0;
}
