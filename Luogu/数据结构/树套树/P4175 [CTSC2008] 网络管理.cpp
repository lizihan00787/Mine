#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
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
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

#define lowbit(x) (x&(-x))

const int N=8e4+50,mx=1e8,M=2e7+50;

int n,m,cnt=0;
int a[N];
int dfx[N],dep[N],f[N][32];
int rtt[N],r[N];

vector<int> g[N];

void dfs(int x,int ff){
    f[x][0]=ff;dep[x]=dep[ff]+1;dfx[x]=++cnt;
    for(int i=0;i<16;i++)f[x][i+1]=f[f[x][i]][i];
    for(auto to:g[x]){
        if(to==ff) continue;
        dfs(to,x);
    }
    rtt[x]=cnt;
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=16;~i;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=16;~i;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}


struct node{
    int l,r,val;
}t[M];
struct Node{
    int len,s[N];
    int calc() {int res=0;for(int i=1;i<=len;++i) res+=t[t[s[i]].r].val;return res;}
    void L() {for(int i=1;i<=len;++i) s[i]=t[s[i]].l;}
    void R() {for(int i=1;i<=len;++i) s[i]=t[s[i]].r;}
    void init(int x) {len=0;for(;x;x-=lowbit(x)) s[++len]=r[x];}
}A,B,C,D;

struct Stree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    void update(int &rt,int l,int r,int k,int x){
        if(!rt) rt=++cnt;
        t[rt].val+=x;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k,x);
        else update(rson,mid+1,r,k,x);
    }
    void modify(int w,int k,int x){
        for(;w<=n;w+=lowbit(w)) update(r[w],1,mx,k,x);
    }
    int query(int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,tmp=A.calc()+B.calc()-C.calc()-D.calc();
        if(tmp>=k) {A.R(),B.R(),C.R(),D.R();return query(mid+1,r,k);}
        else {A.L(),B.L(),C.L(),D.L();return query(l,mid,k-tmp);}
    }
}Q;

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<n;++i){
        int u,v;
        read(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    cnt=0;
    for(int i=1;i<=n;++i) Q.modify(dfx[i],a[i],1),Q.modify(rtt[i]+1,a[i],-1);
    for(int i=1;i<=m;++i){
        int op,x,y;
        read(op,x,y);
        if(op){
            int lc=lca(x,y);if(dep[x]+dep[y]-2*dep[lc]+1<op) {puts("invalid request!");continue;}
            A.init(dfx[x]),B.init(dfx[y]),C.init(dfx[lc]),D.init(dfx[f[lc][0]]);
            cout<<Q.query(1,mx,op)<<endl;
        }
        else Q.modify(dfx[x],a[x],-1),Q.modify(rtt[x]+1,a[x],1),Q.modify(dfx[x],a[x]=y,1),Q.modify(rtt[x]+1,y,-1);
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}