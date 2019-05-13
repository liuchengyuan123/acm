#include<bits/stdc++.h>
using namespace std;
#define ll long long
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
const int N  = 2e5 + 5;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson

int a[N];
int base[N << 2][31], bscnt[N << 2];
int x[62], y[31];
void push_up(int a, int b, int c)
{
	int cur = 0;
	for (int i = 1; i <= bscnt[a]; i++)
		x[cur++] = base[a][i];
	for (int i = 1; i <= bscnt[b]; i++)
		x[cur++] = base[b][i];
	bscnt[c] = 0;
	for (int i = 0; i < 31; i++)
		base[c][i] = 0, y[i] = 0;
	for (int i = 0; i < cur; i++)
		for (int j = 30; j >= 0; j--)
		{
			if (x[i] >> j & 1)
			{
				if (!y[j])
				{
					y[j] = x[i];
					break;
				}
				else
					x[i] ^= y[j];
			}
		}
	for (int i = 0; i < 31; i++)
		if (y[i])
			base[c][++bscnt[c]] = y[i];
}

void build(int L, int R, int rt)
{
	if (L == R)
	{
		base[rt][bscnt[rt] = 1] = a[L] ^ a[L - 1];
		if (base[rt][1] == 0)
			bscnt[rt] = 0;
		return;
	}
	int mid = (L + R) >> 1;
	build(Lson);
	build(Rson);
	push_up(lson, rson, rt);
}

void update(int x, int val, int L, int R, int rt)
{
	//puts("update");
	//dbg(x, val, L, R, val);
	if (L > R)
		return;
	if (L == R)
	{
		/*
		if (L == 6)
		{
			dbg(base[rt][1], val);
		}
		*/
		base[rt][1] ^= val;
		if (base[rt][1] == 0)
			bscnt[rt] = 0;
		else
			bscnt[rt] = 1;
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid)
		update(x, val, Lson);
	else
		update(x, val, Rson);
	push_up(lson, rson, rt);
}

void query(int l, int r, int L, int R, int rt)
{
	if (L > R)
		return;
	if (l <= L && r >= R)
	{
		/*
		if (L == 6)
		{
			puts("query");
			dbg(bscnt[rt]);
		}
		*/
		push_up(0, rt, 0);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid)
		query(l, r, Lson);
	if (r > mid)
		query(l, r, Rson);
}

int change[N];

inline int lowbit(int x)
{
	return x & -x;
}

void XOR(int x, int val)
{
	while (x <= 200000)
	{
		change[x] ^= val;
		x += lowbit(x);
	}
}

int sum(int x)
{
	int ans = 0;
	while (x)
	{
		ans ^= change[x];
		x -= lowbit(x);
	}
	return ans;
}

template<class T>
void read(T& ret)
{
	ret = 0;
	char c;
	while ((c = getchar()) > '9' || c < '0');
	while (c >= '0' && c <= '9')
	{
		ret = ret * 10 + c - '0';
		c = getchar();
	}
}
int main()
{
	int n, q;
	read(n), read(q);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	a[0] = 0;
	build(1, n, 1);
	for (int i = 1; i <= n; i++)
		change[i] = 0;
	while (q--)
	{
		int ty;
		read(ty);
		if (ty == 1)
		{
			int l, r, k;
			read(l), read(r), read(k);
			update(l, k, 1, n, 1);
			if (r < n)
				update(r + 1, k, 1, n, 1);
			XOR(l, k);
			if (r < n)
				XOR(r + 1, k);
		}
		else
		{
			int l, r;
			read(l), read(r);
			bscnt[0] = 0;
			int ball = sum(l) ^ a[l];
			//dbg(ball);
			if (ball)
				base[0][++bscnt[0]] = ball;
			query(l + 1, r, 1, n, 1);
			printf("%lld\n", 1ll << bscnt[0]);
		}
	}
	return 0;
}
