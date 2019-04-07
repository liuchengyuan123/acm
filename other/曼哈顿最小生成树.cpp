//poj3241
//debug惨痛历史
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<math.h>
using namespace std;
const int N = 1e4 + 5;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson

struct node
{
	int a, b, id;
	bool operator < (const node& x) const
	{
		if (a == x.a)
			return b < x.b;
		return a < x.a;
	}
	node(int a = 0, int b = 0, int id = 0) : a(a), b(b), id(id) {}
}a[N];
int lis[N];
int li_cnt = 0;
int seg[N << 2];
int is[N << 2];

void pushup(int rt)
{
	if (seg[lson] < seg[rson])
	{
		seg[rt] = seg[lson];
		is[rt] = is[lson];
	}
	else
	{
		seg[rt] = seg[rson];
		is[rt] = is[rson];
	}
}

int inf = 0x3f3f3f3f;

void build(int L, int R, int rt)
{
	if (L == R)
	{
		is[rt] = -1;
		seg[rt] = inf;
		return;
	}
	int mid = (L + R) >> 1;
	build(Lson);
	build(Rson);
	pushup(rt);
	is[rt] = -1;
}

void update(int l, int r, int val, int id, int L, int R, int rt)
{
	if (L == R)
	{
		if (val < seg[rt])
		{
			seg[rt] = val;
			is[rt] = id;
		}
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid)
		update(l, r, val, id, Lson);
	if (r > mid)
		update(l, r, val, id, Rson);
	pushup(rt);
}

int query(int l, int r, int L, int R, int rt)
{
// 	printf("on seg , %d %d %d %d\n", l, r, L, R);
	if (l <= L && r >= R)
		return is[rt];
	int mid = (L + R) >> 1;
	int ans = inf;
	int q_id = -1;
	if (l <= mid)
	{
		int ret = query(l, r, Lson);
		if (ret != -1 && (q_id == -1 || ans > a[ret].a + a[ret].b))
		{
			ans = a[ret].a + a[ret].b;
			q_id = ret;
		}
//		printf("lson ret %d\n", ret);
	}
	if (r > mid)
	{
		int ret = query(l, r, Rson);
		if (ret != -1 && (q_id == -1 || ans > a[ret].a + a[ret].b))
		{
			ans = a[ret].a + a[ret].b;
			q_id = ret;
		}
//		printf("rson ret %d\n", ret);
	}
	return q_id;
}

int tot = 0;
struct Edge
{
	int u, v, w;
	Edge(int v = 0, int u = 0, int w = 0) : v(v), u(u), w(w) {}
	bool operator < (const Edge& e) const
	{
		return w < e.w;
	}
}edge[N * 4];

int head[N];

void add_edge(int u, int v, int w)
{
	edge[++tot] = Edge(v, u, w);
}

void get_edge(int n, int li_cnt)
{
	for (int i = n; i >= 1; i--)
	{
//		printf("get edge %d %d\n", i, a[i].id);
		int tmp = lower_bound(lis, lis + li_cnt, a[i].b - a[i].a) - lis + 1;
		int ret = query(tmp, li_cnt, 1, li_cnt, 1);
//		printf("ret %d\n", ret);
		if (ret != -1)
			add_edge(a[i].id, a[ret].id, a[ret].a + a[ret].b - a[i].a - a[i].b);
//		printf("update %d\n", tmp);
		update(tmp, tmp, a[i].a + a[i].b, i, 1, li_cnt, 1);
	}
}

int fa[N];

int Find(int x)
{
	if (x == fa[x])
		return x;
	return fa[x] = Find(fa[x]);
}

void Merge(int a, int b)
{
	a = fa[a], b = fa[b];
	if (a == b)
		return;
	fa[a] = b;
}

bool check(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (Find(i) != Find(1))
			return false;
	}
	return true;
}

priority_queue<int> pq;

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	li_cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		head[i] = 0;
		scanf("%d%d", &a[i].a, &a[i].b);
		a[i].id = i;
		fa[i] = i;
		lis[li_cnt++] = a[i].b - a[i].a;
	}
	sort(lis, lis + li_cnt);
    li_cnt = unique(lis, lis + li_cnt) - lis;
	sort(a + 1, a + n + 1);
	build(1, li_cnt, 1);
	//debug
//	puts("ljkahsdkj 1");
	get_edge(n, li_cnt);
	
	for (int i = 1; i <= n; i++)
		swap(a[i].a, a[i].b);
	sort(a + 1, a + n + 1);
	li_cnt = 0;
	for (int i = 1; i <= n; i++)
		lis[li_cnt++] = a[i].b - a[i].a;
	sort(lis, lis + li_cnt);
	li_cnt = unique(lis, lis + li_cnt) - lis;
	build(1, li_cnt, 1);
	//debug
//	puts("jkshdakj 2");
	get_edge(n, li_cnt);

	li_cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i].b = -a[i].b;
		lis[li_cnt++] = a[i].b - a[i].a;
	}
	sort(lis, lis + li_cnt);
	li_cnt = unique(lis, lis + li_cnt) - lis;
	sort(a + 1, a + n + 1);
	build(1, li_cnt, 1);
	//debug
//	puts("jahsdjka 3");
	get_edge(n, li_cnt);

	li_cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		swap(a[i].a, a[i].b);
		lis[li_cnt++] = a[i].b - a[i].a;
	}
	sort(lis, lis + li_cnt);
	li_cnt = unique(lis, lis + li_cnt) - lis;
	sort(a + 1, a + n + 1);
	build(1, li_cnt, 1);
	//debug
//	puts("asjdh 4");
	get_edge(n, li_cnt);
//	puts("");
	sort(edge + 1, edge + tot + 1);
	for (int i = 1; i <= tot; i++)
	{
		int x = Find(edge[i].u), y = Find(edge[i].v);
//		printf("add_edge %d %d %d yes? %d\n", edge[i].u, edge[i].v, edge[i].w, x == y);
		if (x != y)
		{
			Merge(x, y);
			pq.push(edge[i].w);
			if (check(n))
				break;
		}
	}
	k -= 1;
	while (k--)
		 pq.pop();
	printf("%d\n", pq.top());
	return 0;
}
