#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
map<int, int> mp;
priority_queue<int> pq;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        mp[x]++;
    }
    int base = 0;
    for (auto &p : mp)
    {
        pq.push(p.second);
        base = max(base, p.second);
    }
    int ans = 0;
    int c = 0;
    while (!pq.empty())
    {
        int f = pq.top();
        pq.pop();
        base = min(base, f);
        ans = max(ans, ((1 << (c + 1)) - 1) * base);
        c++;
        base /= 2;
    }
    printf("%d\n", ans);
    return 0;
}
