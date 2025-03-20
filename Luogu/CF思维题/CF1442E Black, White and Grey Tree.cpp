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
#define inf 0x3f3f3f3f
const int Max=200010;
int n,m,res;
struct edge{
	int to,nxt;
}e[Max<<1];
int head[Max],cnt=0;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int a[Max],f[Max][3],g[Max][3];
void dfs(int u,int fa){
	int c=a[u];
	if(c) f[u][c^3]=g[u][c^3]=inf,f[u][c]=0,g[u][c]=-inf;
	else f[u][1]=f[u][2]=0,g[u][1]=g[u][2]=-inf;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa) continue;
		dfs(to,u);
		for(int j=1;j<=2;++j){
			if(c+j==3) continue;
			int tf=inf,tg=inf;
			for(int k=1;k<=2;++k){
				if(f[to][k]==inf) continue;
				tf=min(tf,f[to][k]+(j!=k));
				tg=min(tg,f[u][j]+f[to][k]+(j!=k));
			}
			f[u][j]=max(f[u][j],tf);
			g[u][j]=max(g[u][j],tg);
		}
	}
	res=max(res,min(g[u][1],g[u][2]));
}
int T=1;
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) head[i]=0;
		for(int i=1;i<=n;++i) read(a[i]);
		for(int i=1;i<n;++i){
			int u,v;
			read(u),read(v);
			add(u,v),add(v,u);
		}
		res=0;
		dfs(1,0);
		printf("%lld\n",(res+1)/2+1);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}

