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

const int N=1e5+20;

int n,m,s,t;

vector<int> g[N];

int rk[N],dfx[N],low[N],tot=0,f[N];
int clow[N],ed[N],ced[N];

void tanjan(int u,int fa){
	f[u]=fa;
	dfx[u]=low[u]=clow[u]=++tot;
	rk[tot]=u;
	ed[u]=ced[u]=u;
	for(auto to:g[u]){
		if(to==fa) continue;
		if(!dfx[to]){
			tanjan(to,u);
			if(low[to]<low[u]){
				clow[u]=low[u],ced[u]=ed[u];
				low[u]=low[to],ed[u]=ed[to];
			}
			else if(low[to]<clow[u]) clow[u]=low[to],ced[u]=ed[to];
		}
		else{
			if(dfx[to]<low[u]){
				clow[u]=low[u],ced[u]=ed[u];
				low[u]=dfx[to],ed[u]=u;
			}
			else if(dfx[to]<clow[u]) clow[u]=dfx[to],ced[u]=u;	
		}
	}
	if(!s && !t && clow[u]<dfx[u]) s=u,t=rk[clow[u]];
	return;
}

inline vector<int> getPath(int u,int fa){
	vector<int> res;
	for(int i=u;i!=fa;i=f[i]) res.push_back(i);
	res.push_back(fa);
	return res;
}
inline vector<int> reverse(vector<int> a){
	reverse(a.begin(),a.end());
	return a;
}
inline vector<int> merge(vector<int> a,vector<int> b){
	a.insert(a.end(),b.begin(),b.end());
	return a;
}

void solve(){
	read(n,m);
	for(int i=1;i<=n;++i) g[i].clear();
	for(int i=1;i<=m;++i){
		int u,v;
		read(u,v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	s=t=0,tot=0;
	fill(dfx+1,dfx+n+1,0);
	for(int i=1;i<=n;++i) if(!dfx[i]) tanjan(i,0);
	if(!s && !t) cout<<-1<<endl;
	else{
		cout<<s<<' '<<t<<endl;

		vector<int> ans1=getPath(s,t);
		cout<<ans1.size()<<' ';
		for(auto it:ans1) cout<<it<<' ';
		cout<<endl;

		vector<int> ans2=merge(reverse(getPath(ed[s],s)),reverse(getPath(t,rk[low[s]])));
		cout<<ans2.size()<<' ';
		for(auto it:ans2) cout<<it<<' ';
		cout<<endl;

		vector<int> ans3=merge(reverse(getPath(ced[s],s)),getPath(rk[clow[s]],rk[clow[s]]));
		cout<<ans3.size()<<' ';
		for(auto it:ans3) cout<<it<<' ';
		cout<<endl;
	}
}

signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}


