#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int prime[N];
int tot;
int vis[N];
int miu[N];
int phi[N];
void getprime()
{
    tot = 0;
    for (int i = 2; i < N; i++)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            phi[i] = i - 1;
            miu[i] = -1;
        }
        for (int j = 1; j <= tot && i * prime[j] < N; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                miu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] / prime[j] * (prime[j] - 1);
            }
            else
            {
                miu[i * prime[j]] = -miu[i];
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
