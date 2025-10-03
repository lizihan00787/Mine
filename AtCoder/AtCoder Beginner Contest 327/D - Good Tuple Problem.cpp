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
int a[200010],b[200010];
struct edge{
	int to,nxt;
}e[400020];
int head[200010],cnt=0;
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
bool vis[200010];
int lens[200010];
void dfs(int u,int fa,int len){
	vis[u]=1;
	lens[u]=len;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to!=fa){
			if(vis[to]){
				if(abs(len-lens[to])%2!=1){
					cout<<"No"<<endl;
					exit(0);
				}
				continue;
			}
			dfs(to,u,len+1);
		}
	}
}
signed main(){
	auto solve=[&](){
		read(n),read(m);
		map<PII,bool> q;
		for(int i=1;i<=m;++i) read(a[i]);
		for(int i=1;i<=m;++i) read(b[i]);
		for(int i=1;i<=m;++i){
			int x=a[i];
			int y=b[i];
			if(!q[mk(x,y)]) q[mk(x,y)]=q[mk(y,x)]=1;
			else continue;
			add(x,y);
			add(y,x);
		}
		for(int i=1;i<=n;++i){
			if(!vis[i]) dfs(i,0,1);
		}
		cout<<"Yes"<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


