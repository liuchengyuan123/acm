#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int maxtre = 6e6;
struct node
{
	int lson, rson, sum;
	node()
	{
		lson = 0;
		rson = 0;
		sum = 0;
	}
}seg[maxtre];
int tot = 0;
int root[N], n, m, fa[N], a[N], num[N];
int find(int x)
{
	if (x == fa[x])
		return x;
	return fa[x] = find(fa[x]);
}
void build(int p, int L, int R, int &rt)
{
	if (!rt)
		rt = ++tot;
	seg[rt].sum++;
	if (L == R)
	{
		return;
	}
	int mid = (L + R) >> 1;
	if (p <= mid)
		build(p, L, mid, seg[rt].lson);
	else
		build(p, mid + 1, R, seg[rt].rson);
}
void Merge(int &x, int y)
{
	if (!x)
	{
		x = y;
		return;
	}
	if (!y)
	{
		return;
	}
	seg[x].sum += seg[y].sum;
	Merge(seg[x].lson, seg[y].lson);
	Merge(seg[x].rson, seg[y].rson);
}
int query(int k, int L, int R, int rt)
{
	if (L == R)
	{
		return num[L];
	}
	int mid = (L + R) >> 1;
	if (seg[seg[rt].lson].sum >= k)
		return query(k, L, mid, seg[rt].lson);
	else
	{
		return query(k - seg[seg[rt].lson].sum, mid + 1, R, seg[rt].rson);
	}
}
template <class T>
inline void read(T &ret)
{
	char c;
	ret = 0;
	while ((c = getchar()) < '0' || c > '9');
	while (c >= '0' && c <= '9')
	{
		ret = ret * 10 + (c - '0'), c = getchar();
	}
}
int main()
{
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= n; i++)
	{
		int x;
		read(x);
		a[i] = x;
		num[x] = i;
		build(x, 1, n, root[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		read(x), read(y);
		Merge(root[find(y)], root[find(x)]);
		fa[find(x)] = find(y);
	}
	int q;
	read(q);
	for (int i = 1; i <= q; i++)
	{
		char oper[10];
		scanf("%s", oper);
		if (oper[0] == 'B')
		{
			int a, b;
			read(a), read(b);
			Merge(root[find(a)], root[find(b)]);
			fa[find(b)] = find(a);
		}
		if (oper[0] == 'Q')
		{
			int a, k;
			read(a), read(k);
			if (seg[root[find(a)]].sum < k)
			{
				puts("-1");
				continue;
			}
			int ans = query(k, 1, n, root[find(a)]);
			printf("%d\n", ans);
		}
	}
	return 0;
}
