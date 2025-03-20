#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int Max=1e5+10,MM=6e6+10;
struct edge{
    int to,nxt;
}e[Max<<1];
int tp[Max],fa[Max],head[Max],cnt=0,dep[Max],son[Max],siz[Max],X[Max],Y[Max],Z[Max];
int n,m,rtt[Max],R,num;
int ans[Max];
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
void dfs1(int u,int f){
    siz[u]=1;dep[u]=dep[f]+1;fa[u]=f;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to!=f){
            dfs1(to,u);
            siz[u]+=siz[to];
            if(siz[to]>siz[son[u]]) son[u]=to;
        }
    }
}
void dfs2(int u,int t){
    tp[u]=t;
    if(!son[u]) return;
    dfs2(son[u],t);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to!=fa[u] && to!=son[u]) dfs2(to,to);
    }
}
int lca(int u,int v){
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]]) swap(u,v);
        u=fa[tp[u]];
    }
    if(dep[u]<dep[v]) return u;
    return v;
}
#define lson (t[rt].l)
#define rson (t[rt].r)
struct node{
    int sum,maxx,l,r;
}t[MM];
void pushup(int rt){
    if(t[lson].sum>=t[rson].sum) t[rt].sum=t[lson].sum,t[rt].maxx=t[lson].maxx;
    else t[rt].sum=t[rson].sum,t[rt].maxx=t[rson].maxx;
}
int update(int rt,int l,int r,int k,int x){
    if(!rt) rt=++num;
    if(l==r) {t[rt].sum+=x,t[rt].maxx=l;return rt;}
    int mid=(l+r)>>1;
    if(k<=mid) lson=update(lson,l,mid,k,x);
    else rson=update(rson,mid+1,r,k,x);
    pushup(rt);
    return rt;
}
int merge(int rt1,int rt2,int l,int r){;
    if(!rt1) return rt2;
    if(!rt2) return rt1;
    if(l==r) {t[rt1].sum+=t[rt2].sum,t[rt1].maxx=l;return rt1;}
    int mid=(l+r)>>1;
    t[rt1].l=merge(t[rt1].l,t[rt2].l,l,mid);t[rt1].r=merge(t[rt1].r,t[rt2].r,mid+1,r);
    pushup(rt1);
    return rt1;
}
void rdfs(int x){
    for(int i=head[x];i;i=e[i].nxt){
        int to=e[i].to;
        if(dep[to]>dep[x]) rdfs(to),rtt[x]=merge(rtt[x],rtt[to],1,R);
    }
    if(t[rtt[x]].sum) ans[x]=t[rtt[x]].maxx;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);int x,y;
        for(int i=1;i<n;++i) read(x),read(y),add(x,y),add(y,x);
        dep[1]=1,dfs1(1,0),dfs2(1,1);
        for(int i=1;i<=m;++i) read(X[i]),read(Y[i]),read(Z[i]),R=max(R,Z[i]);
        for(int i=1;i<=m;++i){
            int la=lca(X[i],Y[i]);
            rtt[X[i]]=update(rtt[X[i]],1,R,Z[i],1);
            rtt[Y[i]]=update(rtt[Y[i]],1,R,Z[i],1);
            rtt[la]=update(rtt[la],1,R,Z[i],-1);
            if(fa[la]) rtt[fa[la]]=update(rtt[fa[la]],1,R,Z[i],-1);
        }
        rdfs(1);
        for(int i=1;i<=n;++i) cout<<ans[i]<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}