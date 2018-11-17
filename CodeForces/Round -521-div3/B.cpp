#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int ok[N];
int a[N];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		ok[i] = 1;
		scanf("%d", &a[i]);
	}
	for (int i = 2; i < n; i++)
	{
		if (a[i] == 0 && a[i - 1] == 1 && a[i + 1] == 1)
			ok[i] = 0;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (i - 1 > 0 && i + 1 <= n && a[i] == 1 && a[i - 1] == 0 && a[i + 1] == 0 && !ok[i - 1] && !ok[i + 1])
		{
			cnt++;
			ok[i - 1] = 1;
			ok[i + 1] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (i + 1 <= n && !ok[i + 1])
		{
			cnt++;
			ok[i + 1] = 1;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
