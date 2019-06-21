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
const int N = 1e5 + 5;
int prime[10000];
int tot;
bool vis[N];
ll miu[N];
void pre(int n)
{
	tot = 0;
	miu[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
			prime[++tot] = i, miu[i] = -1;
		for (int j = 1; j <= tot && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				miu[i * prime[j]] = 0;
				break;
			}
			miu[i * prime[j]] = -miu[i];
		}
	}
}
ll cnt[N];
int a[N];
const ll mod = 1e9 + 7;
ll f[N];
ll Pow(ll a, ll b)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
int main()
{
	int n;
	pre(100000);
	int T;
	scanf("%d", &T);
	for (int ks = 1; ks <= T; ks++)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i <= 100000; i++)
			cnt[i] = 0;
		int mnv = 0x3f3f3f3f, mxv = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			mnv = min(mnv, a[i]);
			mxv = max(mxv, a[i]);
			cnt[a[i]]++;
		}
		if (mnv <= 1)
		{
			printf("Case #%d: %lld\n", ks, 0ll);
			continue;
		}
		for (int i = 1; i <= mxv; i++)
			cnt[i] = cnt[i] + cnt[i - 1];
		ll ans = 0;
		int j;
		for (int i = 0; i <= mxv; i++)
			f[i] = 0ll;
		for (int i = 2; i <= mnv; i++)
		{
			f[i] = 1ll;
			for (int l = i; l <= mxv; l += i)
			{
				//f[i] = f[i] * (cnt[min(l + i - 1, mxv)] - cnt[l - 1] + mod) % mod * (l / i) % mod;
				f[i] = f[i] * Pow(1ll * l / i, cnt[min(l + i - 1, mxv)] - cnt[l - 1]) % mod;
			}
			//dbg(i, f[i]);
			/*
			for (int j = i; j <= mxv; j++)
			{
				f[i] = f[i] * Pow(j / i, cnt[j]) % mod;
			}
			*/
		}
		for (int i = 2; i <= mnv; i++)
		{
			for (int d = i; d <= mxv; d += i)
				ans = (ans + f[d] * miu[d / i] % mod + mod) % mod;
		}
		printf("Case #%d: %lld\n", ks, ans);
	}
	return 0;
}
