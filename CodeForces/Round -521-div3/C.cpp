#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
#define ll long long
struct node
{
    int id, val;
    bool operator < (const node& a) const
    {
        return val < a.val;
    }
}a[N];

int main()
{
    int n;
    scanf("%d", &n);
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].val);
        sum += a[i].val;
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    set<int> ans;
    ans.clear();
    int cnt = 0;

    for (int i = 1; i <= n; i++)
    {
        ll tmp = sum - a[i].val;
        if (tmp & 1)
            continue;
        tmp = tmp / 2;
        node cmp;
        cmp.val = tmp;
        int pos = lower_bound(a + 1, a + n + 1, cmp) - a;
        if (pos == i)
            pos++;
        if (a[pos].val == tmp)
            ans.insert(a[i].id), cnt++;
    }
    printf("%d\n", cnt);
    for (auto &t : ans)
        printf("%d ", t);
    putchar('\n');
    return 0;
}
