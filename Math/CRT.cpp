#include<bits/stdc++.h>
using namespace std;
#define ll long long
void exgcd(ll a,ll b,ll &x,ll &y)
{
    
}
const int N;
ll in[N], a[N], M[N];
ll CRT()
{
    ll x,ans=0,y, m = 0;
    for(int i=1;i<=n;i++)
        m*=in[i];
    for(int i=1;i<=n;i++)
    {
        M[i]=m/in[i];
        exgcd(M[i],in[i],x,y);
        ans=(ans+a[i]*x*M[i])%m;
    }
    return (ans+m)%m;
}
