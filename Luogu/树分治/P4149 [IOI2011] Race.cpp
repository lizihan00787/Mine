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

const int N=2e5+10,inf=0x3f3f3f3f;

int n,k;
struct edge{
    int to,nxt,w;
}e[N<<1];
int cnt=0,head[N];
void add(int u,int v,int w){
    e[++cnt].nxt=head[u];
    e[cnt].w=w;
    e[cnt].to=v;
    head[u]=cnt;
}

int rt,sum,ans;
int siz[N],maxp[N],rem[N],cz[1000010],remm[N];
bool vis[N];
void getrt(int u,int fa){
    siz[u]=1;maxp[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        if(e[i].to==fa || vis[e[i].to]) continue;
        getrt(e[i].to,u);
        siz[u]+=siz[e[i].to];
        maxp[u]=max(maxp[u],siz[e[i].to]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}
void getdis(int u,int fa,int di,int de){
    if(di>k) return;
    rem[++rem[0]]=di;
    remm[rem[0]]=de;
    for(int i=head[u];i;i=e[i].nxt){
        if(e[i].to==fa || vis[e[i].to]) continue;
        getdis(e[i].to,u,di+e[i].w,de+1);
    }
}

void calc(int u){
    cz[0]=0,rem[0]=0;
    for(int i=head[u];i;i=e[i].nxt){
        if(vis[e[i].to]) continue;
        int pd=rem[0];
        getdis(e[i].to,u,e[i].w,1);
        for(int j=pd+1;j<=rem[0];++j) ans=min(ans,remm[j]+cz[k-rem[j]]);
        for(int j=pd+1;j<=rem[0];++j) cz[rem[j]]=min(remm[j],cz[rem[j]]);
    }
    for(int i=1;i<=rem[0];++i) cz[rem[i]]=inf;
}

void sol(int u){
    vis[u]=1;
    calc(u);
    for(int i=head[u];i;i=e[i].nxt){
        if(vis[e[i].to]) continue;
        rt=0;
        sum=siz[e[i].to];
        getrt(e[i].to,u);sol(rt);
    }
}

inline void solve(){
    read(n,k);
    ans=inf;
    for(int i=1;i<n;++i){
        int u,v,w;
        read(u,v,w);
        u++,v++;
        add(u,v,w);
        add(v,u,w);
    }
    maxp[0]=(sum=n)+1;
    getrt(1,0);
    memset(cz,0x3f,sizeof(cz));
    sol(rt);
    if(ans>=n) cout<<-1<<endl;
    else cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}