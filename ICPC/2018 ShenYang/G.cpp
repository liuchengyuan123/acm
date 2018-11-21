#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 1e9 + 7;

ll Pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

const int C = 10000;

ll fac[C];
vector<ll> mult;

int main()
{
    ll inv2 = (mod + 1) / 2;
    ll inv6 = Pow(6, mod - 2) % mod;
    ll m, n;

    #ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif

    while (scanf("%lld%lld", &n, &m) == 2)
    {
        int tot = 0;
        ll t = m;
        for (int i = 2; i * i <= t; i++)
        {
            if (t % i == 0)
            {
                fac[++tot] = i * 1ll;
                t /= i;
                while (t % i == 0)
                    t /= i;
            }
        }
        if (t > 1)
            fac[++tot] = t * 1ll;
        mult.clear();
        ll ans = n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + n * (n + 1) % mod * inv2 % mod;
        ans %= mod;

        //printf("%d\n", tot);

        mult.push_back(-1);
        for (int i = 1; i <= tot; i++)
        {
            for (auto &u: mult)
            {
                //printf("%lld %lld\n", fac[i], u);
                ll tmp = u * fac[i];
                if (abs(tmp) > n)
                    continue;
                int f = 1;
                if (tmp < 0)
                    f = -1;
                tmp = abs(tmp);
                ll tim = n / tmp;
                ans = (ans + tmp * tim % mod * (tim + 1) % mod * inv2 % mod * f + tmp * tmp % mod * tim % mod * (tim + 1) % mod * (2 * tim + 1) % mod * inv6 % mod * f + mod * 2) % mod;
                mult.push_back(tmp * f * (-1));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
