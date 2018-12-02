//from https://www.cnblogs.com/TSHugh/p/9265155.html 
//在FP中求固定项数数列的线性递推式
//此递推式严格符合数学定义,故可能在末尾出现一些看起来奇怪但是在数学上必要的0,虽然这些0可能在实际操作时没有用处
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
typedef long long LL;
const int N=10010;
const int P=65521;
inline int Pow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=(LL)ret*x%P;
        x=(LL)x*x%P;y>>=1;
    }
    return ret;
}
int n,a[N],pos,len,wa[N],cnt,cur[N],tmp[N];
int main(){
    int i,j,x,s;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        scanf("%d",a+i);
    for(i=1;i<=n;++i)
        if(a[i])
            break;
    if(i==n+1)
        return 0;
    pos=i;
    len=1;
    wa[1]=Pow(a[i],P-2);
    cnt=i;
    for(++i;i<=n;++i){
        s=0;
        for(j=1;j<=cnt;++j)
        s=(s+(LL)a[i-j]*cur[j])%P;
        s=(s+P-a[i])%P;
        if(s==0)continue;
        memcpy(tmp,cur,cnt+1<<2);
        for(j=1;j<=len;++j)
        cur[i-pos+j-1]=(cur[i-pos+j-1]+(LL)wa[j]*(P-s))%P;
        wa[1]=P-1;
        for(j=1;j<=cnt;++j)
        wa[j+1]=tmp[j];
        x=len;
        len=cnt+1;
        s=Pow(s,P-2);
        for(j=1;j<=len;++j)
        wa[j]=(LL)wa[j]*s%P;
        cnt=std::max(cnt,i-pos+x-1);
        pos=i;
    }
    for(i=1;i<=cnt;++i)
        printf("%d ",cur[i]);
    puts("");
    return 0;
}
