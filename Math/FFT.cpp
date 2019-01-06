/*
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
const int N = 36000 * 2 + 5;
const double PI = acos(-1.0);

struct Complex
{
	double x, y;
	Complex(double _x = 0, double _y = 0)
	{
		x = _x, y = _y;
	}
	Complex operator - (const Complex& b) const
	{
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex& b) const
	{
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex &b) const
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

Complex x1[N], x2[N];
int suf[30005], pre[30005];
int a[N];

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

template<class T>
void write(T ret)
{
	if (ret < 0)
		putchar('-'), ret = -ret;
	if (ret >= 10)
		write(ret / 10);
	putchar('0' + ret % 10);
}

void solve(int qua)
{
	int n = 1;
	memset(suf, 0, sizeof(suf));
	memset(pre, 0, sizeof(pre));
	int mx = 1;
	for (int i = 1; i <= qua; i++)
	{
		read(a[i]);
		suf[a[i]]++;
		mx = max(mx, a[i]);
	}
	while (n <= mx * 2)
		n *= 2;
	int lenb = (int)sqrt(qua * 1.0) * 5;
	ll ans = 0;
	int start = 0, end = 0;
	for (int c = 1; end < qua; c++)
	{
		start = (c - 1) * lenb + 1, end = min(c * lenb, qua);
		for (int j = start; j <= end; j++)
		{
			suf[a[j]]--;
			for (int i = start; i < j; i++)
			{
				if (2 * a[j] - a[i] > mx || 2 * a[j] - a[i] <= 0)
					continue;
				ans += suf[2 * a[j] - a[i]];
			}
			for (int k = j + 1; k <= end; k++)
			{
				if (2 * a[j] - a[k] > mx || 2 * a[j] - a[k] <= 0)
					continue;
				ans += pre[2 * a[j] - a[k]];
			}
		}
		for (int i = 0; i <= mx; i++)
			x1[i] = Complex(pre[i], 0);
		for (int i = mx + 1; i < n; i++)
			x1[i] = Complex(0, 0);
		for (int i = 0; i <= mx; i++)
			x2[i] = Complex(suf[i], 0);
		for (int i = mx + 1; i < n; i++)
			x2[i] = Complex(0, 0);
		fft(x1, n, 1);
		fft(x2, n, 1);
		for (int i = 0; i < n; i++)
			x1[i] = x1[i] * x2[i];
		fft(x1, n, -1);
		for (int j = start; j <= end; j++)
		{
			if (a[j] * 2 >= n)
				continue;
			ans += (ll)(x1[2 * a[j]].x + 0.5);
		}
		for (int i = start; i <= end; i++)
		{
			pre[a[i]]++;
		}
	}
	
	printf("%lld\n", ans);
}

int main()
{
	int qua;
	while (scanf("%d", &qua) != EOF)
		solve(qua);
	return 0;
}
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const double PI = acos(-1.0);
struct Complex
{
	double x, y;
	Complex(double _x = 0, double _y = 0)
	{
		x = _x, y = _y;
	}
	Complex operator - (const Complex& b) const
	{
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex& b) const
	{
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex &b) const
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
const int MAXN = 200010;
Complex x1[MAXN], x2[MAXN];
char str1[MAXN / 2], str2[MAXN / 2];
int sum[MAXN];
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
    while (scanf("%s%s", str1, str2) == 2)
    {
        int len1 = strlen(str1), len2 = strlen(str2);
        int len = 1;
        while (len < len1 * 2 || len < len2 * 2)
            len <<= 1;
        for (int i = 0; i < len1; i++)
            x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
        for (int i = len1; i < len; i++)
            x1[i] = Complex(0, 0);
        for (int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len - i - 1] - '0', 0);
        for (int i = len2; i < len; i++)
            x2[i] = Complex(0, 0);
        fft(x1, len, 1); fft(x2, len, 1);
        for (int i = 0; i < len; i++)
            x1[i] = x1[i] * x2[i];
        fft(x1, len, -1);
        for (int i = 0; i < len; i++)
            sum[i] = (int)(x1[i].x + 0.5);
        for (int i = 0; i < len; i++)
        {
            sum[i + 1] += sum[i] / 10;
            sum[i] %= 10;
        }
        len = len1 + len2 - 1;
        while (sum[len] <= 0 && len > 0)
            len--;
        for (int i = len; i >= 0; i--)
            putchar('0' + sum[i]);
        putchar('\n');
    }
    return 0;
}
