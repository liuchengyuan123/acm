#include<bits/stdc++.h>
using namespace std;
const int N = 100;
#define ll long long

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
    int q;
    scanf("%d", &q);
    while (q--)
    {
        ll n;
        read(n);
        printf("%lld\n", n - 1);
    }
    return 0;
}
