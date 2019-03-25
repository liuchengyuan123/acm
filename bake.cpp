#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int cnt[N];
typedef long long ll;
ll ans[2 * N];
const double PI = acos(-1.0);
struct Complex
{
	double x, y;
	Complex(double _x = 0.0, double _y = 0.0)
	{
		x = _x;
		y = _y;
	}
	Complex operator - (const Complex& b) const
	{
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex& b) const
	{
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex& b) const
	{
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};

void change(Complex y[], int len)
{
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; i++)
	{
		if (i < j)
			swap(y[i], y[j]);
		k = len / 2;
		while (j >= k)
		{
			j -= k;
			k /= 2;
		}
		if (j < k)
			j += k;
	}
}

void fft(Complex y[], int len, int on)
{
	change(y, len);
	for (int h = 2; h <= len; h <<= 1)
	{
		Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
		for (int j = 0; j < len; j += h)
		{
			Complex w(1, 0);
			for (int k = j; k < j + h / 2; k++)
			{
				Complex u = y[k];
				Complex t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1)
		for (int i = 0; i < len; i++)
			y[i].x /= len;
}

Complex x1[2 * N], x2[2 * N];

void solve(int l, int r)
{
	if (l == r)
	{
		
	}
	return;
}

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	int mxv = 0;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cnt[x]++;
		mxv = max(mxv, x);
	}
	int len = 1;
	solve(0, mxv + 1);
	for (int i = 0; i <= mxv * 2; i++)
		ans[i] = (ll)(x2[i].x + 0.5);
	ll sum = 0;
	for (int i = k; i <= mxv * 2; i += k)
	{
		sum += ans[i];
	}
	printf("%lld\n", sum);
	return 0;
}
