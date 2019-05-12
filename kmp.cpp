#include <bits/stdc++.h>
using namespace std;


void getFail(char* p, int* f) {
	f[0] = 0;
	int m = strlen(p);
	for (int i = 1; i < m; ++i) {
		int j = f[i-1];
		while (j && p[j] != p[i])  j = f[j];
		f[i] = (p[j] == p[i] ? j + 1 : 0);
	}
}


vector<int> find(char* t, char* p, int* f) {
	int n = strlen(t), m = strlen(p);
	vector<int> ans;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j && p[j] != t[i])  j = f[j];
		if (p[j] == t[i])  ++j;
		if (j == m) {
			ans.push_back(i - m + 1);
			j = f[j];
		}
	}
	return ans;
}


int main() {
	const int MAXN = 1e6;
	char text[MAXN], pattern[MAXN];
	cout << "pattern: "; cin >> pattern;
	cout << "text: "; cin >> text;

	// KMP
	int fail[MAXN];
	getFail(pattern, fail);
	for(auto x: find(text, pattern, fail))  cout << "index " << x << endl;
	return 0;
}
