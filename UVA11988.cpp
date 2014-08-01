#include <cstdio>
#include <cstring>
#include <list>
#include <iostream>
using namespace std;

const int N = 100005;

char str[N];
list<char> ans;

int main() {
    while(gets(str)) {
	int len = strlen(str);
	ans.clear();
	list<char>::iterator it = ans.begin();
	for (int i = 0; i < len; i++) {
	    if (str[i] == '[') it = ans.begin();
	    else if (str[i] == ']') it = ans.end();
	    else ans.insert(it, str[i]);
	}
	for (it = ans.begin(); it != ans.end(); it++)
	    printf("%c", *it);
	printf("\n");
    }
    return 0;
}
