//HDU 3966
#include<bits/stdc++.h>
using namespace std;
const int N = 50010;
struct Edge
{
    int to, nxt;
}edge[N * 2];

int head[N], tot, n;
int top[N];
int fa[N], depth[N], siz[N], p[N], son[N], pos;
void init()
{
    tot = 0;
    for (int i = 0; i <= n; i++)
    {
        head[i] = 0;
        son[i] = -1;
    }
    pos = 1;
}

void addedge(int u, int v)
{
    edge[++tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot;
}

void dfs1(int u, int pre, int d)
{
    depth[u] = d;
    fa[u] = pre;
    siz[u] = 1;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v != pre)
        {
            dfs1(v, u, d + 1);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[son[u]] < siz[v])
                son[u] = v;
        }
    }
}

void dfs2(int u, int sp)
{
    top[u] = sp;
    p[u] = pos++;
    if (son[u] == -1)
        return;
    dfs2(son[u], sp);
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

int lowbit(int x)
{
    return x & (-x);
}

int c[N];
int sum(int x)
{
    int ans = 0;
    while (x)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

void add(int x, int val)
{
    while (x <= n)
    {
        c[x] += val;
        x += lowbit(x);
    }
}

void change(int u, int v, int val)
{
    int f1 = top[u];
    int f2 = top[v];
    int tmp = 0;
    while (f1 != f2)
    {
        if (depth[f1] < depth[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        add(p[f1], val);
        add(p[u] + 1, -val);
        u = fa[f1];
        f1 = top[u];
    }
    if(depth[u] > depth[v])
        swap(u, v);
    add(p[u], val);
    add(p[v] + 1, -val);
}

int a[N];
int main()
{
    int m, P;
    while (scanf("%d%d%d", &n, &m, &P) == 3)
    {
        int u, v;
        int c1, c2, k;
        char op[10];
        init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        while (m--)
        {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        dfs1(1, 0, 0);
        dfs2(1, 1);
        for (int i = 0; i <= n; i++)
            c[i] = 0;
        for (int i = 1; i <= n; i++)
        {
            add(p[i], a[i]);
            add(p[i] + 1, -a[i]);
        }
        while (P--)
        {
            scanf("%s", op);
            if (op[0] == 'Q')
            {
                scanf("%d", &u);
                printf("%d\n", sum(p[u]));
            }
            else
            {
                scanf("%d%d%d", &c1, &c2, &k);
                if (op[0] == 'D')
                    k = -k;
                change(c1, c2, k);
            }
        }
    }
    return 0;
}
