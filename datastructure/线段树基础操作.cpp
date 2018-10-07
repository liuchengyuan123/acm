#include<bits/stdc++.h>
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
using namespace std;
const int N = 5e4 + 5;
typedef long long ll;
ll lazy[N << 2];
ll sum[N << 2];

void pushup(int rt)
{
    sum[rt] = sum[lson] + sum[rson];
}

void build(int L, int R, int rt)
{
    lazy[rt] = 0;
    if (L == R)
    {
        scanf("%lld", &sum[rt]);
        return;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void pushdown(int rt, int len)
{
    if (lazy[rt])
    {
        sum[lson] += lazy[rt] * (len - len >> 1);
        sum[rson] += lazy[rt] * (len >> 1);
        lazy[lson] += lazy[rt];
        lazy[rson] += lazy[rt];
        lazy[rt] = 0;
    }
}

void Insert(int l, int r, ll val, int L, int R, int rt)
{
    if (l <= L && r >= R)
    {
        sum[rt] += val * (R - L + 1);
        lazy[rt] += val;
        return;
    }
    pushdown(rt, R - L + 1);
    int mid = (L + R) >> 1;
    if (l <= mid)
        Insert(l, r, val, Lson);
    if (r > mid)
        Insert(l, r, val, Rson);
    pushup(rt);
}

ll query(int l, int r, int L, int R, int rt)
{
    if (l <= L && r >= R)
        return sum[rt];
    int mid = (L + R) >> 1;
    pushdown(rt, R - L + 1);
    ll ans = 0;
    if (l <= mid)
        ans += query(l, r, Lson);
    if (r > mid)
        ans += query(l, r, Rson);
    return ans;
}

int main()
{
    int n;
    int T;
    scanf("%d", &T);
    for (int ks = 1; ks <= T; ks++)
    {
        scanf("%d", &n);
        build(1, n, 1);
        char op[100];
        printf("Case %d:\n", ks);
        while(1)
        {
            scanf("%s", op);
            if (op[0] == 'E')
            {
                break;
            }
            if (op[0] == 'A')
            {
                int l, r;
                ll val;
                scanf("%d%lld", &l, &val);
                Insert(l, l, val, 1, n, 1);
            }
            if (op[0] == 'S')
            {
                int l, r;
                ll val;
                scanf("%d%lld", &l, &val);
                Insert(l, l, -val, 1, n, 1);
            }
            if (op[0] == 'Q')
            {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(l, r, 1, n, 1));
            }
        }
    }
    return 0;
}
