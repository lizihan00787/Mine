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

const int N=1e5+20;

int n,q;
int a[N];
vector<int> G[N];
int dfx[N],rk[N],siz[N],tp[N],tot,son[N],fa[N],dep[N];

namespace Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        int lsum,rsum,sum,maxx;
        int tag;
        inline node (int _lsum = 0,int _rsum = 0,int _sum = 0,int _maxx = 0,int _tag = 10001) :
        lsum(_lsum),rsum(_rsum),sum(_sum),maxx(_maxx),tag(_tag){}
        node operator + (const node a) const{
            node tmp;
            tmp.sum=sum+a.sum;
            tmp.lsum=max(lsum,sum+a.lsum);
            tmp.rsum=max(a.rsum,a.sum+rsum);
            tmp.maxx=max(rsum+a.lsum,max(maxx,a.maxx));
            tmp.tag=10001;
            return tmp;
        }
    }t[N<<2];
    void pushtag(int rt,int l,int r,int x){
        t[rt].sum=(r-l+1)*x;
        t[rt].lsum=t[rt].rsum=t[rt].maxx=max(t[rt].sum,0);
        t[rt].tag=x;
    }
    void pushdown(int rt,int l,int r){
        if(t[rt].tag==10001) return;
        int mid=(l+r)>>1;
        pushtag(lson,l,mid,t[rt].tag);pushtag(rson,mid+1,r,t[rt].tag);
        t[rt].tag=10001;
    }
    void build(int rt,int l,int r){
        t[rt].tag=10001;
        if(l==r) return (void)(t[rt].sum=a[rk[l]],t[rt].lsum=t[rt].rsum=t[rt].maxx=max(0,t[rt].sum));
        int mid=(l+r)>>1;
        build(lson,l,mid);build(rson,mid+1,r);
        t[rt]=t[lson]+t[rson];
    }
    void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l & r<=R) return (void)(pushtag(rt,l,r,x));
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        t[rt]=t[lson]+t[rson];
    }
    node query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt];
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L>mid) return query(rson,mid+1,r,L,R);
        if(R<=mid) return query(lson,l,mid,L,R);
        return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
    }
}
using namespace Stree;
namespace TD{
    void dfs1(int u,int f){
        siz[u]=1;
        fa[u]=f;
        dep[u]=dep[f]+1;
        for(auto v:G[u]){
            if(v==f) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]]) son[u]=v;
        }
    }
    void dfs2(int u,int t){
        tp[u]=t;
        dfx[u]=++tot;rk[tot]=u;
        if(son[u]) dfs2(son[u],t);
        for(auto v:G[u]){
            if(v==fa[u] || v==son[u]) continue;
            dfs2(v,v);
        }
    }
    void upd(int u,int v,int x){
        while(tp[u]!=tp[v]){
            if(dep[tp[u]]<dep[tp[v]]) swap(u,v);
            update(1,1,n,dfx[tp[u]],dfx[u],x);
            u=fa[tp[u]];
        }
        if(dep[u]<dep[v]) swap(u,v);
        update(1,1,n,dfx[v],dfx[u],x);
    }
    int que(int u,int v){
        node L,R;
        while(tp[u]!=tp[v]){
            if(dep[tp[u]]<dep[tp[v]]) R=query(1,1,n,dfx[tp[v]],dfx[v])+R,v=fa[tp[v]];
            else L=query(1,1,n,dfx[tp[u]],dfx[u])+L,u=fa[tp[u]];
        }
        if(dep[u]<dep[v]) R=query(1,1,n,dfx[u],dfx[v])+R;
        else L=query(1,1,n,dfx[v],dfx[u])+L;
        swap(L.rsum,L.lsum);
        return (L+R).maxx;
    }
}
using namespace TD;


inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<n;++i){
        int u,v;
        read(u,v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    read(q);
    while(q--){
        int op,u,v,x;
        read(op,u,v);
        if(op==1) cout<<que(u,v)<<endl;
        else read(x),upd(u,v,x);
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}