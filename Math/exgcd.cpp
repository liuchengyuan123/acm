#include<bits/stdc++.h>
using namespace std;
struct jie
{
    int x;
    int y;
    jie(int x,int y): x(x),y(y) {}
};
jie Exgcd(int a,int b)
{
    if(b==0)
    {
        return jie(1,0);
    }
    jie j=Exgcd(b,a%b);
    return jie(j.y,j.x-a/b*j.y);
}
//int main()
//{
//    int a,b,c;
//    while(cin>>a>>b>>c)
//    {
//        if(c%__gcd(a,b))
//        {
//            cout<<"No Integer answer!"<<endl;
//        }
//        else
//        {
//            jie j=Exgcd(a,b);
//            int w=c/__gcd(a,b);
//            printf("%d %d\n",w*j.x,w*j.y);
//        }
//    }
//    return 0;
//}
