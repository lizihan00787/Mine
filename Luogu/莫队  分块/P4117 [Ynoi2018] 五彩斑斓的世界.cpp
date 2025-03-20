#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int N=1e6+100;

int n,m,sum,mx,tag,l,r,klen,block;
int a[N],ans[N],fa[N],rt[N];
int to[N],L[N],R[N];
int siz[N];
struct qu{
    int opt;
    int l,r,x;
}q[N];

inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    if(rt[y]) fa[rt[x]]=rt[y];
    else rt[y]=rt[x],to[rt[y]]=y;
    siz[y]+=siz[x];
    rt[x]=siz[x]=0;
}

void build(int x){
    mx=tag=0;
    for(int i=L[x];i<=R[x];++i){
        mx=max(mx,a[i]);
        if(rt[a[i]]) fa[i]=rt[a[i]];
        else rt[a[i]]=fa[i]=i,to[i]=a[i];
        ++siz[a[i]];
    }
}
void restruct(int x,int l,int r,int nx){
    for(int i=L[x];i<=R[x];++i)
        a[i]=to[find(i)],rt[a[i]]=siz[a[i]]=0,a[i]-=tag;
    for(int i=L[x];i<=R[x];++i) to[i]=0;
    l=max(l,L[x]);r=min(r,R[x]);
    for(int i=l;i<=r;++i) a[i]=a[i]-(a[i]>nx)*nx;
    build(x);
}
void update(int x){
    if((x<<1)<=mx-tag){
        for(int i=tag+1;i<=tag+x;++i) if(rt[i]) merge(i,i+x);
        tag+=x;
    }
    else{
        for(int i=tag+x+1;i<=mx;++i) if(rt[i]) merge(i,i-x);
        if(tag+x<mx) mx=tag+x;
    }
}
void query(int x,int i){
    int l=q[i].l,r=q[i].r,nx=q[i].x;
    if(nx+tag>500000) return;
    if(l<=L[x] && r>=R[x]) ans[i]+=siz[nx+tag];
    else{
        l=max(l,L[x]),r=min(r,R[x]);
        for(int j=l;j<=r;++j) if(to[find(j)]-tag==nx) ++ans[i];
    }
}

signed main(){
    read(n),read(m);
    klen=sqrt(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=m;++i)
        read(q[i].opt),read(q[i].l),read(q[i].r),read(q[i].x);
    block=(n-1)/klen+1;
    for(int i=1;i<=block;++i) L[i]=R[i-1]+1,R[i]=i*klen;
    R[block]=n;
    for(int i=1;i<=block;++i){
        memset(rt,0,sizeof(int)*(n+10));
        memset(siz,0,sizeof(int)*(n+10));
        build(i);
        for(int j=1;j<=m;++j){
            if(L[i]>q[j].r || R[i]<q[j].l) continue;
            else if(q[j].opt==1){
                if(mx-tag<=q[j].x) continue;
                if(q[j].l<=L[i] && R[i]<=q[j].r) update(q[j].x);
                else restruct(i,q[j].l,q[j].r,q[j].x);
            }
            else query(i,j);
        }
    }
    for(int i=1;i<=m;++i) if(q[i].opt==2) write(ans[i]),putchar('\n');
    return 0;
}