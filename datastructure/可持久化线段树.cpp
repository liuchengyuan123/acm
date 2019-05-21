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
const int N = 1e5 + 5;
int lson[20 * N], rson[20 * N], val[20 * N];
int root[N];
int tot = 0;

void push_up(int rt)
{
	val[rt] = val[lson[rt]] + val[rson[rt]];
}
void update(int old, int p, int L, int R, int &rt)
{
	rt = ++tot;
	lson[rt] = lson[old];
	rson[rt] = rson[old];
	val[rt] = val[old];
	if (L == R)
	{
		val[rt]++;
		return;
	}
	int mid = (L + R) >> 1;
	if (p <= mid)
		update(lson[old], p, L, mid, lson[rt]);
	else
		update(rson[old], p, mid + 1, R, rson[rt]);
	push_up(rt);
}

int query(int l, int r, int L, int R, int rt)
{
	if (rt == 0)
		return 0;
	if (l <= L && r >= R)
		return val[rt];
	int mid = L + R >> 1;
	int ans = 0;
	if (l <= mid)
		ans += query(l, r, L, mid, lson[rt]);
	if (r > mid)
		ans += query(l, r, mid + 1, R, rson[rt]);
	return ans;
}

int a[N];
vector<int> det;
int main()
{
	int n, m;
	int cur = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), det.push_back(a[i]);
	sort(det.begin(), det.end());
	det.erase(unique(det.begin(), det.end()), det.end());
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(det.begin(), det.end(), a[i]) - det.begin() + 1;
	int sz = det.size();
	for (int i = 1; i <= n; i++)
		update(root[i - 1], a[i], 1, sz, root[i]);
	while (m--)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		int left = 1, right = sz;
		while (left < right)
		{
			int mid = (left + right) >> 1;
			int cnt = query(1, mid, 1, sz, root[r]) - query(1, mid, 1, sz, root[l - 1]);
			if (cnt >= k)
				right = mid;
			else
				left = mid + 1;
		}
		printf("%d\n", det[left - 1]);
	}
	return 0;
}
