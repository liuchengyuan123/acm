#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int MAXN = 1e6 + 5;
vector<int> fac[MAXN];

#define ll long long
ll ans[N];
stack<pair<int, ll> > pre;
ll mod = 1e9 + 7;

ll a[N];

int main()
{
    for (int i = 1; i <= 1000000; i++)
    {
        for (int j = 1; j * i <= 1000000; j++)
        {
            fac[i * j].push_back(i);
        }
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    ans[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (auto &u: fac[a[i]])
        {
            if (u > n)
                continue;
            //printf("%d %lld\n", u, ans[u - 1]);
            pre.push(make_pair(u, ans[u - 1]));
        }
        while (!pre.empty())
        {
            pair<int, ll> f = pre.top();
            pre.pop();
            ans[f.first] = (ans[f.first] + f.second) % mod;
        }
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++)
        sum = (sum + ans[i]) % mod;
    printf("%lld\n", sum);
    return 0;
}
