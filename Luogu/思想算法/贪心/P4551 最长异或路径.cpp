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
const int N=2e6+10;
struct node{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].w=w;
	head[u]=cnt;
}
int sum[N];
int t[N][2],tot=0;
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to!=fa){
			sum[to]=sum[u]^e[i].w;
			dfs(to,u);
		}
	}
}
void build(int val,int x){
	for(int i=(1<<30);i;i>>=1){
		bool c=val&i;
		if(!t[x][c]) t[x][c]=++tot;
		x=t[x][c];
	}
}
int query(int val,int x){
	int ans=0;
	for(int i=(1<<30);i;i>>=1){
		bool c=val&i;
		if(t[x][!c]){
			ans+=i;
			x=t[x][!c];
		}
		else x=t[x][c];
	}
	return ans;
}
signed main(){
	auto solve=[&](){
		int n;
		read(n);
		for(int i=1;i<n;++i){
			int u,v,w;
			read(u),read(v),read(w);
			add(u,v,w);
			add(v,u,w);
		}
		dfs(1,-1);
		for(int i=1;i<=n;++i) build(sum[i],0);
		int ans=0;
		for(int i=1;i<=n;++i) ans=max(ans,query(sum[i],0));
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


