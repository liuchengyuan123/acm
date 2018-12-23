/*
https://ac.nowcoder.com/acm/contest/280/D
*/

#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
const int M = 2e5 + 5;
int sta[N];
const int inf = 0x3f3f3f3f;
struct node
{
    int v, w, pre;
}edge[2 * M];
int tot;

void addedge(int u, int v, int w)
{
    edge[++tot].v = v;
    edge[tot].w = w;
    edge[tot].pre = sta[u];
    sta[u] = tot;
}

int dis[N];
int n, m;
struct cmp
{
    bool operator () (int a, int b)
    {
        return dis[a] > dis[b];
    }
};
priority_queue<int, vector<int>, cmp> pq;
bool known[N];

int main()
{
    int s, t;
    while (scanf("%d%d%d%d", &n, &m, &s, &t) == 4)
    {

        for (int i = 1; i <= n; i++)
            sta[i] = -1, known[i] = false;
        tot = 0;
        for (int i = 1; i <= m; i++)
        {
            int f, u, v, w;
            scanf("%d%d%d%d", &f, &u, &v, &w);
            if (f == 0)
                continue;
            addedge(u, v, w);
            addedge(v, u, w);
        }
        memset(dis, inf, sizeof(dis));
        dis[s] = 0;
        while (!pq.empty())
            pq.pop();
        pq.push(s);
        while (!pq.empty())
        {
            int f = pq.top();
            pq.pop();
            if (known[f])
                continue;
            known[f] = true;
            for (int t = sta[f]; t != -1; t = edge[t].pre)
            {
                int v = edge[t].v;
                if (known[v])
                    continue;
                if (dis[v] <= dis[f] + edge[t].w)
                    continue;
                dis[v] = dis[f] + edge[t].w;
                pq.push(v);
            }
        }
        printf("%d\n", dis[t]);
    }
    return 0;
}
