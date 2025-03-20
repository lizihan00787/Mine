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

const int N=120,M=520;

int n,m;
int w[N],v[N],d[N];
vector<int> g[N],ge[N];
int dp[N][M];

int dfx[N],low[N],st[N],bel[N],in[N],tot=0,tp=0;
bool vis[N];

void tanjan(int u){
	dfx[u]=low[u]=++tot;
	st[++tp]=u;vis[u]=1;
	for(auto to:g[u]){
		if(!dfx[to]) tanjan(to),low[u]=min(low[u],low[to]);
		else if(vis[to]) low[u]=min(low[u],dfx[to]);
	}
	if(low[u]==dfx[u]){
		bel[u]=u;
		while(st[tp]!=u){
			bel[st[tp]]=u;
			w[u]+=w[st[tp]];
			v[u]+=v[st[tp]];
			vis[st[tp]]=0;
			--tp;
		}
		vis[st[tp]]=0;
		tp--;
	}
}

void dfs(int u){
	for(int i=w[u];i<=m;++i) dp[u][i]=v[u];
	for(auto to:ge[u]){
		dfs(to);
		int k=m-w[u];
		for(int i=k;i>=0;--i){
			for(int j=0;j<=i;++j){
				dp[u][i+w[u]]=max(dp[u][i+w[u]],dp[to][j]+dp[u][i+w[u]-j]);
			}
		}
	}
}

void solve(){
    read(n,m);
	for(int i=1;i<=n;++i) read(w[i]);
	for(int i=1;i<=n;++i) read(v[i]);
	for(int i=1;i<=n;++i){
		read(d[i]);
		g[d[i]].push_back(i);
	}
	for(int i=1;i<=n;++i) if(!dfx[i]) tanjan(i);
	for(int i=1;i<=n;++i) if(bel[i]!=i) in[i]=0x3f3f3f3f;
	for(int i=1;i<=n;++i){
		if(bel[d[i]]!=bel[i]){
			ge[bel[d[i]]].push_back(bel[i]);
			in[bel[i]]++;
		}
	}
	for(int i=1;i<=n;++i) if(!in[i]) ge[0].push_back(i);
	dfs(0);
	cout<<dp[0][m]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


