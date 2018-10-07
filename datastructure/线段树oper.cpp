#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
typedef long long ll;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
ll lazy1[N * 4], lazy2[N * 4];
ll sum1[N * 4], sum2[N * 4];
int n, m;
void pushup(int rt)
{
    sum1[rt] = sum1[lson] + sum1[rson];
    sum2[rt] = sum2[lson] + sum2[rson];
}
 
void build(int L, int R, int rt)
{
    lazy1[rt] = 0;
    lazy2[rt] = 1;
    if (L == R)
    {
        scanf("%lld", &sum1[rt]);
        sum2[rt] = sum1[rt] * sum1[rt];
        return;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}
void pushdown(int rt, int len)
{
    if (lazy1[rt] || lazy2[rt] > 1)
    {
        sum2[lson] = sum2[lson] * lazy2[rt] * lazy2[rt] + sum1[lson] * lazy2[rt] * 2 * lazy1[rt] + lazy1[rt] * lazy1[rt] * (len - (len >> 1));
        sum2[rson] = sum2[rson] * lazy2[rt] * lazy2[rt] + sum1[rson] * lazy2[rt] * 2 * lazy1[rt] + lazy1[rt] * lazy1[rt] * (len >> 1);
        sum1[lson] = sum1[lson] * lazy2[rt] + lazy1[rt] * (len - (len >> 1));
        sum1[rson] = sum1[rson] * lazy2[rt] + lazy1[rt] * (len >> 1);
        lazy1[lson] = lazy1[lson] * lazy2[rt] + lazy1[rt];
        lazy1[rson] = lazy1[rson] * lazy2[rt] + lazy1[rt];
        lazy2[lson] *= lazy2[rt];
        lazy2[rson] *= lazy2[rt];
        lazy1[rt] = 0;
        lazy2[rt] = 1;
    }
}
 
void update1(int l, int r, ll val, int L, int R, int rt)
{
    if (l <= L && r >= R)
    {
        sum2[rt] += val * val * (R - L + 1) + 2 * val * sum1[rt];
        sum1[rt] += val * (R - L + 1);
        lazy1[rt] += val;
        return;
    }
    pushdown(rt, R - L + 1);
    int mid = (L + R) >> 1;
    if (l <= mid)
        update1(l, r, val, Lson);
    if (r > mid)
        update1(l, r, val, Rson);
    pushup(rt);
}
 
void update2(int l, int r, ll val, int L, int R, int rt)
{
    if (l <= L && r >= R)
    {
        sum2[rt] *= val * val;
        sum1[rt] *= val;
        lazy1[rt] *= val;
        lazy2[rt] *= val;
        return;
    }
    pushdown(rt, R - L + 1);
    int mid = (L + R) >> 1;
    if (l <= mid)
        update2(l, r, val, Lson);
    if (r > mid)
        update2(l, r, val, Rson);
    pushup(rt);
}
 
ll query1(int l, int r, int L, int R, int rt)
{
    if (l <= L && r >= R)
        return sum1[rt];
    int mid = (L + R) >> 1;
    pushdown(rt, R - L + 1);
    ll ans = 0;
    if (l <= mid)
        ans += query1(l, r, Lson);
    if (r > mid)
        ans += query1(l, r, Rson);
    return ans;
}
 
ll query2(int l, int r, int L, int R, int rt)
{
    if (l <= L && r >= R)
        return sum2[rt];
    int mid = (L + R) >> 1;
    pushdown(rt, R - L + 1);
    ll ans = 0;
    if (l <= mid)
        ans += query2(l, r, Lson);
    if (r > mid)
        ans += query2(l, r, Rson);
    return ans;
}
int main()
{
    int n, m;

    scanf("%d%d", &n, &m);
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1)
        {
            printf("%lld\n", query1(l, r, 1, n, 1));
        }
        if (op == 2)
        {
            printf("%lld\n", query2(l, r, 1, n, 1));
        }
        if (op == 3)
        {
            ll v;
            scanf("%lld", &v);
            update2(l, r, v, 1, n, 1);
        }
        if (op == 4)
        {
            ll v;
            scanf("%lld", &v);
            update1(l, r, v, 1, n, 1);
        }
    }

    return 0;
}
