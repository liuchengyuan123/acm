//shuoj #560
#include<bits/stdc++.h>
using namespace std;
const int N = 1e9 + 5;
typedef long long ll;
const ll mod = 1e9 + 7;
const int MAX = 1e5 + 5;
ll prime[MAX];
ll spg[10000];
ll sph[10000];
ll spi[10000];
ll w[MAX];
ll id1[MAX];
ll id2[MAX];
ll g[MAX], h[MAX], ii[MAX];
int tot;
bool vis[MAX];

ll Pow(ll a, int b)
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

void pre(int n)
{
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    prime[tot = 0] = 1;
    sph[0] = spg[0] = spi[0] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            spg[tot] = (spg[tot - 1] + i * i % mod) % mod;
            sph[tot] = (sph[tot - 1] + 2 * i) % mod;
            spi[tot] = spi[tot - 1] + 1;
        }
        for (int j = 1; j <= tot && prime[j] * i <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}

ll sqr, n, m;

ll S(ll x, int y)
{
    if (x <= 1 || prime[y] > x)
    {
        return 0;
    }
    int k = (x <= sqr) ? id1[x] : id2[n / x];
    ll ret = (g[k] - spg[y - 1] + h[k] - sph[y - 1] - (ii[k] - spi[y - 1]) + mod) % mod;
    for (int i = y; i <= tot && 1ll * prime[i] * prime[i] <= x; i++)
    {
        ll t1 = prime[i], t2 = 1ll * prime[i] * prime[i];
        for (int e = 1; t2 <= x; e++, t1 = t2, t2 *= prime[i])
        {
            if (e == 1)
            {
                ret = (ret + 1ll * S(x / t1, i + 1) * (prime[i] * prime[i] % mod + 2 * prime[i] % mod - 1) % mod - 3 + mod) % mod;
                continue;
            }
            ret = (ret - 1ll * S(x / t1, i + 1) * 3 % mod - 3 + mod) % mod;
        }
    }
    return ret;
}

void solve()
{
    m = 0;
    sqr = sqrt(n);
    pre(sqr);
    int l, r;
    ll inv6 = Pow(6, mod - 2);
    for (l = 1; l <= n; l = r + 1)
    {
        r = n / (n / l);
        w[++m] = n / l;
        g[m] = w[m] * (w[m] + 1) % mod * (2 * w[m] + 1) % mod * inv6 % mod;     //二次项
        g[m] = (g[m] - 1 + mod) % mod;          //减去1
        h[m] = w[m] * (w[m] + 1) % mod;
        h[m] = (h[m] - 2 + mod) % mod;
        ii[m] = w[m] - 1;
        if (n / l <= sqr)
        {
            id1[w[m]] = m;
        }
        else
        {
            id2[r] = m;
        }
    }
    for (int j = 1; j <= tot; j++)
    {
        for (int i = 1; i <= m && prime[j] * prime[j] <= w[i]; i++)
        {
            int k = (w[i] / prime[j] <= sqr)? id1[w[i] / prime[j]] : id2[n / (w[i] / prime[j])];
            g[i] = (g[i] - 1ll * prime[j] * prime[j] % mod * (g[k] - spg[j - 1]) + mod) % mod;
            h[i] = (h[i] - 1ll * prime[j] * (h[k] - sph[j - 1]) + mod) % mod;
            ii[i] = (ii[i] - (ii[k] - spi[j - 1]) + mod) % mod;
        }
    }
    ll ans = S(n, 1) + 1;
    printf("%lld\n", ans);
}

int main()
{
    while (scanf("%lld", &n) == 1)
    {
        solve();
    }
    return 0;
}
