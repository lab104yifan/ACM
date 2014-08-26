void manachar() {
    len = 2;
    s[0] = '@'; s[1] = '#';
    for (int i = 0; i < n; i++) {
	s[len++] = str[i];
	s[len++] = '#';
    }
    s[len] = '\0';
    int mx = 0, id;
    for (int i = 1; i < len; i++) {
	if (mx > i) p[i] = min(p[2 * id - i], mx - i);
	else p[i] = 1;
	while (s[i + p[i]] == s[i - p[i]]) p[i]++;
	if (i + p[i] > mx) {
	    id = i;
	    mx = i + p[i];
	}
    }
}
