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
const int N=1e5+10;
#define lson (rt<<1)
#define rson (rt<<1|1)
int n,m;
int a[N];
struct edge{
    int to,nxt,u;
}e[N<<1];
int cnt=0,head[N];
int siz[N],dep[N],fa[N],top[N],dfsx[N],pre[N],son[N],tot=0;
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
    dfsx[u]=++tot,pre[tot]=u,top[u]=tp;
    if(son[u]) dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa[u] || to==son[u]) continue;
        dfs2(to,to);
    }
}
struct node{
    int l,r;
    int sum;
    int tag;
}t[N<<2];
struct Stree{
    void pushup(int rt){
        t[rt].sum=t[lson].sum+t[rson].sum;
        if(t[lson].r==t[rson].l) t[rt].sum--;
        t[rt].l=t[lson].l;
        t[rt].r=t[rson].r;
    }
    void pushdown(int rt){
        if(!t[rt].tag) return;
        t[lson].tag=t[rt].tag;
        t[rson].tag=t[rt].tag;
        t[lson].sum=1;
        t[rson].sum=1;
        t[lson].l=t[lson].r=t[rson].l=t[rson].r=t[rt].tag;
        t[rt].tag=0;
    }
    void build(int rt,int l,int r){
        if(l==r){
            t[rt].sum=1;
            t[rt].l=a[pre[l]];
            t[rt].r=a[pre[l]];
            t[rt].tag=0;
            return;
        }
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(rt);
    }
    void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l && r<=R){
            t[rt].tag=x;
            t[rt].sum=1;
            t[rt].l=t[rt].r=x;
            return;
        }
        pushdown(rt);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        pushup(rt);
    }
    node query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R){
            return {t[rt].l,t[rt].r,t[rt].sum,t[rt].tag};
        }
        int mid=(l+r)>>1;
        pushdown(rt);
        node ans={0,0,0},m={0,0,0};
        if(L<=mid) ans=query(lson,l,mid,L,R);
        if(R>mid){
            m=query(rson,mid+1,r,L,R);
            if(!ans.sum) return m;
            ans.sum+=m.sum-(t[lson].r==t[rson].l);
            ans.r=m.r;
        }
        return ans;
    }
}Q;
void upd(int u,int v,int x){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        Q.update(1,1,n,dfsx[top[u]],dfsx[u],x);
        u=fa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    Q.update(1,1,n,dfsx[v],dfsx[u],x);
}
node s;
int qsum(int u,int v){
    int ans=0,upre=-1,vpre=-1;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v),swap(upre,vpre);
        s=Q.query(1,1,n,dfsx[top[u]],dfsx[u]);
        ans+=s.sum;
        u=fa[top[u]];
        if(s.r==upre) ans--;
        upre=s.l;
    }
    if(dep[u]<dep[v]) swap(u,v),swap(upre,vpre);
    s=Q.query(1,1,n,dfsx[v],dfsx[u]);
    ans+=s.sum;
    if(s.r==upre) ans--;
    if(s.l==vpre) ans--;
    return ans;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
        }
        fa[1]=0,dep[1]=1;
        dfs1(1,-1),dfs2(1,1);
        Q.build(1,1,n);
        for(int i=1;i<=m;++i){
            char op;
            cin>>op;
            if(op=='Q'){
                int u,v;
                read(u),read(v);
                cout<<qsum(u,v)<<endl;
            }
            else{
                int u,v,x;
                read(u),read(v),read(x);
                upd(u,v,x);
            }
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}