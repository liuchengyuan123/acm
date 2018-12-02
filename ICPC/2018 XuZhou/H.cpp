#include<bits/stdc++.h>
using namespace std;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson

const int N = 1e5 + 5;
typedef long long ll;

ll a[N];
ll sum[N << 2];
ll lazy[N << 2];

ll last;

void pushup(int rt)
{
    sum[rt] = sum[lson] + sum[rson];
}

void build(int L, int R, int rt)
{
    lazy[rt] = 0;
    if (L == R)
    {
        sum[rt] = last + a[L];
        last = sum[rt];
        //printf("pre  %d %lld\n", L, sum[rt]);
        return;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void pushdown(int L, int R, int rt)
{
    if (lazy[rt])
    {
        int len = R - L + 1;
        sum[lson] += (len - (len >> 1)) * lazy[rt];
        sum[rson] += (len >> 1) * lazy[rt];
        lazy[lson] += lazy[rt];
        lazy[rson] += lazy[rt];
        lazy[rt] = 0;
    }
}

void update(int l, int r, ll val, int L, int R, int rt)
{
    if (l <= L && r >= R)
    {
        sum[rt] += (R - L + 1) * val;
        lazy[rt] += val;
        return;
    }
    int mid = (R + L) >> 1;
    pushdown(L, R, rt);
    if (l <= mid)
        update(l, r, val, Lson);
    if (r > mid)
        update(l, r, val, Rson);
    pushup(rt);
}

ll query(int l, int r, int L, int R, int rt)
{
    if (l == 0 && r == 0)
        return 0;
    if (l <= L && r >= R)
    {
        return sum[rt];
    }
    int mid = (L + R) >> 1;
    ll ans = 0;
    pushdown(L, R, rt);
    if (l <= mid)
        ans += query(l, r, Lson);
    if (r > mid)
        ans += query(l, r, Rson);
    pushup(rt);
    return ans;
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    a[0] = 0;
    last = 0;
    build(1, n, 1);
    
    while (q--)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l, r, 1, n, 1) - (r - l + 1) * 1ll * query(l - 1, l - 1, 1, n, 1));
        }
        if (type == 2)
        {
            int x;
            ll val;
            scanf("%d%lld", &x, &val);
            update(x, n, val - a[x], 1, n, 1);
            a[x] = val;
        }
    }
    return 0;
}
