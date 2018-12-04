#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex <double> cp;

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
void write(T& ret)
{
    if (ret < 0)
        putchar('-'), ret = -ret;
    if (ret >= 10)
        write(ret / 10);
    putchar('0' + ret % 10);
}

const int N = 1e5 + 5e4 + 5;
const double PI = acos(-1);

char sa[N], sb[N];
int n = 1, lena, lenb, res[N];
cp a[N], b[N], omg[N], inv[N];

void init()
{
    for (int i = 0; i < n; i++)
    {
        omg[i] = cp(cos(2 * PI * i / n), sin(2 * PI * i / n));
        inv[i] = conj(omg[i]);
    }
}

void fft(cp *a, cp *omg)
{
    int lim = 0;
    while ((1 << lim) < n)
        lim++;
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        for (int j = 0; j < lim; j++)
            if ((i >> j) & 1)
                t |= (1 << (lim - j - 1));
        if (i < t)
            swap(a[i], a[t]);
    }
    for (int l = 2; l <= n; l *= 2)
    {
        int m = l / 2;
        for (cp *p = a; p != a + n; p += l)
        {
            for (int i = 0; i < m; i++)
            {
                cp t = omg[n / l * i] * p[i + m];
                p[i + m] = p[i] - t;
                p[i] += t;
            }
        }
    }
}

int main()
{
    //freopen("1.txt", "r", stdin);
    //freopen("out1.txt", "w", stdout);
    while (~scanf("%s%s", sa, sb))
    {
        lena = strlen(sa), lenb = strlen(sb);
        n = 1;
        while (n < lena + lenb)
            n *= 2;
        for (int i = 0; i <= n; i++)
            a[i].real(0), a[i].imag(0), b[i].real(0), b[i].imag(0);
        memset(res, 0, sizeof(res));
        for (int i = 0; i < lena; i++)
            a[i].real(sa[lena - 1 - i] - '0');
        for (int i = 0; i < lenb; i++)
            b[i].real(sb[lenb - 1 - i] - '0');
        init();
        fft(a, omg);
        fft(b, omg);
        for (int i = 0; i < n; i++)
            a[i] *= b[i];
        fft(a, inv);
        for (int i = 0; i < n; i++)
        {
            res[i] += floor(a[i].real() / n + 0.5);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
        bool flag = 0;
        for (int i = res[lena + lenb - 1]? lena + lenb - 1: lena + lenb - 2; i >= 0; i--)
        {
            if (i > 0 && res[i] == 0 && !flag)
                continue;
            flag = 1;
            putchar(res[i] + '0');
        }
        putchar('\n');
    }
    return 0;
}
