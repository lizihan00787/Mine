#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int T=1;
int n,m;
int w[120],z[120];
long long dp[100010];
signed main(){
	read(n);
	int u,v,c=0;
	long long res=0x3f3f3f3f3f3f3f3f;
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;++i){
		read(u),read(v),read(z[i]);
		if(u<v) w[i]=(u+v+1)/2-u;
		c+=z[i];
	}
	dp[0]=0;
	for(int i=0;i<n;++i){
		for(int j=c;j>=z[i];--j){
			dp[j]=min(dp[j-z[i]]+w[i],dp[j]);
		}
	}
	for(int i=(c+1)/2;i<=c;++i) res=min(res,dp[i]);
	cout<<res<<endl;
	return 0;
}


