#include<bits/stdc++.h>
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
const int N=100010,inf=10000010;
struct edge{
    int to,nxt,w;
}e[N<<1];
int n,m,cnt=0,head[N];
int maxp[N],siz[N],dis[N],rem[N];
int vis[N],tet[inf],judge[inf],q[N];
int query[1010];
int sum,rt;
void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
void getrt(int u,int fa){
    siz[u]=1;maxp[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa || vis[to]) continue;
        getrt(to,u);
        siz[u]+=siz[to];
        maxp[u]=max(maxp[u],siz[to]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}
void getdis(int u,int fa){
    rem[++rem[0]]=dis[u];
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa || vis[to]) continue;
        dis[to]=dis[u]+e[i].w;
        getdis(to,u);
    }
}
void calc(int u){
    int p=0;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(vis[to]) continue;
        rem[0]=0,dis[to]=e[i].w;
        getdis(to,u);
        for(int j=rem[0];j;--j){
            for(int k=1;k<=m;++k){
                if(query[k]>=rem[j]){
                    tet[k]|=judge[query[k]-rem[j]];
                }
            }
        }
        for(int j=rem[0];j;--j) q[++p]=rem[j],judge[rem[j]]=1;
    }
    for(int i=1;i<=p;++i) judge[q[i]]=0;
}
void sol(int u){
    vis[u]=judge[0]=1;calc(u);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(vis[to]) continue;
        sum=siz[to];maxp[rt=0]=inf;
        getrt(to,0),sol(rt);
    }
}
signed main(){
    read(n),read(m);
    for(int i=1;i<n;++i){
        int u,v,w;
        read(u),read(v),read(w);
        add(u,v,w),add(v,u,w);
    }
    for(int i=1;i<=m;++i) read(query[i]);
    maxp[rt]=sum=n;
    getrt(1,0);
    sol(rt);
    for(int i=1;i<=m;++i){
        if(tet[i]) printf("AYE\n");
        else printf("NAY\n");
    }
    return 0;
}