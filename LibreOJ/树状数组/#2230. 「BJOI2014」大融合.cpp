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

const int N=1e6+20;

int n,m;
int fa[N];
int dfx[N],tot,las[N],tr[N],rot[N],cnt[N];
vector<int> g[N];
struct node{
	int t,x,y;
}que[N];

void add(int u,int v){
	g[u].push_back(v),cnt[u]++;
	g[v].push_back(u),cnt[v]++;
}
void dfs(int u,int f){
	dfx[u]=++tot,fa[u]=f;
	for(int i=0;i<cnt[u];++i){
		int to=g[u][i];
		if(to==f) continue;
		dfs(to,u);
	}
	las[u]=tot;
}

int find(int x){
	if(rot[x]==x) return x;
	return rot[x]=find(rot[x]);
}


struct BIT{
	#define lowbit(x) (x&(-x))
	int t[N];
	void add(int x,int val){
		if(x==0) return;
		for(;x<=n;x+=lowbit(x)) t[x]+=val;
	}
	int query(int x){
		int ans=0;
		for(;x;x-=lowbit(x)) ans+=t[x];
		return ans;
	}
	int que(int l,int r){
		return query(r)-query(l-1);
	}
}Q;

void init() {for(int i=1;i<=n;++i) rot[i]=i,Q.add(dfx[i],1),Q.add(dfx[fa[i]],-1);}

void solve(){
    read(n,m);
	for(int i=1;i<=m;++i){
		char op;
		int x,y;
		cin>>op;
		read(x,y);
		if(op=='A') add(x,y),que[i]={0,x,y};
		else que[i]={1,x,y};
	}
	for(int i=1;i<=n;++i) if(!dfx[i]) dfs(i,0);
	init();
	for(int i=1;i<=m;++i){
		int x=que[i].x,y=que[i].y;
		if(dfx[x]<dfx[y]) swap(x,y);
		int rt=find(y),val=Q.que(dfx[x],las[x]);
		if(que[i].t==0) rot[x]=rt,Q.add(dfx[y],val),Q.add(dfx[fa[rt]],-val);
		else cout<<val*(Q.que(dfx[rt],las[rt])-val)<<endl;
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


