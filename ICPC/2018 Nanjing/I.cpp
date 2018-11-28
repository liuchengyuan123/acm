#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
typedef long long ll;
ll mod = 1e9 + 7;

ll Pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

struct Palindrome_Tree
{
    int n, sz, last;
    int ch[N][15], fail[N], cnt[N], len[N], s[N];

    int root1, root0;
    ll ans = 0;
    int new_node(int x)
    {
        for (int i = 0; i < 10; i++)
            ch[sz][i] = 0;
        cnt[sz] = 0;
        len[sz] = x;
        return sz++;
    }

    void init()
    {
        ans = 0;
        sz = 0;
        root0 = new_node(0), root1 = new_node(-1);
        last = 0;
        n = 0;
        s[0] = -1, fail[0] = 1;
        fail[1] = 0, s[1] = 0;
    }

    int get_fail(int u)
    {
        while (s[n - len[u] - 1] != s[n])
            u = fail[u];
        return u;
    }

    void add(int c)
    {
        c -= '0';
        s[++n] = c;
        int u = get_fail(last);
        if (!ch[u][c])
        {
            int np = new_node(len[u] + 2);
            fail[np] = ch[get_fail(fail[u])][c];
            ch[u][c] = np;
        }
        last = ch[u][c];
        cnt[last]++;
    }

    void counnt()
    {
        for (int i = sz - 1; i >= 0; i--)
            cnt[fail[i]] += cnt[i];
    }
    void dfs(int u, ll ret)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!ch[u][i])
                continue;
            int tp = ch[u][i];
            //printf("%d %d %d\n", u, tp, cnt[tp]);
            if (u == root0)
            {
                ans += (i * 10 + i);
                ans %= mod;
                //printf("%lld\n", ans);
                dfs(tp, i * 10 + i);
                continue;
            }
            else if (u == root1)
            {
                ans += i;
                ans %= mod;
                //printf("%lld\n", ans);
                dfs(tp, i);
                continue;
            }
            else
            {
                ll tmp = Pow(10, len[tp] - 1) * i % mod + ret * 10 % mod + i;
                tmp %= mod;
                ans += tmp;
                ans %= mod;
                //printf("%lld\n", ans);
                dfs(tp, tmp);
            }
        }
    }

};

Palindrome_Tree pt;
char s[N];

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        pt.init();
        int len = strlen(s);
        for (int i = 0; i < len; i++)
            pt.add(s[i]);
        pt.counnt();
        pt.dfs(1, 0);
        pt.dfs(0, 0);

        printf("%lld\n", pt.ans);
    }

    return 0;
}
