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
const int N=100005,Max=1e6+10;
int h[N];
struct edge{
    int to,w,nxt;
}e[Max<<1];
struct nedge{
    int u,to,w;
}ee[Max<<1];
int head[N],cnt=0,cnt1=0;
void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
int ans1=0;
bool vis[N];
int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int u){
    ans1++;
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        ee[++cnt1].u=u,ee[cnt1].to=e[i].to,ee[cnt1].w=e[i].w;
        int to=e[i].to;
        if(vis[to]) continue;
        dfs(to);
    }
}
bool cmp(nedge a,nedge b){
    if(h[a.to]!=h[b.to]) return h[a.to]>h[b.to];
    return a.w<b.w;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;i++) read(h[i]);
        for(int i=1;i<=m;i++){
            int u,v,w;
            read(u),read(v),read(w);
            if(h[u]>=h[v]) add(u,v,w);
            if(h[v]>=h[u]) add(v,u,w);
        }
        for(int i=1;i<=n;i++) fa[i]=i;
        dfs(1);
        sort(ee+1,ee+cnt1+1,cmp);
        int ans2=0;
        for(int i=1;i<=cnt1;++i){
            auto now=ee[i];
            int u=now.u,to=now.to,w=now.w;
            int fu=find(u),fto=find(to);
            if(fu!=fto){
                ans2+=w;
                fa[fu]=fto;
            }
        }
        cout<<ans1<<' '<<ans2<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}