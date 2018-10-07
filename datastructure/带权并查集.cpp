//HDU3038
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int sum[N];
int fa[N];

int find(int x)
{
    if (x == fa[x])
        return x;
    int tmp = fa[x];
    fa[x] = find(fa[x]);
    sum[x] += sum[tmp];
    return fa[x];
}

void init(int n)
{
    fa[0] = 0;
    for (int i = 1; i <= n; i++)
    {   
        fa[i] = i;
        sum[i] = 0;
    }
}

int main()
{
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        int l, r;
        init(n);
        int cnt = 0;
        for (int i = 1; i <= m; i++)
        {
            int z;
            int fl, fr;
            scanf("%d%d%d", &l, &r, &z);
            l--;
            fl = find(l), fr = find(r);
            if (fl == fr)
            {
                cnt += (sum[r] != sum[l] + z);
                continue;
            }
            else
            {
                if (fl < fr)
                {
                    sum[fr] = sum[l] + z - sum[r];
                    fa[fr] = fl;
                }
                else
                {
                    sum[fl] = sum[r] - z - sum[l];
                    fa[fl] = fr;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
