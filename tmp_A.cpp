#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef ONLINE_JUDGE
#define dbg(x...) do{cout << "\033[33;1m" << #x << "->" ; err(x);} while (0)
void err(){cout << "\033[39;0m" << endl;}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x){for (auto v: a) cout << v << ' '; err(x...);}
template<typename T, typename... A>
void err(T a, A... x){cout << a << ' '; err(x...);}
#else
#define dbg(...)
#endif
#define inf 1ll << 50
const int N = 80005;
char s1[N], s2[N];
int main()
{
	int n;
	int x, y;
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &x, &y);
		scanf("%s%s", s1, s2);
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if (s1[i] == s2[i])
				cnt++;
		if (x + y - cnt > n)
		{
			puts("Lying");
			continue;
		}
		cnt = n - cnt;
		if (abs(x - y) > cnt)
			puts("Lying");
		else
			puts("Not lying");
	}
	return 0;
}
