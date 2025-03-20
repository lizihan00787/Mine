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
int a[200020];
int sum[200020];
int q[200020];
bool check(int x){
	if((sum[n]-1)/x>m) return 0;
	int len=1;
	int sum=0;
	int cnt=0,cnn=0;
	while(1){
		sum++;
		int k=upper_bound(q+1,q+n+1,x*len+cnt-cnn)-q-1;
		int p=q[k];
		if(p<(x*len+cnt-cnn)) cnn+=x*len+cnt-cnn-p;
		cnt++;
		if(x*len+cnt-cnn>=q[n]) break;
		len++;
	}
	if(sum<=m){
		return 1;
	}
	return 0;
}
signed main(){
	auto solve=[&](){
		read(n),read(m);
		int l=-0x3f3f3f3f3f3f3f3f; 
		for(int i=1;i<=n;++i){
			read(a[i]);
			sum[i]=sum[i-1]+a[i]+1;
			q[i]=sum[i]-1;
			l=max(l,a[i]);
		}
		if(m==1){
			cout<<q[n]<<endl;
			return;
		}
		int r=2e5+100,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) r=mid-1,ans=mid;
			else l=mid+1;
		}
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


