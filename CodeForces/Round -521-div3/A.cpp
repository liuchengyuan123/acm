/*
Author: Lcy
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll a, b, k;
        scanf("%lld%lld%lld", &a, &b, &k);
        if (k & 1)
        {
            printf("%lld\n", (k - 1) / 2 * (a - b) + a);
        }
        else
        {
            printf("%lld\n", k / 2 * (a - b));
        }
    }
    return 0;
}
