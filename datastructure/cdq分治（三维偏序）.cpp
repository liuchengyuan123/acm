#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int K = 2e5 + 5;
int n, k;
int tot;
#define ll long long

int sum[K];

int lowbit(int x)
{
    return x & (-x);
}
void update(int x, int val)
{
    while (x <= k + 1)
    {
        sum[x] += val;
        x += lowbit(x);
    }
}
int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans += sum[x];
        x -= lowbit(x);
    }
    return ans;
}

struct node
{
    int a, b, c;
    int id, wei;
    bool operator < (const node& un) const
    {
        if (a != un.a)
            return a < un.a;
        if (b != un.b)
            return b < un.b;
        return c < un.c;
    }
    node(int _a = 0, int _b = 0, int _c = 0, int _id = 0, int _wei = 0) : a(_a), b(_b), c(_c), id(_id), wei(_wei) {}
}A[N], B[N];

int ans[N];
int cnt[N];
int myset[N];

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = l + r >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int setot = 0;
    int t1 = l, t2 = mid + 1;
    for (int i = l; i <= r; i++)
    {
        if (t2 > r || (t1 <= mid && A[t1].b <= A[t2].b))
        {
            update(A[t1].c, A[t1].wei);
            B[i] = A[t1++];
            myset[++setot] = i;
        }
        else
        {
            ans[A[t2].id] += query(A[t2].c);
            B[i] = A[t2++];
        }
    }
    for (int i = l; i <= r; i++)
        A[i] = B[i];
    for (int i = 1; i <= setot; i++)
        update(B[myset[i]].c, -B[myset[i]].wei);
}

int main()
{
    
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif // ONLINE_JUDGE
    
    tot = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &A[i].a, &A[i].b, &A[i].c);
        A[i].a++, A[i].b++, A[i].c++;
        A[i].id = i;
    }
    memset(ans, 0, sizeof(ans));
    sort(A + 1, A + n + 1);
    A[0].a = -1;
    for (int i = 1; i <= n; i++)
    {
        if (A[i].a != A[i - 1].a || A[i].b != A[i - 1].b || A[i].c != A[i - 1].c)
        {
            A[++tot] = A[i];
            A[tot].wei = 1;
        }
        else
        {
            A[tot].wei++;
        }
    }
    cdq(1, tot);
    memset(cnt, 0, sizeof(cnt));
    /*
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", A[i].id, ans[A[i].id]);
        */
    for (int i = 1; i <= tot; i++)
    {
        cnt[ans[A[i].id] + A[i].wei - 1] += A[i].wei;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", cnt[i]);
    }
    return 0;
}
