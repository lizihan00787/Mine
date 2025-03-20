#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int N=5020,mod=1e9+7;

int n;
int siz[N],g[N],f[N][N],ff[N],ans=0;
vector<int> G[N];

void dfs(int u,int fa){
	siz[u]=1,f[u][1]=1;
	for(auto to:G[u]){
		if(to==fa) continue;
		dfs(to,u);
		for(int j=1;j<=siz[u];++j) ff[j]=f[u][j],f[u][j]=0;
		for(int j=1;j<=siz[u];++j){
			for(int k=1;k<=siz[to];++k){
				f[u][j]=(f[u][j]-1ll*ff[j]*f[to][k]%mod*g[k]%mod+mod)%mod;
				f[u][j+k]=(f[u][j+k]+ff[j]*f[to][k]%mod)%mod;
			}
		}
		siz[u]+=siz[to];
	}
}

void solve(){
    read(n);
	g[0]=1;
	for(int i=2;i<=n;i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
	for(int i=1;i<n;++i){
		int u,v;
		read(u,v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,-1);
	for(int i=1;i<=n;++i) ans=(ans+f[1][i]*g[i]%mod)%mod;
	cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



