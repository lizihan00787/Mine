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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+10;

int n,m,nn;
int a[N],b[N];
int dep[N],siz[N],tp[N],son[N],f[N];
int rtt[N];
vector<int> g[N];


struct ZXT{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int l,r,sum;
    }t[N<<5];
    int cnt=0;
    void pushup(int rt){
        t[rt].sum=t[lson].sum+t[rson].sum;
    }
    void update(int &rt,int l,int r,int k){
        t[++cnt]=t[rt];
        t[cnt].sum=t[rt].sum+1;
        rt=cnt;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k);
        else update(rson,mid+1,r,k);
        pushup(rt);
    }
    int query(int rt1,int rt2,int rt3,int rt4,int l,int r,int k){
        int res=0,mid=(l+r)>>1,x=t[t[rt1].l].sum+t[t[rt2].l].sum-t[t[rt3].l].sum-t[t[rt4].l].sum;
        if(l==r) return l;
        if(x>=k) res=query(t[rt1].l,t[rt2].l,t[rt3].l,t[rt4].l,l,mid,k);
        else res=query(t[rt1].r,t[rt2].r,t[rt3].r,t[rt4].r,mid+1,r,k-x);
        return res;
    }
}Q;

void dfs1(int u,int fa){
    siz[u]=1;
    dep[u]=dep[fa]+1;
    rtt[u]=rtt[f[u]];
    Q.update(rtt[u],1,nn,a[u]);
    for(auto to:g[u]){
        if(to==fa) continue;
        f[to]=u;
        dfs1(to,u);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
    }
}
void dfs2(int u,int top){
    tp[u]=top;
    if(son[u]) dfs2(son[u],top);
    for(auto to:g[u]){
        if(to==son[u] || to==f[u]) continue;
        dfs2(to,to);
    }
}
int lca(int u,int v){
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]]) swap(u,v);
        u=f[tp[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    return v;
}

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        sort(b+1,b+n+1);
        nn=unique(b+1,b+n+1)-b-1;
        for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
        dfs1(1,0);
        dfs2(1,1);
        int las=0;
        for(int i=1;i<=m;++i){
            int u,v,k;
            read(u),read(v),read(k);
            u^=las;
            int lc=lca(u,v);
            las=b[Q.query(rtt[u],rtt[v],rtt[lc],rtt[f[lc]],1,nn,k)];
            cout<<las<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}