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

const int N=1e5+20,M=3e5+20;

int n,m;
int is[N],in[N];
vector<int> g[N],ge[N];
int dfx[N],low[N],vis[N],st[N],tot=0,tp=0;
int bel[N],scc=0,siz[N];

void tanjan(int u){
	dfx[u]=low[u]=++tot;
	st[++tp]=u;vis[u]=1;
	for(auto to:g[u]){
		if(!dfx[to]) tanjan(to),low[u]=min(low[to],low[u]);
		else if(vis[to]) low[u]=min(low[u],dfx[to]);
	}
	if(low[u]==dfx[u]){
		scc++;
		while(st[tp+1]!=u){
			vis[st[tp]]=0;
			bel[st[tp]]=scc;
			siz[scc]++;
			tp--;
		}
	}
}


void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
 	    int u,v;
	    read(u,v);
	    g[u].push_back(v);
    }
    for(int i=1;i<=n;++i) if(!dfx[i]) tanjan(i);
    for(int u=1;u<=n;++u){
 	    for(auto v:g[u]){
 		    if(bel[u]==bel[v] || is[bel[v]]) continue;
 	        ge[bel[u]].push_back(bel[v]);
		    in[bel[v]]++;
	        is[bel[v]]=1;
	    }
	    for(auto v:g[u]) is[bel[v]]=0; 
    }
	int ctot=0;
	bool f=1;
	for(int i=1;i<=scc;++i){
		if(!in[i]) ctot++;
		if(in[i] || siz[i]>1) continue;
		if(f){
			bool ff=1;
			for(auto v:ge[i]){
				if(in[v]<=1){
					ff=0;
					break;
				}
			}
			if(ff) ctot--,f=0;
		}
	}
	printf("%.6lf",1.0*(n-ctot)/n);
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


