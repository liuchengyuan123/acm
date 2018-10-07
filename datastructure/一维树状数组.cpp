#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
typedef long long ll;
ll sum[N];
int n;
int lowbit(int x)
{
    return x & (-x);
}

void update(int x, ll val)
{
    while (x <= n)
    {
        sum[x] += val;
        x += lowbit(x);
    }
}

ll query(int x)
{
    ll ans = 0;
    while (x)
    {
        ans += sum[x];
        x -= lowbit(x);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int ks = 1; ks <= T; ks++)
    {
        scanf("%d", &n);
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; i++)
        {
            ll a;
            scanf("%lld", &a);
            update(i, a);
        }
        printf("Case %d:\n",ks);
        char op[100];
        while (1)
        {
            scanf("%s", op);
            if (op[0] == 'E')
                break;
            if (op[0] == 'A')
            {
                int x;
                ll val;
                scanf("%d%lld", &x, &val);
                update(x, val);
            }
            if (op[0] == 'S')
            {
                int x;
                ll val;
                scanf("%d%lld", &x, &val);
                update(x, -val);
            }
            if (op[0] == 'Q')
            {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(r) - query(l - 1));
            }
        }
    }
    return 0;
}
