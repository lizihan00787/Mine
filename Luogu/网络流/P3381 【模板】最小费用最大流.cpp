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
const int Max=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
bool vis[Max];
int n,m,s,t,dis[Max],pre[Max],flow[Max],maxf,minc;
struct edge{
    int to,nxt,w,flow;
}e[Max<<1];
int head[Max],cnt=1;
queue<int> q;
void add(int u,int v,int f,int w){
    e[++cnt].flow=f;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    e[cnt].to=v;
    head[u]=cnt;
}
bool SPFA(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push(s),vis[s]=1,dis[s]=0,flow[s]=1<<30;
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to,w=e[i].w,f=e[i].flow;
            if(f>0 && dis[to]>dis[u]+w){
                dis[to]=dis[u]+w;
                pre[to]=i;
                flow[to]=min(flow[u],f);
                if(!vis[to]){
                    vis[to]=1;
                    q.push(to);
                }
            }
        }
    }
    if(dis[t]==0x3f3f3f3f3f3f3f3f) return 0;
    return 1;
}
void mcmf(){
    while(SPFA(s,t)){
        int now=t;
        maxf+=flow[t];
        minc+=flow[t]*dis[t];
        int p;
        while(now!=s){
            p=pre[now];
            e[p].flow-=flow[t];
            e[p^1].flow+=flow[t];
            now=e[p^1].to;
        }
    }
}
signed main(){
    auto solve=[&](){
        cnt=1;
        read(n),read(m),read(s),read(t);
        for(int i=1;i<=m;++i){
            int u,v,w,f;
            read(u),read(v),read(f),read(w);
            add(u,v,f,w);
            add(v,u,0,-w);
        }
        mcmf();
        cout<<maxf<<" "<<minc<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}