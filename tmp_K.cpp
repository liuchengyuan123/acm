#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef ONLINE_JUDGE
#define dbg(x...) do{cout << "\033[33;1m" << #x << "->" ; err(x);} while (0)
void err(){cout << "\033[39;0m" << endl;}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x){for (auto v: a) cout << v << ' '; err(x...);}
template<typename T, typename... A>
void err(T a, A... x){cout << a << ' '; err(x...);}
#else
#define dbg(...)
#endif
#define inf 1ll << 50
const int N = 205;
int mov[3][2]={{0,1},{1,0},{1,1}};
bool has[210][210];
vector<pair<int, int> > v;
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i <= 209; i++)
			for (int j = 0; j <= 209; j++)
				has[i][j] = 0;
		v.clear();
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			has[x + 100][y + 100] = true;
			v.push_back(make_pair(x, y));
		}
		ll cnt = 0;
		int sz=v.size();
		for (int i=0;i<sz;i++)
		{
			int x=v[i].first,y=v[i].second;
			for(int j=0;j<sz;j++){
				int xx=v[j].first,yy=v[j].second;
				if(j==i) continue;
				int dx=xx-x,dy=yy-y;
				int flag=1;
				int dxx=x-dy,dyy=y+dx;
				
				if(dxx<-100 || dxx>100 || dyy<-100 || dyy>100||!has[dxx+100][dyy+100]){
					flag=0; 
				}

				dxx=x-dy+dx,dyy=y+dx+dy;
				if(dxx<-100 || dxx>100 || dyy<-100 || dyy>100||!has[dxx+100][dyy+100]){
					flag=0; 
				}
				cnt+=flag;
			}	
		}
		printf("%lld\n",cnt / 4);
	}
	return 0;
}
