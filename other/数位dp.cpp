/*
https://ac.nowcoder.com/acm/contest/318/L
*/

#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long

int p[7];
int tot;

struct node
{
    bool valid;
    ll cnt, sum, sqsum;
    node(ll _cnt = 0, ll _sum = 0, ll _sqsum = 0, bool v = false): cnt(_cnt), sum(_sum), sqsum(_sqsum), valid(v) {}
};
node dp[8][10];
ll ten[10];

node dfs(int pos, bool limit, int ret)
{
    if (pos == -1)
    {
        if (ret % 6 == 0)
        {
            return node(0, 0, 0, 1);
        }
        else
        {
            return node(1, 0, 0, 1);
        }
    }
    if (!limit && dp[pos][ret].valid)
        return dp[pos][ret];
    int up = limit? p[pos]: 9;
    node cur;
    cur.cnt = 0, cur.sqsum = 0, cur.sum = 0, cur.valid = true;
    for (int i = 0; i <= up; i++)
    {
        if (i == 6)
            continue;
        node tmp = dfs(pos - 1, i == up && limit, (ret * 10 + i) % 6);
        cur.cnt += tmp.cnt;
        cur.sum += tmp.sum + ten[pos] * i * tmp.cnt;
        cur.sqsum = cur.sqsum + tmp.sqsum + 2 * ten[pos] * i * tmp.sum + tmp.cnt * ten[pos] * ten[pos] * i * i;
    }
    if (!limit)
        dp[pos][ret] = cur;
    return cur;
}

int main()
{
    ten[0] = 1;
    for (int i = 1; i <= 9; i++)
    {
        ten[i] = ten[i - 1] * 10;
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        tot = 0;
        int t = n;
        while (t)
        {
            p[tot++] = t % 10;
            t /= 10;
        }
        node ans = dfs(tot - 1, true, 0);
        printf("%llu\n", ans.sqsum);
    }
    return 0;
}
