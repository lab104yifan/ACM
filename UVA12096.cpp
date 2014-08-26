#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int t, n, hn;
char op[10];
stack<set<int> > st;
map<set<int>, int> hash;
set<int> s1, s2;
set<int>::iterator it;

void print() {
    printf("%d\n", (int)st.top().size());
}

void ad(set<int> s) {
    if (hash.count(s))
	return;
    hash[s] = hn++;
}

void pus() {
    set<int> s;
    ad(s);
    st.push(s);
    print();
}

void dup() {
    set<int> s = st.top();
    st.push(s);
    print();
}

void uni() {
    s1 = st.top(); st.pop();
    s2 = st.top(); st.pop();
    for (it = s1.begin(); it != s1.end(); it++)
	s2.insert(*it);
    ad(s2);
    st.push(s2);
    print();
}

void ins() {
    s1 = st.top(); st.pop();
    s2 = st.top(); st.pop();
    set<int> s3;
    it = s1.begin();
    set<int>::iterator it2 = s2.begin();
    while (it != s1.end() && it2 != s2.end()) {
	if (*it < *it2) *it++;
	else if (*it > *it2) it2++;
	else {
	    s3.insert(*it);
	    it++;
	    it2++;
	}
    }
    ad(s3);
    st.push(s3);
    print();
}

void add() {
    s1 = st.top(); st.pop();
    s2 = st.top(); st.pop();
    s2.insert(hash[s1]);
    ad(s2);
    st.push(s2);
    print();
}

int main() {
    scanf("%d", &t);
    while (t--) {
	hn = 0;
	hash.clear();
	while (!st.empty()) st.pop();
	scanf("%d", &n);
	while (n--) {
	    scanf("%s", op);
	    if (op[0] == 'P')
		pus();
	    if (op[0] == 'D')
		dup();
	    if (op[0] == 'A')
		add();
	    if (op[0] == 'U')
		uni();
	    if (op[0] == 'I')
		ins();
	}
	printf("***\n");
    }
    return 0;
}
