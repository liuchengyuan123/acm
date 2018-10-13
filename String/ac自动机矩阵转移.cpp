//Text Generator
#include<bits/stdc++.h>
using namespace std;
const int N = 70;
const int mod = 10007;
int root, sz;
int fail[N];
int ch[N][26];
int ed[N];

void init()
{
	root = sz = 0;
	for (int i = 0; i < 26; i++)
		ch[root][i] = 0;
	ed[root] = 0;
	fail[root] = root;
}

int newnode()
{
	sz++;
	for (int i = 0; i < 26; i++)
	{
		ch[sz][i] = 0;
	}
	fail[sz] = 0;
	ed[sz] = 0;
	return sz;
}

void insert(char buf[])
{
	int now = root;
	int len = strlen(buf);
	for (int i = 0; i < len; i++)
	{
		if (!ch[now][buf[i] - 'A'])
		{
			ch[now][buf[i] - 'A'] = newnode();
		}
		now = ch[now][buf[i] - 'A'];
	}
	ed[now] = 1;
}

void getfail()
{
	queue<int> q;
	for (int i = 0; i < 26; i++)
	{
		if (ch[root][i])
		{
			int u = ch[root][i];
			fail[u] = root;
			q.push(u);
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
		{
			int v = ch[u][i];
			if (!v)
			{
				ch[u][i] = ch[fail[u]][i];
				continue;
			}
			int tmp = fail[u];
			while (tmp != root && !ch[tmp][i])
				tmp = fail[tmp];
			fail[v] = ch[tmp][i];
			ed[v] |= ed[fail[v]];
		}
	}
}

struct matrix
{
	int a[N][N];
	int* operator [] (int i)
	{
		return a[i];
	}
	matrix()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				a[i][j] = 0;
			}
		}
	}
};

matrix mult(matrix a, matrix b)
{
	matrix ans;
	for (int i = 0; i <= sz; i++)
	{
		for (int j = 0; j <= sz; j++)
		{
			for (int k = 0; k <= sz; k++)
			{
				ans[i][j] += a[i][k] * b[k][j] % mod;
				ans[i][j] %= mod;
			}
		}
	}
	return ans;
}

matrix powmat(matrix a, int b)
{
	matrix ans;
	for (int i = 0; i <= sz; i++)
	{
		ans[i][i] = 1;
	}
	while (b)
	{
		if (b & 1)
		{
			ans = mult(ans, a);
		}
		a = mult(a, a);
		b >>= 1;
	}
	return ans;
}

int pownum(int a, int b)
{
	int ans = 1;
	a %= mod;
	while (b)
	{
		if (b & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

void getbase(matrix &a)
{
	for (int node = 0; node <= sz; node++)
	{
		for (int c = 0; c < 26; c++)
		{
			if (!ed[ch[node][c]])
			{
				a[node][ch[node][c]]++;
			}
		}
	}
}

char s[10];

int main()
{
	int n;
	int l;
	while (scanf("%d%d", &n, &l) != EOF)
	{
		init();
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s);
			insert(s);
		}
		getfail();
		int tot = pownum(26, l);
		matrix a;
		getbase(a);
		
		matrix ans = powmat(a, l);
		int sum = 0;
		for (int i = 0; i <= sz; i++)
		{
			sum = (sum + ans[0][i]) % mod;
		}
		printf("%d\n", (tot - sum + mod) % mod);
	}
	return 0;
}
