#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
ll a[N];
int q[N];
int main()
{
    int n;
    int k;
    while (scanf("%d%d", &n, &k) != EOF)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        int l = 0, r = 0;
        int cur = 1;
        while (cur <= n)
        {
            while (l < r && a[cur] >= a[q[r - 1]])
                r--;
            q[r++] = cur;
            while (l < r && cur - q[l] + 1 > k)
                l++;
            if (cur >= k)
                printf("%lld%c", a[q[l]], cur == n? '\n' : ' ');
            cur++;
        }
    }
    return 0;
}
