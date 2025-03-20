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
int n,m,e;
vector<int> g[520];
bool vis[520];
int mat[520];
bool find(int u){
	for(int i=0;i<g[u].size();++i){
		int v=g[u][i];
		if(vis[v]) continue;
		vis[v]=1;
		if(!mat[v] || find(mat[v])){
			mat[v]=u;
			return 1;
		}
	}
	return 0;
}
signed main(){
	auto solve=[&](){
		read(n),read(m),read(e);
		for(int i=1;i<=e;++i){
			int u,v;
			read(u),read(v);
			g[u].push_back(v);
		}
		int ans=0;
		for(int i=1;i<=n;++i){
			memset(vis,0,sizeof(vis));
			if(find(i)) ans++;
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


