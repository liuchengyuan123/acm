#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#define N 250005
 
using namespace std;
 
typedef long long ll;
 
struct Node { int To, w, nxt; }e[N*2];
int Stack[N], Size[N], begind[N], deep[N], hson[N], dfn[N], fa[N], ls[N], a[N];
int n, m, Q, top, cnt, num;
ll mlen[N];
 
vector <int> dop[N];
 
int read(int &x)
{
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s >= '0' && s <= '9') { x = x * 10 + (s - '0'); s = getchar(); }
    x = x * f;  
}
 
void write(ll x)
{
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');  
}
 
bool cmp(int aa, int bb)
{
    return dfn[aa] < dfn[bb];    
}
 
void Addedge(int u, int v, int w)
{
    e[++cnt].To = v, e[cnt].w = w, e[cnt].nxt = ls[u], ls[u] = cnt;
    e[++cnt].To = u, e[cnt].w = w, e[cnt].nxt = ls[v], ls[v] = cnt;
}
 
void Jiabian(int u, int v)
{
    dop[u].push_back(v);
}
 
void dfs1(int x, int father)
{
    Size[x] = 1, fa[x] = father;
    for (int i = ls[x]; i; i = e[i].nxt)
    {
        if (e[i].To == father) continue;
        int y = e[i].To; 
        mlen[y] = min(mlen[x], (ll)e[i].w); 
        deep[y] = deep[x] + 1;
        dfs1(y, x); Size[x] += Size[y];
        if (Size[y] > Size[hson[x]]) hson[x] = y;
    }   
}
 
void dfs2(int x, int firstd)
{
    begind[x] = firstd; dfn[x] = ++num;
    if (hson[x]) dfs2(hson[x], firstd);
    for (int i = ls[x]; i; i = e[i].nxt)
        if (!begind[e[i].To]) dfs2(e[i].To, e[i].To);
}
 
int Get_lca(int x, int y)
{
    while (begind[x] != begind[y]) 
    { 
        if (deep[begind[x]] < deep[begind[y]]) swap(x, y); 
        x = fa[begind[x]];
    }
    return ((deep[x] > deep[y]) ? y : x);
}
 
void Insert(int x) 
{
    if (top == 1) { Stack[++top] = x; return; }
    int LCA = Get_lca(x, Stack[top]);
    if (LCA == Stack[top]) return;
    while(top > 1 && dfn[Stack[top - 1]] >= dfn[LCA]) 
          Jiabian(Stack[top - 1], Stack[top]), top--;
    if(LCA != Stack[top]) Jiabian(LCA, Stack[top]), Stack[top] = LCA;
    Stack[++top] = x;
}
 
ll Work_dp(int x)
{
    if (!dop[x].size()) return mlen[x];
    ll sum = 0;
    for (int i = 0; i < dop[x].size(); i++) sum += Work_dp(dop[x][i]);
    dop[x].clear();
    return min(sum, mlen[x]);
}
 
int main()
{
    read(n);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        read(u); read(v); read(w);
        Addedge(u, v, w);
    }
    deep[1] = 1, mlen[1] = 1ll<<60, dfs1(1, -1); 
    dfs2(1, 1);
    read(Q);
    while (Q--)
    {
        read(m);
        for (int i = 1; i <= m; i++) scanf("%d", &a[i]); 
        sort(a + 1, a + m + 1, cmp);
        top = 1; Stack[1] = 1;
        for (int i = 1; i <= m; i++) Insert(a[i]);
        while (top > 1) Jiabian(Stack[top - 1], Stack[top]), top--;
        write(Work_dp(1)); printf("\n"); 
    }
    return 0;
}
