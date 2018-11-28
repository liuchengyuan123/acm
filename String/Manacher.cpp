
//HDU-3068
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 110005;
char s[N * 2];
char ma[2 * N];
int mp[N * 2];
int n;

void manacher()
{
	int l = 0;
	ma[l++] = '$';
	ma[l++] = '#';
	for (int i = 0; i < n; i++)
	{
		ma[l++] = s[i];
		ma[l++] = '#';
	}
	ma[l] = 0;
	int mx = 0, id = 0;
	for (int i = 0; i < l; i++)
	{
		mp[i] = mx > i ? min(mp[2 * id - i], mx - i) : 1;
		while (ma[i + mp[i]] == ma[i - mp[i]])
			mp[i]++;
		if (i + mp[i] > mx)
		{
			mx = i + mp[i];
			id = i;
		}
	}
}

int main()
{
	while (scanf("%s", s) != EOF)
	{
		n = strlen(s);
		manacher();
		int ans = 0;
		for (int i = 0; i < 2 * n; i++)
		{
			ans = max(ans, mp[i]);
		}
		printf("%d\n", ans - 1);
	}
	return 0;
}
