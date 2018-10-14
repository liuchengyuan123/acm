//51nod 1244
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6 + 5;
int prime[348518];
bool vis[N];
int miu[N];
int tot = 0;
typedef long long ll;
void get_miu()
{
    miu[1] = 1;
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= 5e6; i++)
    {
        if(!vis[i])
        {
            prime[++tot] = i;
            miu[i] = -1;
        }
        for(int j = 1; j <= tot && i * prime[j] <= 5e6; j++)
        {
            vis[i * prime[j]] = true;
            if(i % prime[j] == 0)
            {
                miu[i * prime[j]] = 0;
                break;
            }
            miu[i * prime[j]] = -miu[i];
        }
        //cout << miu[i] << endl;
    }
}
int up = 5e6;
template <class T>
void read(T &ret)
{
    ret = 0;
    char c;
    while((c = getchar()) < '0' || c > '9');
    while(c <= '9' && c >= '0')
    {
        ret = ret * 10 + c - '0';
        c = getchar();
    }
}
map<ll,int> Miu;
ll calmiu(ll n)
{
    if(n <= up)
    {
        return miu[n];
    }
    map<ll,int> :: iterator it = Miu.find(n);
    if(it != Miu.end())
        return it->second;
    ll ans = 1;
    for(ll l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans -= (r - l + 1) * calmiu(n / l);
    }
    return Miu[n] = ans;
}

int main()
{
    get_miu();
    ll ans = 0;
    ll a, b;
    miu[0] = 0;
    for(int i = 1; i <= up; i++)
        miu[i] += miu[i - 1];
    read(a), read(b);
    ans = calmiu(b) - calmiu(a - 1);
    /*
    for(int i = 1; i <= 10; i++)
    {
        printf("%d ***\n", miu[i]);
    }
    */
    cout << ans << endl;
    return 0;
}
