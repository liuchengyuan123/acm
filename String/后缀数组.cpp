
//POJ1743

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 20010;
int t1[N], t2[N], c[N];

bool cmp(int *r, int a, int b, int l)
{
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int str[], int sa[], int rank[], int height[], int n, int m)
{
	n++;
	int *x = t1, *y = t2, p;
	for (int i = 0; i < m; i++)
		c[i] = 0;
	for (int i = 0; i < n; i++)
		c[x[i] = str[i]]++;
	for (int i = 1; i < m; i++)
		c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; i--)
		sa[--c[x[i]]] = i;
	for (int j = 1; j <= n; j <<= 1)
	{
		p = 0;
		for (int i = n - j; i < n; i++)
		{
			y[p++] = i;
		}
		for (int i = 0; i < n; i++)
			if (sa[i] >= j)
				y[p++] = sa[i] - j;
		for (int i = 0; i < m; i++)
			c[i] = 0;
		for (int i = 0; i < n; i++)
			c[x[y[i]]]++;
		for (int i = 1; i < m; i++)
			c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; i--)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		for (int i = 1; i < n; i++)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
		if (p >= n)
			break;
		m = p;
	}
	int k = 0;
	n--;
	for (int i = 0; i <= n; i++)
		rank[sa[i]] = i;
	for (int i = 0; i < n; i++)
	{
		if (k)
			k--;
		int j = sa[rank[i] - 1];
		while (str[i + k] == str[j + k])
			k++;
		height[rank[i]] = k;
	}
}
int Rank[N], height[N], sa[N];
int r[N];
int num[N];

int solve(int n)
{
	int low, high, minn, maxx;
	high = n / 2;
	low = 0;
	while (low <= high)
	{
		minn = maxx = sa[1];
		int mid = (low + high) >> 1;
		bool f = false;
		for (int i = 2; i <= n; i++)
		{
			if (height[i] < mid)
				minn = maxx = sa[i];
			else
			{
				minn = min(sa[i], minn);
				maxx = max(maxx, sa[i]);
				if (maxx - minn >= mid)
				{
					f = true;
					break;
				}
			}
		}
		if (f)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return high >= 4 ? high + 1 : 0;
}

int main()
{
	int n;
	while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; i++)
			scanf("%d", &num[i]);
		if (n < 10)
		{
			puts("0");
			continue;
		}
		for (int i = 0; i < n - 1; i++)
			r[i] = num[i + 1] - num[i] + 100;
		r[n-1] = 0;
		n--;
		da(r, sa, Rank, height, n, 200);
		printf("%d\n", solve(n));
	}
	return 0;
}
