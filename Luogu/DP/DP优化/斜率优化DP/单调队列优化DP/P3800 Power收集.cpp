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
int n,m,t,k;
int f[4040][4040];
int q[4040]={0x3f3f3f3f3f3f3f3f};
int l=1,r=1;
int now;
signed main(){
	auto push=[&](int x){
		while(l<=r && f[now-1][q[r]]<f[now-1][x]) r--;
		q[++r]=x;
	};
	auto find=[&](int x){
		if(x+t<=m) push(x+t);
		while(q[l]+t<x) l++;
		return q[l];
	};
	auto solve=[&](){
		read(n),read(m),read(k),read(t);
		for(int i=1;i<=k;++i){
			int x,y,c;
			read(x),read(y),read(c);
			f[x][y]=c;
		}
		for(now=2;now<=n;++now){
			for(int j=1;j<=t;++j) push(j);
			for(int j=1;j<=m;++j){
				f[now][j]+=f[now-1][find(j)];
			}
			l=r=1,q[1]=0;
		}
		int ans=0;
		for(int i=1;i<=m;++i){
			ans=max(ans,f[n][i]);
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


