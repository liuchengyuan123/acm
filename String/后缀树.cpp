#include<bits/stdc++.h>
using namespace std;
const int N = 100005;

struct Palindrome_Tree
{
    int n, sz, last;
    int ch[N][26], fail[N], cnt[N], len[N], s[N];

    int new_node(int x)
    {
        for (int i = 0; i < 26; i++)
            ch[x][i] = 0;
        cnt[sz] = 0;
        len[sz] = x;
        return sz++;
    }

    void init()
    {
        sz = 0;
        new_node(0), new_node(-1);
        last = 0;
        n = 0;
        s[0] = -1, fail[0] = 1;
        fail[1] = 0, s[1] = 0;
    }

    int get_fail(int u)
    {
        while (s[n - len[u] - 1] != s[n])
            u = fail[u];
        return u;
    }

    void add(int c)
    {
        c -= 'a';
        s[++n] = c;
        int u = get_fail(last);
        if (!ch[u][c])
        {
            int np = new_node(len[u] + 2);
            fail[np] = ch[get_fail(fail[u])][c];
            ch[u][c] = np;
        }
        last = ch[u][c];
        cnt[last]++;
    }

    void counnt()
    {
        for (int i = sz - 1; i >= 0; i--)
            cnt[fail[i]] += cnt[i];
    }

};

Palindrome_Tree pt;
char s[N];

int main()
{
    scanf("%s", s);
    pt.init();
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        pt.add(s[i]);
    pt.counnt();
    return 0;
}
