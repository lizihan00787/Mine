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

const int N=4e4+10,inf=0x3f3f3f3f;

int n,k;
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}

int rt,sum,ans=0;
int dis[N],rem[N],siz[N],maxp[N],cz[20020];
bool vis[N];
void getrt(int u,int fa){
    siz[u]=1;maxp[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa || vis[to]) continue;
        getrt(to,u);
        siz[u]+=siz[to];
        maxp[u]=max(siz[to],maxp[u]);
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

int calc(int u,int w){
    rem[0]=0,dis[u]=w;
    getdis(u,0);
    sort(rem+1,rem+rem[0]+1);
    int l=1,r=rem[0],res=0;
    while(l<=r){
        if(rem[l]+rem[r]<=k) res+=r-l,++l;
        else r--;
    }
    return res;
}
void sol(int u){
    vis[u]=1,ans+=calc(u,0);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(vis[to]) continue;
        ans-=calc(to,e[i].w);
        maxp[rt=0]=n;
        sum=siz[to];
        getrt(to,u);
        sol(rt);
    }
}

inline void solve(){
    read(n);
    for(int i=1;i<n;++i){
        int u,v,w;
        read(u,v,w);
        add(u,v,w);
        add(v,u,w);
    }
    read(k);
    maxp[rt=0]=sum=n;
    getrt(1,0);
    sol(rt);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}