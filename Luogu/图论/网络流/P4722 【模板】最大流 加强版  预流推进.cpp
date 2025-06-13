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
const int N=2e4+10,Max=2e5+10,inf=0x3f3f3f3f3f3f3f3f;
int n,m,s,t,h[N],ex[N],gap[N<<1],flow[N];
struct edge{
    int to,nxt,w;
}e[Max<<1];
int head[N],cnt=1;
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}
struct cmp{
    inline bool operator()(int a,int b)const{
        return h[a]<h[b];
    }
};
queue<int> q;
priority_queue<int,vector<int>,cmp> pq;
bool bfs(){
    memset(h+1,0x3f,sizeof(int)*n);
    h[t]=0;q.push(t);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(h[to]>h[u]+1 && e[i^1].w){
                h[to]=h[u]+1;
                q.push(to);
            }
        }
    }
    return h[s]!=inf;
}
void push(int u){
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to,w=e[i].w;
        if(w && h[to]+1==h[u]){
            int dep=min(ex[u],w);
            e[i].w-=dep,e[i^1].w+=dep,ex[u]-=dep,ex[to]+=dep;
            if(to!=s && to!=t && !flow[to]) pq.push(to),flow[to]=1;
            if(!ex[u]) break;
        }
    }
    return;
}
void relabel(int u){
    h[u]=inf;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to,w=e[i].w;
        if(w && h[to]+1<h[u]) h[u]=h[to]+1;
    }
}
int HLPP(){
    if(!bfs()) return 0;
    h[s]=n;
    memset(gap,0,sizeof(int)*(n<<1));
    for(int i=1;i<=n;++i) if(h[i]<inf) ++gap[h[i]];
    int d;
    for(int i=head[s];i;i=e[i].nxt){
        int to=e[i].to,w=e[i].w;
        d=w;
        if(d){
            e[i].w-=d,e[i^1].w+=d,ex[s]-=d,ex[to]+=d;
            if(to!=s && to!=t && !flow[to] && h[to]<inf) pq.push(to),flow[to]=1;
        }
    }
    while(!pq.empty()){
        int u=pq.top();
        pq.pop();
        flow[u]=0;
        push(u);
        if(ex[u]){
            if(!--gap[h[u]]){
                for(int i=1;i<=n;++i)
                    if(i!=s && i!=t && h[i]>h[u] && h[i]<n+1) h[i]=n+1;
            }
            relabel(u),++gap[h[u]];
            pq.push(u);
            flow[u]=1;
        }
    }
    return ex[t];
}
signed main(){
    auto solve=[&](){
        int u,v,w;
        read(n),read(m),read(s),read(t);
        for(int i=1;i<=m;++i){
            read(u),read(v),read(w);
            add(u,v,w);add(v,u,0);
        }
        cout<<HLPP()<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}