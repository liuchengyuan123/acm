//最讨厌模拟了QAQ

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 5;

ll a[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    ll ans = 0;
    a[0] = 0;
    int now = 1;
    
    ll lack = 0, exceed = 0;

    while (now <= n)
    {
        int cnt = 1;
        while (now + 1 <=  n && a[now + 1] == a[now])
            now++, cnt++;
        ll tmp = max(cnt * 1ll, a[now] - a[now - cnt]);
        if (a[now] - a[now - cnt] > cnt)
        {
            exceed += a[now] - a[now - cnt] - cnt;
        }
        else
        {
            lack += cnt - a[now] + a[now - cnt];
            if (exceed >= lack)
            {
                tmp -= lack;
                exceed -= lack;
                lack = 0;
            }
            else
            {
                tmp -= exceed;
                lack = 0;
                exceed = 0;
            }
        }
        ans += a[now] * cnt - tmp;
        //printf("%d %d %lld\n", now, cnt, ans);
        now++;
    }
    printf("%lld\n", ans);
    return 0;
}
