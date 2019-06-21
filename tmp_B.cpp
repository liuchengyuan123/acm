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

const ll mod = 1e9 + 7;
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

template<class T>
void read(T& ret)
{
	ret = 0;
	char c;
	while ((c = getchar()) > '9' || c < '0');
	while (c >= '0' && c <= '9')
	{
		ret = ret * 10 + c - '0';
		c = getchar();
	}
}

int main()
{
	int T;
	read(T);
	while (T--)
	{
		ll n, m;
		read(n);
		read(m);
		ll ans = 0;
		ll inv3 = Pow(3, mod - 2);
		ans = Pow(2, n % (mod - 1)) - 1;
		ans = (ans + mod) % mod;
		ans = Pow(ans, m - 1) % mod * inv3 % mod;
		ans = ans * 2 % mod;
		if (n % 2 == 1)
		{
			ans = (ans + inv3 + mod) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
