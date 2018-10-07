//HDU2222

#include<bits/stdc++.h>
#define siz 26
using namespace std;
const int N = 1e4 * 50;
int ch[N][siz];
int fail[N];
int ed[N];
bool vis[N];
int sz;
int root;
char nit = 'a';

void init(int n)
{
    root = 0;
    for (int i = 0; i < siz; i++)
        ch[root][i] = 0;
    fail[root] = 0;
    ed[root] = 0;
    sz = 0;
}

int newnode()
{
    sz++;
    for (int i = 0; i < siz; i++)
    {
        ch[sz][i] = 0;
    }
    fail[sz] = 0;
    ed[sz] = 0;
    return sz;
}

void insert(char buf[])
{
    int len = strlen(buf);
    int now = root;
    for (int i = 0; i < len; i++)
    {
        if (!ch[now][buf[i] - nit])
        {
            ch[now][buf[i] - nit] = newnode();
        }
        now = ch[now][buf[i] - nit];
    }
    ed[now]++;
}

void getfail()
{
    fail[root] =root;
    queue<int> Q;
    for (int i = 0; i < siz; i++)
    {
        int u = ch[root][i];
        if (u)
        {
            fail[u] = root;
            Q.push(u);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < siz; i++)
        {
            int v = ch[u][i];
            if (!v)
            {
                ch[u][i] = ch[fail[u]][i];
                continue;
            }
            int tmp = fail[u];
            while (tmp != root && !ch[tmp][i])
                tmp = fail[tmp];
            fail[v] = ch[tmp][i];
            Q.push(v);
        }
    }
}

void resetv()
{
    memset(vis, 0, sizeof(vis));
}

int query(char buf[])
{
    int len = strlen(buf);
    int cnt = 0;
    int now = root;
    resetv();
    for (int i = 0; i < len; i++)
    {
        while (now != root && !ch[now][buf[i] - nit])
            now = fail[now];
        now = ch[now][buf[i] - nit];
        int tmp = now;
        while (tmp != root)
        {
            if (ed[tmp] && !vis[tmp])
            {
                cnt += ed[tmp];
                vis[tmp] = true;
            }
            tmp = fail[tmp];
        }
    }
    return cnt;
}

char s[1000005];

int main()
{
    int n, m;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        init(n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", s);
            insert(s);
        }
        getfail();
        scanf("%s", s);
        printf("%d\n", query(s));
    }
    return 0;
}
