#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
#define lson (rt<<1)
#define rson (rt<<1|1)
const int N=1e5+10;
int n,m,a[N<<2];
struct edge{
    int to,nxt,u;
}e[N<<1];
int cnt=0,head[N];
int siz[N],son[N],fa[N],dep[N],top[N];
int dfsx[N],pre[N],tot=0;
void add(int u,int v){
    e[++cnt].u=u;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
    e[++cnt].u=v;
    e[cnt].nxt=head[v];
    e[cnt].to=u;
    head[v]=cnt;
}
void dfs1(int u,int f){
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==f) continue;
        dep[to]=dep[u]+1;
        fa[to]=u;
        dfs1(to,u);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
    }
}
void dfs2(int u,int tp){
    dfsx[u]=++tot;pre[tot]=u,top[u]=tp;
    if(son[u]) dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa[u] || to==son[u]) continue;
        dfs2(to,to);
    }
}
struct Stree{
    struct node{
        int minn,tag;
    }t[N<<2];
    inline void pushup(int rt){
        t[rt].minn=min(t[lson].minn,t[rson].minn);
    }
    inline void build(int rt,int l,int r){
        if(l==r){
            t[rt].minn=a[pre[l]];
            t[rt].tag=0;
            return;
        }
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(rt);
    }
    inline void pushdown(int rt){
        if(!t[rt].tag) return;
        t[lson].tag=t[rson].tag=t[rt].tag;
        t[lson].minn=t[rson].minn=t[rt].tag;
        t[rt].tag=0;
    }
    inline void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l && r<=R){
            t[rt].minn=x;
            t[rt].tag=x;
            return;
        }
        pushdown(rt);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        pushup(rt);
    }
    inline int query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt].minn;
        pushdown(rt);
        int mid=(l+r)>>1;
        int ans=0x3f3f3f3f3f3f3f3f;
        if(L<=mid) ans=min(ans,query(lson,l,mid,L,R));
        if(R>mid) ans=min(ans,query(rson,mid+1,r,L,R));
        pushup(rt);
        return ans;
    }
}Q;
void upd(int u,int v,int x){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        Q.update(1,1,n,dfsx[top[u]],dfsx[u],x);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    Q.update(1,1,n,dfsx[u],dfsx[v],x);
}
int mq;
int find(int u){
    if(u==mq) return -1;
    if(dfsx[u]>=dfsx[mq] || dfsx[u]+siz[u]-1<dfsx[mq]) return 0;
    int now=mq;
    while(top[now]!=top[u]){
        if(fa[top[now]]==u) return top[now];
        now=fa[top[now]];
    }
    return son[u];
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
        }
        for(int i=1;i<=n;++i) read(a[i]);
        read(mq);
        fa[1]=0,dep[1]=1;
        dfs1(1,0),dfs2(1,1);
        Q.build(1,1,n);
        for(int i=1;i<=m;++i){
            int op;
            read(op);
            if(op==1){
                read(mq);
            }
            else if(op==2){
                int x,y,z;
                read(x),read(y),read(z);
                upd(x,y,z);
            }
            else{
                int id;
                read(id);
                int p=find(id);
                if(p==-1) cout<<Q.t[1].minn<<endl;
                else if(p==0) cout<<Q.query(1,1,n,dfsx[id],dfsx[id]+siz[id]-1)<<endl;
                else{
                    int ans=Q.query(1,1,n,1,dfsx[p]-1);
                    if(dfsx[p]+siz[p]-1!=n) ans=min(ans,Q.query(1,1,n,dfsx[p]+siz[p],n));
                    cout<<ans<<endl;
                }
            }
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}