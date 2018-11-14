#include<bits/stdc++.h>
using namespace std;
const int N = 3e4 + 5;
const int M = 1e5 + 5;
#define inf 0x3f3f3f3f
struct edge
{
    int to, w;
    edge(int v, int w): to(v), w(w) {}
};
struct node
{
    int po, dis;
    node(int p, int d): po(p), dis(d) {}
    bool operator < (const node& a) const
    {
        return dis > a.dis;
    }
};
int n, m;
vector<edge> G[N];
int d[N];
priority_queue<node> pq;

void dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
        d[i] = inf;
    d[s] = 0;
    pq.push(node(s, 0));

    while (!pq.empty())
    {
        node f = pq.top();
        pq.pop();
        int lcy = f.po;
        if (d[lcy] < f.dis)
            continue;
        for (auto &t : G[lcy])
        {
            if (d[lcy] + t.w < d[t.to])
            {
                d[t.to] = d[lcy] + t.w;
                pq.push(node(t.to, d[t.to]));
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        G[i].clear();
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(edge(v, w));
        G[v].push_back(edge(u, w));
    }
    dijkstra(1);
    printf("%d\n", d[n]);
    return 0;
}
