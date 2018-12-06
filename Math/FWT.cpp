/*
codeforces 662C
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
void FWT_or(ll *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < n; ++k)
				if (opt == 1)
					a[i + j + k] = a[j + k] + a[i + j + k];
				else
					a[i + j + k] = a[i + j + k] - a[j + k];
}
void FWT_and(ll *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < i; ++k)
				if (opt == 1)
					a[j + k] = a[j + k] + a[i + j + k];
				else
					a[j + k] = a[j + k] - a[i + j + k];
}
void FWT_xor(ll *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < i; ++k)
			{
				ll X = a[j + k], Y = a[i + j + k];
				a[j + k] = X + Y;
				a[i + j + k] = X - Y;
				if (opt == -1)
					a[j + k] = 1ll * a[j + k] / 2, a[i + j + k] = 1ll * a[i + j + k] / 2;
			}
}

int calc(int x, int n)
{
    return min(__builtin_popcount(x), n - __builtin_popcount(x));
}

const int N = 1050000;
ll a[N], b[N];
char s[25][100005];
int state[100005];

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
        memset(state, 0, sizeof(state));
		int up = (1 << n);
        for (int i = 0; i < up; i++)
        {
            a[i] = 0;
            b[i] = calc(i, n);
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                state[j] = state[j] << 1 | (s[i][j] - '0');
            }
        }
        for (int j = 0; j < m; j++)
            a[state[j]]++;
        FWT_xor(a, up, 1);
        FWT_xor(b, up, 1);
        for (int i = 0; i < up; i++)
            a[i] *= b[i];
        FWT_xor(a, up, -1);
        ll ans = 1ll << 60;
        for (int i = 0; i < up; i++)
            ans = min(ans, a[i]);
        printf("%lld\n", ans);
	}
    return 0;
}
