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
const int N = 2e5 + 5;
int h[N];
int p[N];
vector<int> dec;
int R[N], u[N][35];
stack<int> dst;
int sum[N][35];
int main()
{
	int n, q;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i], &h[i]);
	R[n] = p[n] + h[n];
	dst.push(n);
	u[n][0] = n + 1;
	u[n + 1][0] = n + 1;
	for (int i = n - 1; i >= 1; i--)
	{
		R[i] = p[i] + h[i];
		u[i][0] = n + 1;
		while (!dst.empty() && R[i] >= p[dst.top()])
		{
			R[i] = max(R[i], R[dst.top()]);
			dst.pop();
		}
		if (!dst.empty())
		{
			u[i][0] = dst.top();
			sum[i][0] = p[dst.top()] - R[i];
		}
		dst.push(i);
	}
	/*
	for (int i = 1; i <= n; i++)
	{
		printf("i %d R %d u %d\n", i, R[i], u[i][0]);
	}
	*/
	for (int k = 1; k <= 18; k++)
	{
		u[n + 1][k] = n + 1;
		for (int i = 1; i <= n; i++)
		{
			u[i][k] = u[u[i][k - 1]][k - 1];
			sum[i][k] = sum[i][k - 1] + sum[u[i][k - 1]][k - 1];
		}
	}
	scanf("%d", &q);
	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int ret = 0;
		for (int k = 18; k >= 0; k--)
			if (u[l][k] <= r)
			{
				ret += sum[l][k];
				l = u[l][k];
			}
		printf("%d\n", ret);
	}
	return 0;
}
