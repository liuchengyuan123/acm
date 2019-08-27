/×
//from https://www.cnblogs.com/TSHugh/p/9265155.html 
//在FP中求固定项数数列的线性递推式
//此递推式严格符合数学定义,故可能在末尾出现一些看起来奇怪但是在数学上必要的0,虽然这些0可能在实际操作时没有用处
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
typedef long long LL;
const int N=10010;
const int P=65521;
inline int Pow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=(LL)ret*x%P;
        x=(LL)x*x%P;y>>=1;
    }
    return ret;
}
int n,a[N],pos,len,wa[N],cnt,cur[N],tmp[N];
int main(){
    int i,j,x,s;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        scanf("%d",a+i);
    for(i=1;i<=n;++i)
        if(a[i])
            break;
    if(i==n+1)
        return 0;
    pos=i;
    len=1;
    wa[1]=Pow(a[i],P-2);
    cnt=i;
    for(++i;i<=n;++i){
        s=0;
        for(j=1;j<=cnt;++j)
        s=(s+(LL)a[i-j]*cur[j])%P;
        s=(s+P-a[i])%P;
        if(s==0)continue;
        memcpy(tmp,cur,cnt+1<<2);
        for(j=1;j<=len;++j)
        cur[i-pos+j-1]=(cur[i-pos+j-1]+(LL)wa[j]*(P-s))%P;
        wa[1]=P-1;
        for(j=1;j<=cnt;++j)
        wa[j+1]=tmp[j];
        x=len;
        len=cnt+1;
        s=Pow(s,P-2);
        for(j=1;j<=len;++j)
        wa[j]=(LL)wa[j]*s%P;
        cnt=std::max(cnt,i-pos+x-1);
        pos=i;
    }
    for(i=1;i<=cnt;++i)
        printf("%d ",cur[i]);
    puts("");
    return 0;
}
×/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef ONLINE_JUDGE
#define dbg(x...) do{cout << "\033[33;1m" << #x << "->" ; err(x);} while (0)
void err(){cout << "\033[39;0m" << endl;}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x){for (auto v: a) cout << v << ' '; err(x...);}
template<typename T, typename... A>
void err(T a, A... x){cout << a << ' '; err(x...);}
#else
#define dbg(...)
#endif
#define inf 1ll << 50
const int N = 1e5+ 5;
//#define rep(i,a,n) for (int i=a;i<n;i++)
//#define per(i,a,n) for (int i=n-1;i>=a;i--)
//#define pb push_back
//#define mp make_pair
//#define all(x) (x).begin(),(x).end()
//#define fi first
//#define se second
//#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;        //修改成题目要求的模数
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll Pow(ll a, ll b)
{
	ll ans = 1;
	a %= mod;
	assert(b >= 0);
	while (b)
	{
		if (b & 1)
			ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}
// head
namespace linear_seq
{
    const int N = 10010;
    ll res[N], base[N], _c[N], _md[N];
    vector<int> Md;
	inline int SZ(vector<int> x)
	{
		return (int)x.size();
	}
    void mul(ll *a, ll *b, int k) 
	{
		for (int i = 0; i < k + k; i++)
			_c[i] = 0;
        //rep(i,0,k+k) _c[i]=0;
        //rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
		for (int i = 0; i < k; i++)
			if (a[i])
				for (int j = 0; j < k; j++)
					_c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
        for (int i = k + k - 1; i >= k; i--) 
			if (_c[i])
            	for (int j = 0; j < SZ(Md); j++) 
					_c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
        for (int i = 0; i < k; i++) 
			a[i] = _c[i];
    }
    int solve(ll n, vector<int> a, vector<int> b) 
	{ // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
        //        printf("%d\n",SZ(b));
        ll ans = 0, pnt = 0;
        int k = SZ(a);
        assert(SZ(a) == SZ(b));
        //rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
		for (int i = 0; i < k; i++)
			_md[k - 1 - i] = -a[i];
		_md[k] = 1;
        Md.clear();
        //rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
		for (int i = 0; i < k; i++)
			if (_md[i] != 0)
				Md.push_back(i);
        //rep(i,0,k) res[i]=base[i]=0;
		for (int i = 0; i < k; i++)
			res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n)
			pnt++;
        for (int p = pnt; p >= 0; p--) 
		{
            mul(res, res, k);
            if ((n >> p) & 1) 
			{
                for (int i = k - 1; i >= 0; i--) 
					res[i + 1] = res[i];
				res[0] = 0;
                //rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
				for (int j = 0; j < SZ(Md); j++)
					res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
            }
        }
        //rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
		for (int i = 0; i < k; i++)
			ans = (ans + res[i] * b[i]) % mod;
        if (ans < 0) 
			ans+=mod;
        return ans;
    }
    vector<int> BM(vector<int> s) 
	{
        vector<int> C(1,1),B(1,1);
        int L = 0, m = 1, b = 1;
        for (int n = 0; n < SZ(s); n++) 
		{
            ll d = 0;
            for (int i = 0; i < L + 1; i++) 
				d = (d + (ll)C[i] * s[n-i]) % mod;
            if (d==0) 
				++m;
            else if (2 * L <= n)
			{
                vector<int> T = C;
                ll c = mod - d * Pow(b, mod - 2) % mod;
                while (SZ(C) < SZ(B) + m) 
					C.push_back(0);
                for (int i = 0; i < SZ(B); i++) 
					C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L; 
				B = T; 
				b = d; 
				m=1;
            } 
			else 
			{
                ll c = mod - d * Pow(b, mod - 2) % mod;
                while (SZ(C) < SZ(B) + m) 
					C.push_back(0);
                for (int i = 0; i < SZ(B); i++) 
					C[i + m] = (C[i + m] + c * B[i]) % mod;
                ++m;
            }
        }
        return C;
    }
    int gao(vector<int> a,ll n) 
	{
        vector<int> c = BM(a);
        c.erase(c.begin());
        for (int i = 0; i < SZ(c); i++) 
			c[i] = (mod - c[i]) % mod;
		dbg(SZ(c));
        return solve(n, c, vector<int> (a.begin(), a.begin() + SZ(c)));
    }
};
int main()
{
	int n;
    while (~scanf("%d",&n))
    {
        vector<int>v;       //输入前几项(一般2k项足够)
        v.push_back(1);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(5);
        v.push_back(8);
        //VI{1,1,2,3,5,8}		解出斐波那契数列
        printf("i:%d  arr:%d\n",n,linear_seq::gao(v,n-1));
    }
}
