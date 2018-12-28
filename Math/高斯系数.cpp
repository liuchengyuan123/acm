#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
#define ll long long
ll mod = 1e9 + 7;
ll fac[N];
template<class T>
void read(T &ret)
{
    ret = 0;
    char c;
    while ((c = getchar()) > '9' || c < '0');
    while (c <= '9' && c >= '0')
    {
        ret = ret * 10 + c - '0';
        c = getchar();
    }
}
template<class T>
void Write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x < 10)
    {
        putchar('0' + x);
        return;
    }
    Write(x / 10);
    putchar('0' + x % 10);
}
template<class T>
void write(T x)
{
    Write(x);
    putchar('\n');
}
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
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll n, m, k;
        read(n), read(m), read(k);
        fac[0] = 1;
        for (int i = 1; i <= n + m; i++)
        {
            fac[i] = fac[i - 1] * k % mod;
        }
        ll ans = 1;
        for (int i = 0; i < n; i++)
        {
            ans = ans * (fac[n + m - i] - 1) % mod;
        }
        ll tmp = 1;
        for (int i = 1; i <= n; i++)
        {
            tmp = tmp * (fac[i] - 1) % mod;
        }
        ans = ans * Pow(tmp, mod - 2) % mod;
        write(ans);
    }
    return 0;
}
