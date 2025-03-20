#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
template<typename P>
void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
	     if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
int T=1;

const int N=5e5+20,M=3e7+20;;

int n,p,q,fa[N],vis[N];
ll a[N],b[N],maxn;
vector<int> g[N];

struct trie{
	int cnt;
	int val[M],tr[M][2],pp=0,qq=0;
	ll mx=0;
	void clear(){
		cnt=mx=0;
		memset(val,0,sizeof(val));
		memset(tr,0,sizeof(tr));
	}
	void ins(int id){
		int x=0;
		for(int i=59;i>=0;--i){
			int k=(a[id]>>i)&1ll;
			if(!tr[x][k]) tr[x][k]=++cnt;
			x=tr[x][k];
		}
		val[x]=id;
		x=0;
		for(int i=59;i>=0;--i){
			int k=(a[id]>>i)&1ll;
			if(tr[x][k^1]) x=tr[x][k^1];
			else if(!tr[x][k^1] && tr[x][k]) x=tr[x][k];
			else return;
		}
		if((a[id]^a[val[x]])>mx){
			pp=id;
			qq=val[x];
			mx=a[id]^a[val[x]];
		}
	}
}t;

void dfs(int u){
	t.ins(u);
	for(auto to:g[u]) dfs(to);
}
void dfs1(int u,int f){
	if(u==0) return;
	dfs1(fa[u],u);
	b[u]=t.mx;
	vis[u]=1;
	t.ins(u);
	if(u!=f) for(auto to:g[u]) if(to!=f) dfs(to);
}

void solve(){
    read(n);
	for(int i=2;i<=n;++i){
		read(fa[i]);
		g[fa[i]].push_back(i);
	}
	for(int i=1;i<=n;++i) read(a[i]),t.ins(i);
	p=t.pp,q=t.qq,maxn=t.mx;
	t.clear();
	dfs1(p,p);
	t.clear();
	dfs1(q,q);
	for(int i=1;i<=n;++i){
		if(vis[i]) cout<<b[i]<<endl;
		else cout<<maxn<<endl;
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


