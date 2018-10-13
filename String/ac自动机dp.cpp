//POJ3691
#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
using namespace std;
typedef long long ll;
int sz, root;
const int N = 20 * 50 + 10;
int ch[N][4];
int fail[N];
int ed[N];

int react(char c)
{
	if (c == 'A')
		return 0;
	if (c == 'C')
		return 1;
	if (c == 'G')
		return 2;
	if (c == 'T')
		return 3;
}

void init()
{
	root = sz = 0;
	for (int i = 0; i < 4; i++)
		ch[root][i] = 0;
	fail[root] = 0;
	ed[root] = 0;
}

int newnode()
{
	int now = ++sz;
	for (int i = 0; i < 4; i++)
		ch[now][i] = 0;
	fail[now] = 0;
	ed[now] = 0;
	return sz;
}

void insert(char buf[])
{
	int now = root;
	int len = strlen(buf);
	for (int i = 0; i < len; i++)
	{
		int c = react(buf[i]);
		int x = ch[now][c];
		if (!x)
		{
			ch[now][c] = newnode();
			x = ch[now][c];
		}
		now = x;
	}
	ed[now] = 1;
}

void getfail()
{
	queue<int> q;
	for (int i = 0; i < 4; i++)
	{
		int x = ch[root][i];
		if (x)
		{
			fail[x] = root;
			q.push(x);
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int v = ch[u][i];
			if (!v)
			{
				ch[u][i] = ch[fail[u]][i];
				continue;
			}
			int tmp = fail[u];
			while (tmp && !ch[tmp][i])
				tmp = fail[tmp];
			fail[v] = ch[tmp][i];
			ed[v] |= ed[fail[v]];
			q.push(v);
		}
	}
}

int dp[N][1005];
char s[1005];
int main()
{
	int n;
	int ks = 0;
	while (scanf("%d", &n), n)
	{
		init();
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s);
			insert(s);
		}
		getfail();
		memset(dp, 0x3f3f3f3f, sizeof(dp));
		dp[root][0] = 0;
		scanf("%s", s);
		int slen = strlen(s);
		for (int i = 0; i < slen; i++)
		{
			for (int node = 0; node <= sz; node++)
			{
				for (int c = 0; c < 4; c++)
				{
					if (dp[node][i] <= 10000)
					{
						if (c == react(s[i]))
						{
							if (!ed[ch[node][c]])
								dp[ch[node][c]][i + 1] = min(dp[ch[node][c]][i + 1], dp[node][i]);
						}
						else
						{
							if (!ed[ch[node][c]])
								dp[ch[node][c]][i + 1] = min(dp[ch[node][c]][i + 1], dp[node][i] + 1);
						}
					}
				}
			}
		}
		printf("Case %d: ", ++ks);
		int still = 1, ans = 0x3f3f3f3f;
		still = ans;
		for (int i = root; i <= sz; i++)
		{
			if (dp[i][slen] <= 10000)
			{
				still = 0;
				ans = min(ans, dp[i][slen]);
			}
		}
		if (still)
		{
			puts("-1");
			continue;
		}
		printf("%d\n", ans);
	}
	return 0;
}
