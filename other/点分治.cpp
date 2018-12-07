// POJ1741

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 1e4 + 5;
int G[N];
int sz[N], f[N];
bool vis[N];
int root;
int k;

struct edge
{
	int v, d;
	int next;
	edge(int next = 0, int v = 0, int d = 0) : next(next), v(v), d(d) {}
}e[N * 2];
int edge_tot = 0;

void add(int u, int v, int d)
{
	e[++edge_tot].v = v;
	e[edge_tot].d = d;
	e[edge_tot].next = G[u];
	G[u] = edge_tot;
}

void getroot(int u, int fa, int n)
{
	sz[u] = 1; f[u] = 0;
	int index = G[u];
	while (index != -1)
	{
		int v = e[index].v;
		index = e[index].next;
		if (v == fa || vis[v]) 
			continue;
		getroot(v, u, n);
		sz[u] += sz[v]; f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], n - sz[u]);
	if (f[u] < f[root]) 
		root = u;
}

int dis[N];
int t, ans;

void getdis(int u, int fa, int d) //计算距离
{
	dis[++t] = d;
	int index = G[u];
	while (index != -1)
	{
		int v = e[index].v, dd = e[index].d;
		index = e[index].next;
		if (vis[v] || v == fa)
			continue;
		getdis(v, u, d + dd);
	}
	return;
}

int calc(int u, int d)
{
	t = 0;
	getdis(u, 0, d);
	sort(dis + 1, dis + t + 1);
	int l = 1, r = t;
	int ret = 0;
	while (l < r)
	{
		if (dis[l] + dis[r] <= k)
		{
			ret += r - l;
			l++;
		}
		else
			r--;
	}
	return ret;
}

void home(int u) //分治
{
	vis[u] = true;
	ans += calc(u, 0);
	int index = G[u];
	while (index != -1)
	{
		int v = e[index].v, dd = e[index].d;
		index = e[index].next;
		if (vis[v])
			continue;
		ans -= calc(v, dd);
		root = 0;
		f[0] = inf;
		getroot(v, u, sz[v]);
		home(root);
	}
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
	int n;
	while (1)
	{
		read(n), read(k);
		if (n == 0 && k == 0)
			break;
		edge_tot = 0;
		memset(G, -1, sizeof(G));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i < n; i++)
		{
			int u, v, d;
			read(u), read(v), read(d);
			add(u, v, d);
			add(v, u, d);
		}
		root = 0;
		f[0] = inf;
		ans = 0;
		getroot(1, 0, n);
		home(root);
		printf("%d\n", ans);
	}
	return 0;
}
