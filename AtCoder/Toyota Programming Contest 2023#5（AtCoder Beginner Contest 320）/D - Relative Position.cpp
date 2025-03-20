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
int fa[200010];
int find(int x){
	if(fa[x]==x){
		return fa[x];
	}
	return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
	int x=find(a),y=find(b);
	if(x!=y){
		fa[y]=x;
	}
}
int n,m;
map<int,PII> q;
map<int,bool> vis;
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		int a,b,x,y;
		for(int i=1;i<=n;++i) fa[i]=i;
		q[1]=mk(0,0);
		for(int i=1;i<=m;++i){
			cin>>a>>b>>x>>y;
			if(q.find(a)!=q.end() && q.find(b)!=q.end()){
				int nx=q[a].first+x;
				int ny=q[a].second+y;
				if(q[b].first!=nx || q[b].second!=ny){
					vis[b]=1;
				}
			}
			else if(q.find(a)!=q.end() && q.find(b)==q.end()){
				int nx=q[a].first+x;
				int ny=q[a].second+y;
				q[b]=mk(nx,ny);
				vis[b]=0;
				if(a<b) unionn(a,b);
				else unionn(b,a);
			}
			else if(q.find(b)!=q.end() && q.find(a)==q.end()){
				int nx=q[b].first-x;
				int ny=q[b].second-y;
				q[a]=mk(nx,ny);
				vis[a]=0;
				if(a<b) unionn(a,b);
				else unionn(b,a);
			}
			else{
				if(a<b) unionn(a,b);
				else unionn(b,a);
				vis[a]=1;
				vis[b]=1;
			}
		}
		for(int i=1;i<=n;++i){
			if(vis[i] && find(i)!=1){
				cout<<"undecidable"<<endl;
			}
			else{
				cout<<q[i].first<<' '<<q[i].second<<endl;
			}
		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


