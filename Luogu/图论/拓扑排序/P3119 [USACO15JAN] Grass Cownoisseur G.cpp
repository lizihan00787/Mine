#include<bits/stdc++.h>
#define int long long
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
int n,m;
const int N=1e5+10,Max=1e5+10;
struct edge{
    int to,nxt,u;
}e[3][Max<<1];
int head[3][N],cnt[3];
int dfx[N],low[N],st[N],tp=0,num=0,scc[N];
int siz[N];
int dp[3][N];
int in[3][N];
int topx[N],numb=0;
void add(int u,int v,int k){
    e[k][++cnt[k]].to=v;
    e[k][cnt[k]].nxt=head[k][u];
    e[k][cnt[k]].u=u;
    head[k][u]=cnt[k];
}
void tarjan(int u){
    dfx[u]=low[u]=++num;
    st[++tp]=u;
    for(int i=head[0][u];i;i=e[0][i].nxt){
        int v=e[0][i].to;
        if(!dfx[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!scc[v]) low[u]=min(low[u],dfx[v]);
    }
    if(low[u]==dfx[u]){
        scc[u]=u;
        siz[u]=1;
        while(st[tp]!=u){
            scc[st[tp]]=u;
            siz[u]++;
            tp--;
        }
        tp--;
    }
}
void topo(int k){
    queue<int> q;
    memset(dp[k],-0x3f,sizeof(dp[k]));
    dp[k][1]=0;
    for(int i=1;i<=n;++i) if(!in[k][i] && scc[i]==i) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[k][u];i;i=e[k][i].nxt){
            int v=e[k][i].to;
            dp[k][v]=max(dp[k][v],dp[k][u]+siz[v]);
            if(--in[k][v]==0) q.push(v);
        }
    }
}
signed main(){
    read(n),read(m);
    for(int i=1;i<=m;++i){
        int u,v;
        read(u),read(v);
        add(u,v,0);
    }
    for(int i=1;i<=n;++i) siz[i]=1;
    for(int i=1;i<=n;++i) if(!dfx[i]) tarjan(i);
    for(int i=1;i<=m;++i){
        if(scc[e[0][i].u]!=scc[e[0][i].to]){
            add(scc[e[0][i].u],scc[e[0][i].to],1);
            add(scc[e[0][i].to],scc[e[0][i].u],2);
            in[1][scc[e[0][i].to]]++;
            in[2][scc[e[0][i].u]]++;
        }
    }
    topo(1);
    topo(2);
    int ans=siz[1];
    for(int i=1;i<=m;++i){
        int u=e[1][i].u,v=e[1][i].to;
        ans=max(ans,max(dp[1][u]+dp[2][v],dp[1][v]+dp[2][u])+siz[1]);
    }
    cout<<ans<<endl;
    return 0;
}