#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
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
const int N=2e5+10;
vector<int> e[N];
int n,col[N],siz[N],maxp[N],rt,vis[N],cnt[N],mk[N],las,tmp[N],tot;
ll ans;
void add(int u,int v) {e[u].push_back(v);e[v].push_back(u);}
int getrt(int u,int fa,int sum){
    siz[u]=1;maxp[u]=0;
    for(auto to:e[u]){
        if(to==fa || vis[to]) continue;
        siz[u]+=(siz[to]=getrt(to,u,sum));
        maxp[u]=max(maxp[u],siz[to]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
    return siz[u];
}
void getdis(int u,int fa){
    if(!mk[col[u]]) cnt[++tot]=col[u];
    mk[col[u]]++;
    for(auto to:e[u]){
        if(vis[to] || to==fa) continue;
        getdis(to,u);
    }
    mk[col[u]]--;
}
void calc(int u){
    tot=las=1,tmp[col[u]]=1;
    for(auto to:e[u]){
        if(vis[to]) continue;
        getdis(to,u);
        for(int i=las;i<=tot;++i) ans+=tmp[cnt[i]];
        for(int i=las;i<=tot;++i) tmp[cnt[i]]++,tmp[col[u]]=1;
        las=tot+1;
    }
    for(int i=1;i<=tot;++i) tmp[cnt[i]]=0;
    tmp[col[u]]=0;
}
void sol(int u){
    vis[u]=1;
    calc(u);
    for(auto to:e[u]){
        if(vis[to]) continue;
        rt=0;
        getrt(to,u,siz[to]);
        sol(to);
    }
    return;
}
signed main(){
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;++i) read(col[i]);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
        }
        maxp[0]=N;rt=0;
        getrt(1,-1,n);
        sol(rt);
        printf("%lld\n",ans);
        for(int i=1;i<=n;++i) e[i].clear(),vis[i]=0;
        ans=0;
    }
    return 0;
}