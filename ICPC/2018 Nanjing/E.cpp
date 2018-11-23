#include<bits/stdc++.h>
using namespace std;
const int N = 25;
int a[N];
int b[N];
int s[N];
typedef long long ll;
ll dp[2097152];
ll inf = 1 << 60;

int popcount(ll x)
{
    int cnt = 0;
    while (x)
    {
        x -= x & (-x);
        cnt++;
    }
    return cnt;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &a[i], &b[i], &s[i]);
        int pp = 0;
        for (int j = 1; j <= s[i]; j++)
        {
            int x;
            scanf("%d", &x);
            x--;
            pp |= 1 << x;
        }
        s[i] = pp;
    }
    for (int i = 0; i <= 2000000; i++)
    {
        dp[i] = 0;
    }
    dp[0] = 0;
    int up = (1 << n) - 1;
    for (int i = 0; i <= up; i++)
    {
        bool can = 1;
        for (int j = 0; j < n; j++)
        {
            if (!(i & (1 << j)))
                continue;
            if ((i & s[j]) < s[j])
            {
                can = 0;
                break;
            }
        }
        if (!can)
            continue;
        for (int j = 0; j < n; j++)
        {
            if (((i & (1 << j)) == 0) && ((i & s[j]) == s[j]))
            {
                dp[i | (1 << j)] = max(dp[i | (1 << j)], dp[i] + a[j] * (popcount(i) + 1) + b[j]);
            }
        }
    }
    printf("%lld\n", dp[(1 << n) - 1]);
    return 0;
}
