#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
using namespace std;
int T=1;
int n,p,d;
int a[2000010];
int q[2000010];
int sum[2000010];
int w[200010];
signed main(){
	auto solve=[&](){
		read(n),read(p),read(d);
		for(int i=1;i<=n;++i) read(a[i]),sum[i]=sum[i-1]+a[i];
		int h=0,t=0,len=1;
		q[t]=d;
		int ans=d;
		for(int i=d+1;i<=n;++i){
			while(h<=t && sum[q[t]]-sum[q[t]-d]<sum[i]-sum[i-d]) t--;
			q[++t]=i;
			while(h<=t && sum[i]-sum[len-1]-sum[q[h]]+sum[q[h]-d]>p){
				++len;
				while(h<=t && q[h]-d+1<len) h++;
			}
			ans=max(ans,i-len+1);
		}
		cout<<ans<<endl;
		return;
	};
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}

