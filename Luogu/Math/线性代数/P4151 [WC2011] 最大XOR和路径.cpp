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

const int N=70;

ll a[N];
int n,m;

void insert(ll x){
	for(int i=62;~i;--i){
		if(!(x>>(ll)i)) continue;
		if(!a[i]) {a[i]=x;break;}
		x^=a[i];
	}
}
ll query(ll x){
	ll res=x;
    for(int i=61;~i;--i){
        if(!a[i]) continue;
        res=max(res,res^a[i]);
    }
	return res;
}

struct edge{
	int to,nxt;
	ll w;
}e[200010];
int head[50010],cnt=0;
void add(int u,int v,ll w){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	e[cnt].w=w;
	head[u]=cnt;
}
int vis[50010];
ll d[50010];
void dfs(int u,ll res){
	d[u]=res,vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(!vis[to]) dfs(to,res^e[i].w);
		else insert(res^e[i].w^d[to]);
	}
}

void solve(){
	read(n,m);
	for(int i=1;i<=m;++i){
		int u,v;
		ll w;
		read(u,v,w);
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	cout<<query(d[n])<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


