//P3804
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int ch[N * 2][26];
int len[N * 2];
int fa[N * 2];
int tot;
int root, last;
ll ed[N * 2];

void init()
{
    tot = 0;
    root = last = ++tot;
    len[root] = 0;
    fa[root] = 0;
}
void insert(int x)
{
    
    int p = last;
    int np = last = ++tot;
    len[np] = len[p] + 1;
    ed[np] = 1;
    while (p && !ch[p][x])
        ch[p][x] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = ch[p][x];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++tot;
            fa[nq] = fa[q];
            len[nq]=len[p]+1;
            ed[nq] = 0;
            for (int i = 0; i < 26; i++)
                ch[nq][i] = ch[q][i];
            fa[q] = fa[np] = nq;
            while (p && ch[p][x] == q)
                ch[p][x] = nq, p = fa[p];
        }
    }
}

char s[N];
int in[N * 2];

int main()
{
    scanf("%s", s);
    int slen = strlen(s);
    init();
    for (int i = 0; i < slen; i++)
        insert(s[i] - 'a');
    memset(in, 0, sizeof(in));
    queue<int> q;
    for (int i = 1; i <= tot; i++)
    {
        in[fa[i]]++;
    }
    for (int i = 1; i <= tot; i++)
        if (!in[i])
            q.push(i);
    ll ans = 0;
    while (!q.empty())
    {
        int lcy = q.front();
        q.pop();
        if (ed[lcy] > 1)
            ans = max(ans, ed[lcy] * 1ll * len[lcy]);
        ed[fa[lcy]] += ed[lcy];
        in[fa[lcy]]--;
        if (fa[lcy] && in[fa[lcy]] == 0)
        {
            q.push(fa[lcy]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
