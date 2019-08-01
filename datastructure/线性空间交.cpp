//https://ac.nowcoder.com/acm/contest/884/B

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
typedef unsigned int ui;
const int N = 5e4 + 5;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
ui base[N << 4][33];

bool insert(int c, ui x)
{
	for (int i = 31; i >= 0; i--)
		if ((x >> i) & 1)
		{
			//dbg(i, base[c][i], x);
			if (base[c][i])
			{
				x ^= base[c][i];
				if (x == 0)
					return 1;
			}
			else
			{
				base[c][i] = x;
				return 0;
			}
		}
	return x == 0;
}
int tot[33], tmp[33];
void merge(int a, int b, int c)
{
	//puts("Merge!!!!!!");
	//dbg(a, b, c);
	for(int i = 0; i < 32; i++)
	{
		//dbg(base[a][i]);
		tot[i] = base[a][i];
		tmp[i] = base[a][i];
		base[c][i] = 0;
	}
    for(int i = 0; i < 32; i++)
        if (base[b][i])
		{
            ui cur = base[b][i], add = 0;
            for (int j = i; j >= 0; j--)
                if ((cur >> j) & 1)
				{
					//dbg(j, tot[j], cur, add, tmp[j]);
                    if (tot[j])
					{
                        cur ^= tot[j];
                        add ^= tmp[j];
						//dbg(cur, add);
                        if (!cur)
						{
                            base[c][i] = add;
							//dbg(base[c][i]);
                            break;
                        }
                    }
					else
					{
                        tot[j] = cur;
                        tmp[j] = add;
                        break;
                    }
                }
        }
}
int siz;
void push_up(int rt)
{
	merge(lson, rson, rt);
}

template<class T>
void read(T& ret)
{
	ret = 0;
	char c;
	while ((c = getchar()) < '0' || c > '9');
	while (c >= '0' && c <= '9')
	{
		ret = ret * 10 + c - '0';
		c = getchar();
	}
}

void build(int L, int R, int rt)
{
	//dbg(L, R);
	if (L == R)
	{
		for (int i = 31; i >= 0; i--)
			base[rt][i] = 0;
		read(siz);
		for (int i = 1; i <= siz; i++)
		{
			ui x;
			read(x);
			insert(rt, x);
		}
		/*
		for (int i = 31; i >= 0; i--)
		{
			if (base[rt][i])
				dbg(rt, i, base[rt][i]);
		}
		*/
		return;
	}
	for (int i = 31; i >= 0; i--)
		base[rt][i] = 1 << i;
	int mid = (L + R) >> 1;
	build(Lson);
	build(Rson);
	push_up(rt);
}

bool check(int a, ui x)
{
	for (int i = 0; i < 32; i++)
	{
		base[0][i] = base[a][i];
	}
	return insert(0, x);
}

bool query(int l, int r, ui x, int L, int R, int rt)
{
	if (l <= L && r >= R)
	{
		return check(rt, x);
	}
	int mid = (L + R) >> 1;
	bool ans = 1;
	if (l <= mid)
		ans = ans && query(l, r, x, Lson);
	if (r > mid)
		ans = ans && query(l, r, x, Rson);
	return ans;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, n, 1);
	for (int q = 1; q <= m; q++)
	{
		int l, r;
		ui x;
		read(l);
		read(r);
		read(x);
		if (query(l, r, x, 1, n, 1))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
