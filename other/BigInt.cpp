#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
const int INF=0x3f3f3f3f;
const int MOD=1e9+7;
const double eps=1e-7;
typedef long long ll;
#define vi vector<int>
#define si set<int>
#define pii pair<int,int>
#define pi acos(-1.0)
#define pb push_back
#define mp make_pair
#define lowbit(x) (x&(-x))
#define sci(x) scanf("%d",&(x))
#define scll(x) scanf("%lld",&(x))
#define sclf(x) scanf("%lf",&(x))
#define pri(x) printf("%d",(x))
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxn=1500;
struct BigInt{
    const static int mod=10000;
    const static int LEN=4;
    int a[maxn],len;
    BigInt()
    {
        memset(a,0,sizeof(a));
        len=1;
    }
    void init(int x)
    {
        memset(a,0,sizeof(a));
        len=0;
        do//四位一存 如123456789存为 6789 2345 1
        {
            a[len++]=x%mod;
            x/=mod;
        }while(x);
    }
    void Init(const char s[])//重点 123 4567
    {
        memset(a,0,sizeof(a));
        int l=strlen(s),res=0;
        len=l/LEN;
        if(l%LEN)len++;//l/LEN向上取整 len=2 表明需要两个字节能存下
        for(int i=l-1;i>=0;i-=LEN)
        {
            int t=0,k=max(i-LEN+1,0);//k是找到当前字节的最高位 回退len-1长 防越界
            for(int j=k;j<=i;j++)t=t*10+s[j]-'0';//从4开始 t临时存储4567
            a[res++]=t;//将低位存入
        }
    }
    int Compare(const BigInt &b)//位多的大
    {
        if(len<b.len)return -1;
        if(len>b.len)return 1;
        for(int i=len-1;i>=0;i--)//从高位比较
            if(a[i]<b.a[i])return -1;
            else if(a[i]>b.a[i])return 1;
        return 0;//完全相等的情况
    }
    BigInt operator +(const BigInt &b)const
    {
        BigInt ans;
        ans.len=max(len,b.len);
        for(int i=0;i<=ans.len;i++)ans.a[i]=0;
        for(int i=0;i<ans.len;i++)
        {
            ans.a[i]+=((i<len)?a[i]:0)+((i<b.len)?b.a[i]:0);//防止越位现象
            ans.a[i+1]+=ans.a[i]/mod;//向高位进位
            ans.a[i]%=mod;
        }
        if(ans.a[ans.len]>0)ans.len++;//产生了9999+9999=9998 1的数组高位进位
        return ans;
    }
    BigInt operator -(const BigInt &b)const//确保被减数大 差为正
    {
        BigInt ans;
        ans.len=len;
        int k=0;
        for(int i=0;i<ans.len;i++)
        {
            ans.a[i]=a[i]+k-b.a[i];
            if(ans.a[i]<0)ans.a[i]+=mod,k=-1;//向a[i]高位借10000,k=-1下轮生效
            else k=0;
        }
        while(ans.a[ans.len-1]==0&&ans.len>1)ans.len--;//把前缀0去掉 如果ans.len=1时说明a=b差为0
        return ans;
    }
    BigInt operator *(const BigInt &b)const
    {
        BigInt ans;
        for(int i=0;i<len;i++)
        {
            int k=0;
            for(int j=0;j<b.len;j++)
            {
                int temp=a[i]*b.a[j]+ans.a[i+j]+k;//模拟小学生乘法 i*j加到i+j上去 k为低位来的进位
                ans.a[i+j]=temp%mod;
                k=temp/mod;//k为向高位进的位 下一轮生效
            }
            if(k!=0)ans.a[i+b.len]=k;//高位进位 99*99=9801 右起第1位*右起第1位还是能到右起第3位的
        }
        ans.len=len+b.len;//4位数*4位数不会超过8位数
        while(ans.a[ans.len-1]==0&&ans.len>1)ans.len--;//查出实际长度
        return ans;
    }
    BigInt operator /(const int &n)const//被确保被除数大 商为正
    {
        BigInt ans;
        ans.len=len;
        int k=0;
        for(int i=ans.len-1;i>=0;i--)
        {
            k=k*mod+a[i];//k=上一位来的退位*10000+这一位
            ans.a[i]=k/n;//这一位除以n
            k=k%n;//这一位除以n的余数送给下一位,i=0最后一位如57/28余的1直接丢掉 取整
        }
        while(ans.a[ans.len-1]==0&&ans.len>1)ans.len--;
        return ans;
    }
    void output(){
        printf("%d",a[len-1]);//是多少就是多少 没有前缀0
        for(int i=len-2;i>=0;i--)
            printf("%04d",a[i]);//包含前缀0 如0001
        printf("\n");
    }
};
BigInt a[105];
int main()
{
    int n;
    scanf("%d",&n);
    a[0].init(1),a[1].init(1);
    rep(k,2,n+1)
    {
        int t=4*k-2;
        BigInt temp1,temp2;
        temp1.init(t);
        a[k]=a[k-1]*temp1;
        temp2=a[k]/(k+1);
        a[k]=temp2;
    }
    a[n+1]=a[n+1]-
    a[1];
    a[n+1].output();
    return 0;
}
