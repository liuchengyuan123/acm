#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct node
{
    int val, cnt;

    bool operator < (const node& a) const
    {
        return cnt > a.cnt;
    }

}a[N];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 200000; i++)
    {
        a[i].val = i;
        a[i].cnt = 0;
    }
    int mx = 1;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        a[x].cnt++;
        mx = max(mx, x);
    }
    int l = 0, r = n + 1;
    int ans = 0;
    sort(a + 1, a + mx + 1);
    while (l < r)
    {
        int mid = (l + r) / 2;
        int ret = k;
        for (int i = 1; i <= mx; i++)
        {
            ret -= a[i].cnt / mid;
            if (ret <= 0)
                break;
        }
        if (ret <= 0)
        {
            ans = max(ans, mid);
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    int ret = k;
    for (int i = 1; i <= mx; i++)
    {
        
        int rep = min(ret, a[i].cnt / ans);
        for (int j = 1; j <= rep; j++)
        {
            printf("%d ", a[i].val);
        }
        ret -= rep;
        if (ret == 0)
            break;
    }
    putchar('\n');
    return 0;
}
