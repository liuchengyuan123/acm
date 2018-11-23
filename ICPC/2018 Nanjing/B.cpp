#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int M = 105;
typedef long long ll;
int a[N][M];
int inf = 0x3f3f3f3f;

int up[M];

int main()
{
    int T;
    scanf("%d", &T);
    int ks = 0;
    while (T--)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                a[i][j] = 0;
        }
        for (int i = 0; i <= m; i++)
            up[i] = 0;
        
        for (int i = 1; i <= k; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x][y] = 1;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == 1)
                    up[j] = 0;
                else
                    up[j]++;
            }
            
            for (int j = 1; j <= m; j++)
            {
                int mn = inf;
                for (int k = j; k > 0; k--)
                {
                    mn = min(mn, up[k]);
                    ans += mn;
                }
            }
        }
        printf("Case #%d: %lld\n", ++ks, ans);
    }
    return 0;
}
