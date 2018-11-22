#include<bits/stdc++.h>
using namespace std;
const int N = 2e7 + 5;
int prime[N];
int tot;
int vis[N];
typedef long long ll;

ll f[N];

void getp()
{
    vis[1] = 1;
    f[1] = 1;
    for (int i = 2; i <= N - 5; i++)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            f[i] = 2;
        }
        for (int j = 1; j <= tot && prime[j] * i <= N - 5; j++)
        {

            if (i % prime[j] == 0)
            {
                vis[i * prime[j]] = 1;
                if (i / prime[j] % prime[j] == 0)
                    f[i * prime[j]] = 0;
                else
                    f[i * prime[j]] = f[i / prime[j]];
                break;
            }

            vis[i * prime[j]] = 1;
            f[i * prime[j]] = 2 * f[i];
        }
    }
}
ll sum[N];
int main()
{
    getp();
    sum[0] = 0;
    for (int i = 1; i <= N - 5; i++)
    {
        sum[i] = sum[i - 1] + f[i];
    }
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int n;
        scanf("%d", &n);
        printf("%lld\n", sum[n]);
    }
    return 0;
}
