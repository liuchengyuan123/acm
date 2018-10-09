
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 2e6 + 5;
int Next[N];
char t[N];
int n;

void getNext()
{
	int i, j;
	j = Next[0] = -1;
	i = 0;
	while (i < n)
	{
		while (j != -1 && t[i] != t[j])
			j = Next[j];
		Next[++i] = ++j;
	}
}

int main()
{
	while (scanf("%s", t), t[0] != '.')
	{
		n = strlen(t);
		getNext();
		int lh = n - Next[n];
		if (n%lh == 0)
			printf("%d\n", n / lh);
		else
			puts("1");
	}
	return 0;
}
