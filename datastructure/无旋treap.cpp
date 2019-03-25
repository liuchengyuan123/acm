//[HYSBZ-3224]
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll seed = 17124057;
#define ls(x) treap[x].child[0]
#define rs(x) treap[x].child[1]
const int N = 1e5 + 5;
int cur = 0;
ll Rand()
{
    return seed = seed * 48271 % 2147483647;
}

struct node
{
    int val, key, child[2], size;
}treap[N];

void pushup(int root)
{
    treap[root].size = treap[ls(root)].size + treap[rs(root)].size + 1;
}

void split(int root, int& x, int& y, int val)
{
    if (!root)
    {
        x = y = 0;
        return;
    }
    if (treap[root].val <= val)
    {
        x = root;
        split(rs(root), rs(x), y, val);
    }
    else
    {
        y = root;
        split(ls(root), x, ls(y), val);
    }
    pushup(root);
}

void merge(int &root, int x, int y)
{
    if (!x || !y)
    {
        root = x + y;
        return;
    }
    if (treap[x].key < treap[y].key)
    {
        root = x;
        merge(rs(root), rs(x), y); 
    }
    else
    {
        root = y;
        merge(ls(root), x, ls(y));
    }
    pushup(root);
}

void insert(int& root, int val)
{
    int x = 0, y = 0, z = ++cur;
    treap[z].val = val;
    treap[z].size = 1;
    ls(z) = rs(z) = 0;
    treap[z].key = Rand();
    split(root, x, y, val);
    merge(x, x, z);
    merge(root, x, y);
}

void del(int& root, int val)
{
    int x = 0, y = 0, z = 0;
    split(root, x, y, val);
    split(x, x, z, val - 1);
    merge(z, ls(z), rs(z));
    merge(x, x, z);
    merge(root, x, y);
}

int query_rank(int& root, int val)
{
    int x = 0, y = 0;
    split(root, x, y, val - 1);
    int ans = treap[x].size + 1;
    merge(root, x, y);
    return ans;
}

int query_value(int root, int rnk)
{
    while (treap[ls(root)].size + 1 != rnk)
    {
        if (treap[ls(root)].size >= rnk)
        {
            root = ls(root);
        }
        else
        {
            rnk -= treap[ls(root)].size + 1;
            root = rs(root);
        }
    }
    return treap[root].val;
}

int pre_val(int& root, int val)
{
    int x = 0, y = 0;
    split(root, x, y, val - 1);
    int ans, tmp = x;
    while (rs(tmp))
        tmp = rs(tmp);
    ans = treap[tmp].val;
    merge(root, x, y);
    return ans;
}

int suf_val(int& root, int val)
{
    int x = 0, y = 0;
    split(root, x, y, val);
    int ans, tmp = y;
    while (ls(tmp))
        tmp = ls(tmp);
    ans = treap[tmp].val;
    merge(root, x, y);
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    cur = 0;
    int root = 0;
    for (int i = 1; i <= n; i++)
    {
        // printf("root %d\n", root);
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            insert(root, x);
            continue;
        }
        if (op == 2)
        {
            del(root, x);
            continue;
        }
        if (op == 3)
        {
            int ans = query_rank(root, x);
            printf("%d\n", ans);
            continue;
        }
        if (op == 4)
        {
            int ans = query_value(root, x);
            printf("%d\n", ans);
            continue;
        }
        if (op == 5)
        {
            int ans = pre_val(root, x);
            printf("%d\n", ans);
            continue;
        }
        if (op == 6)
        {
            int ans = suf_val(root, x);
            printf("%d\n", ans);
            continue;
        }
    }
    return 0;
}
