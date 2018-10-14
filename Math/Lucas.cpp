//HDU 3037
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll mod;
ll mult[N];
ll inv[N];

ll Lucas(ll a, ll b)
{
    ll ans = 1;
    while (a && b)
    {
        ll n = a % mod;
        ll m = b % mod;
        if (n < m)
            return 0;
        ans = ans * mult[n] % mod * inv[mult[n - m] * mult[m] % mod] % mod;
        a /= mod;
        b /= mod;
    }
    return ans;
}

int main()
{
    mult[0] = 1;
    mult[1] = 1;
    inv[1] = 1;
    int T;
    scanf("%d", &T);
    ll a, b;
    while (T--)
    {
        scanf("%lld%lld", &a, &b);
        scanf("%lld", &mod);
        for (int i = 2; i < mod; i++)
            mult[i] = mult[i - 1] * i % mod, inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        ll ans = Lucas(a + b, b);
        printf("%lld\n", ans);
    }
    return 0;
}
