#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
int n, m;
ll dp[2][1 << 12]; // 二维滚动数组
 
int main()
{
    while (cin >> n >> m &&(n||m))
    {
        memset(dp, 0, sizeof(dp));
        ll *cur, *next;
        cur = dp[0]; next = dp[1];
        cur[0] = 1;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                memset(dp[(i*m+j+1)&1], 0, sizeof(dp[(i*m+j+1)&1]));
                cur = dp[(i*m + j) & 1]; next = dp[(i*m + j + 1) & 1];
                for (int k = 0; k < 1 << m; k++){
                    // 如果已经放了，那就直接转移
                    if ((k >> j) & 1){
                        next[k & ~(1 << j)] += cur[k];
                    }
                    else{
                        //　尝试横放
                        if (j + 1 < m && !(k >> (j + 1) & 1)){
                            next[k | 1 << (j + 1)] += cur[k];
                        }
                        // 尝试竖放
                        if (i + 1 < n){
                            next[k | 1 << j] += cur[k];
                        }
                    }
                }
            }
        }
        printf("%lld\n", next[0]);
    }
    return 0;
}
