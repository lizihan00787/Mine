#include<bits/stdc++.h>
#define int long long
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
int n,m;
const int Max=20;
struct node{
	int to,w;
};
vector<node> e[120];
int dp[120][1<<14];
signed main(){
	read(n),read(m);
	int u,v,w;
	for(int i=1;i<=m;++i){
		read(u),read(v),read(w);
		u--,v--;
		e[u].push_back(node{v,w});
		e[v].push_back(node{u,w});
	}
	int ans=0;
	int mas=1<<n;
	int to;
	for(int s=0;s<mas;++s){
		for(int i=0;i<n;++i){
			if((s>>i)&1){
				for(auto edge:e[u=i])
					if(!(s>>(to=edge.to)&1)){
						dp[to][s^(1<<to)]=max(dp[to][s^(1<<to)],dp[u][s]+edge.w);
					}
			}
		}
	}
	for(int i=0;i<n;++i){
		ans=max(ans,dp[i][mas-1]);
	}
	cout<<ans<<endl;
	return 0;
}


