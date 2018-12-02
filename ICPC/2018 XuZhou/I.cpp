#include<bits/stdc++.h>
 
using namespace std;
 
char s[10],S[1000005];
 
int main(){
	
	int T,N;
	scanf("%d",&T);
	while(T--){
		scanf("%d %s",&N,s);
		scanf("%s",S);
		long long sum = 0;
		bool flag = false;
		for(int i=0 ; i<N ; ++i){
			int t = (int)(s[0]-S[i]);
			if(t < 0)t = -t;
			if(t < 10 && t!=0 && flag)++sum;
			if(t == 0 && flag)sum += 2;
			while(t){
                //cout << i << " " << t << endl;
				flag = true;
				t /= 10;
				++sum;
			}
		}
		if(sum == 0)++sum;
		printf("%lld\n",sum);
	}
	
	return 0;
}
