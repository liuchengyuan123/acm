#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int fa[N];
int find(int x)
{
    if (x == fa[x])
        return x;
    return x = find(fa[x]);
}
void merge(int a, int b)
{
    a = find(a), b = find(b);
    if (a == b)
        return;
    fa[a] = b;
}
