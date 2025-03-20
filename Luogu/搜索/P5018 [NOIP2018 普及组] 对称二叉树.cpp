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
int n;
struct node{
	int l,r,x;
}a[1000010];
bool dfs(int xx,int yy){
	if(xx==-1 && yy==-1) return 1;
	if(yy==-1 || xx==-1) return 0;
	if(a[xx].x!=a[yy].x) return 0;
	return dfs(a[xx].l,a[yy].r)&&dfs(a[xx].r,a[yy].l);
}
int cnt(int x){
	return x==-1?0:cnt(a[x].l)+cnt(a[x].r)+1;
}
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			read(a[i].x);
		}
		for(int i=1;i<=n;++i){
			read(a[i].l),read(a[i].r);
		}
		int ans=-1;
		for(int i=1;i<=n;++i){
			if(dfs(i,i)) ans=max(ans,cnt(i));
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


