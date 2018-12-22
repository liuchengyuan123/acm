#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 * 3 +5;
#define ll long long
int n, m, totx, tot;
struct node
{
    int type, id;
    ll val;
    bool operator < (const node& un) const
    {
        return id == un.id? type < un.type : id < un.id;
    }
    node(int _type = 0, int _id = 0, ll _val = 0): type(_type), id(_id), val(_val) {}

}A[N], B[N];
ll ans[N];

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = l + r >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int t1 = l, t2 = mid + 1;
    ll sum = 0;
    for (int i = l; i <= r; i++)
    {
        if (t2 > r || (t1 <= mid && A[t1] < A[t2]))
        {
            if (A[t1].type == 1)
                sum += A[t1].val;
            B[i] = A[t1++];
        }
        else
        {
            if (A[t2].type == 2)
            {
                ans[A[t2].val] -= sum;
            }
            if (A[t2].type == 3)
            {
                ans[A[t2].val] += sum;
            }
            B[i] = A[t2++];
        }
    }
    for (int i = l; i <= r; i++)
        A[i] = B[i];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        A[++tot].type = 1;
        A[tot].id = i;
        scanf("%lld", &A[tot].val);
    }
    for (int i = 1; i <= m; i++)
    {
        int T;
        scanf("%d", &T);
        A[++tot].type = T;
        if (T == 1)
        {
            scanf("%d%lld", &A[tot].id, &A[tot].val);
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            A[tot].val = ++totx, A[tot].id = l - 1;
            A[++tot].val = totx, A[tot].type = 3, A[tot].id = r;
        }
    }
    memset(ans, 0, sizeof(ans));
    cdq(1, tot);
    for (int i = 1; i <= totx; i++)
    {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
