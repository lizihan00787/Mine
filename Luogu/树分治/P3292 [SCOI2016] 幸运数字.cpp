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

const int N=2e4+20,M=2e5+20;

int n,m;

struct que{
	int to,nxt;
	bool vis;
}q[M<<1];
int cntq=1,headq[N];
void addq(int a,int b){
	q[++cntq]={b,headq[a],0};headq[a]=cntq;
	q[++cntq]={a,headq[b],0};headq[b]=cntq;
}

int p[N][65],pp[N];
vector<int> g[N];
int a[N];
int ans[M];
int siz[N],maxp[N];
bool vis[N];

struct Base {
	#define M 60
    long long s[M + 1];
    inline Base& init() {
        for (int i = 0; i <= M; i++) s[i] = 0;
        return *this;
    }
    inline Base& insert(long long x) {
        for (int i = M; ~i; i--) if (x >> i & 1) {
            if (s[i]) x ^= s[i];
            else {s[i] = x; break;}
        }
        return *this;
    }
    inline friend Base operator + (Base a, const Base &b) {
        for (int i = M; ~i; i--) if (b.s[i]) a.insert(b.s[i]);
        return a;
    }
    long long query() {
        long long ans = 0;
        for (int i = M; ~i; i--) if (ans < (ans ^ s[i])) ans ^= s[i];
        return ans;
    }
	#undef M
} f[N];

/*
void ins(int *f,int x){
	for(int i=61;~i;--i){
		if(!(x>>i)) continue;
		if(!f[i]) {f[i]=x;break;}
		x^=f[i];
	}
}
int query(int *f){
	int ans=0;
	for(int i=61;~i;--i) ans=max(ans,ans^f[i]);
	return ans;
}
void merge(int *g,int *f1,int *f2){
	for(int i=0;i<=61;++i) g[i]=f1[i];
	for(int i=0;i<=61;++i) ins(g,f2[i]);
}
*/

int rt,sum;


void getrt(int u,int fa=0){
    siz[u]=1;maxp[u]=0;
    for(auto to:g[u]){
        if(to==fa || vis[to]) continue;
        getrt(to,u);
        siz[u]+=siz[to];
        maxp[u]=max(maxp[u],siz[to]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}
int gett(int u,int no=0){
	sum=no?no:siz[u];
	maxp[rt]=sum;
	getrt(u);
	return rt;
}


int top,S[N],bel[N];

void dfs(int u,int fa,int tp){
	bel[S[top++]=u]=tp;
    (f[u]=f[fa]).insert(a[u]);
	for(auto to:g[u]){
		if(vis[to] || to==fa) continue;
		dfs(to,u,tp);
	}
}

void calc(int u){
	vis[u]=1;top=0;(f[u].init()).insert(a[u]);
	for(auto to:g[u]) if(!vis[to]) dfs(to,u,to);
	for(int i=headq[u];i;i=q[i].nxt){
		if(q[i].vis) continue;
		int to=q[i].to;
		ans[i>>1]=f[to].query();
		q[i].vis=q[i^1].vis=1;
	}
	for(int j=0;j<top;++j){
		int k=S[j];
		for(int i=headq[k];i;i=q[i].nxt){
			if(q[i].vis) continue;
			int to=q[i].to;
			if(bel[k]==bel[to]) continue;
			ans[i>>1]=(f[k]+f[to]).query();
			q[i].vis=q[i^1].vis=1;
		}
	}
	for(auto to:g[u]){
		if(vis[to]) continue;
		calc(gett(to));
	}
}

void solve(){
    read(n,m);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1;i<n;++i){
		int u,v;
		read(u,v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=m;++i){
		int a,b;
		read(a,b);
		addq(a,b);
	}
	calc(gett(1,n));
	for(int i=1;i<=m;++i) cout<<ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


