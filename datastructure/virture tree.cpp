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
const int N = 250005;
struct Edge
{
	int v, nxt, c;
}edge[N], fake[N];
int c[N], cc[N];
int tot, fkt;
int head[N];
int headv[N];
void add_edge(int u, int v, int c)
{
	edge[++tot].c = c;
	edge[tot].v = v;
	edge[tot].nxt = head[u];
	head[u] = tot;
}
int st[N];
int top[N], id[N], son[N], fa[N], size[N], dep[N], rnk[N];
void dfs1(int u, int f)
{
	fa[u] = f;
	dep[u] = dep[f] + 1;
	size[u] = 1;
	for (int it = head[u]; it != -1; it = edge[it].nxt)
	{
		int v = edge[it].v;
		if (v == fa[u])
			continue;
		c[v] = edge[it].c;
		dfs1(v, u);
		if (son[u] == -1 || size[son[u]] < size[v])
			son[u] = v;
		size[u] += size[v];
	}
}
int cur;
void dfs2(int u, int t)
{
	id[u] = ++cur;
	top[u] = t;
	rnk[cur] = u;
	if (son[u] != -1)
		dfs2(son[u], t);
	for (int it = head[u]; it != -1; it = edge[it].nxt)
	{
		int v = edge[it].v;
		if (v == fa[u] || v == son[u])
		{
			continue;
		}
		dfs2(v, v);
	}
}

int LCA(int u, int v)
{
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v]? u : v;
}
void add_fake(int u, int v, int c)
{
	fake[++fkt].c = c;
	fake[fkt].v = v;
	fake[fkt].nxt = headv[u];
	headv[u] = fkt;
}
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
int seg[N << 2];
void push_up(int rt)
{
	seg[rt] = min(seg[lson], seg[rson]);
}

void build(int L, int R, int rt)
{
	if (L == R)
	{
		seg[rt] = c[rnk[L]];
		return;
	}
	int mid = (L + R) >> 1;
	build(Lson);
	build(Rson);
	push_up(rt);
}

int query(int l, int r, int L, int R, int rt)
{
	if (l <= L && r >= R)
		return seg[rt];
	int mid = (L + R) >> 1;
	int ans = 0x3f3f3f3f;
	if (l <= mid)
		ans = min(ans, query(l, r, Lson));
	if (r > mid)
		ans = min(ans, query(l, r, Rson));
}
int calc(int u, int v)
{
	int ans = 0x3f3f3f3f;
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		ans = min(ans, query(id[top[u]], id[u], 1, cur, 1));
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])
		swap(u, v);
	ans = min(ans, query(id[son[v]], id[u], 1, cur, 1));
	return ans;
}
void init()
{
	tot = fkt = 0;
	cur = 0;
	for (int i = 1; i <= 250000; i++)
	{
		son[i] = -1;
		head[i] = -1;
		headv[i] = -1;
	}
	dep[0] = -1;
	fa[1] = 0;
}

bool cmp(int a, int b)
{
	return id[a] < id[b];
}
vector<int> order;
bool sep[N];
ll dp(int u, int f, int c)
{
	dbg(u, f);
	int ans = 0;
	for (int it = headv[u]; it != -1; it = fake[it].nxt)
	{
		int v = fake[it].v;
		if (v == f)
			continue;
		ans += dp(v, u, fake[it].c);
	}
	headv[u] = -1;
	if (sep[u])
		return c;
	if (u == 1)
		return ans;
	return min(ans, c);
}

int main()
{
	int n;
	scanf("%d", &n);
	init();
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	int m;
	scanf("%d", &m);
	build(1, cur, 1);
	while (m--)
	{
		int k;
		fkt = 0;
		scanf("%d", &k);
		int st_top = 0;
		for (int i = 1; i <= k; i++)
		{
			int mtp;
			scanf("%d", &mtp);
			order.push_back(mtp);
			sep[mtp] = 1;
		}
		order.push_back(1);
		sort(order.begin(), order.end(), cmp);
		order.erase(unique(order.begin(),order.end()),order.end());
		for (auto &x:order)
		{
			dbg(x);
			if (st_top == 0)
			{
				st[++st_top] = x;
				continue;
			}
			int lca = LCA(st[st_top], x);
			dbg(lca);
			if (lca == st[st_top])
			{
				st[++st_top] = x;
				continue;
			}
			while (st_top > 1 && id[lca] <= id[st[st_top - 1]])
			{
				add_fake(st[st_top - 1], st[st_top], calc(st[st_top - 1], st[st_top]));
				st_top--;
			}
			if (lca != st[st_top])
			{
				add_fake(lca, st[st_top], calc(lca, st[st_top]));
				st[st_top] = lca;
			}
			st[++st_top] = x;
		}
		printf("%lld\n", dp(1, 0, 0));
		for (auto &x : order)
			sep[x] = 0;
	}
	return 0;
}
