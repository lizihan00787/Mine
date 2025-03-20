#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define PII pair<int,int>
#define PIP pair<int,PII>
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
const int N=1e5+10,Max=2e5+10;
int n,m;
vector<PIP> g[N];
int cnt1=1;
struct edge{
    int to,nxt,w;
}e[N*25];
int head[N<<2],cnt=0;
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
bool cmp(PIP a,PIP b){
    return a.second.first<b.second.first;
}
int dis[N<<2],vis[N];
void dijkstra(int s){
    memset(dis,0x3f,sizeof(dis));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    dis[s]=0;
    q.push(mk(0,s));
    while(!q.empty()){
        int f=q.top().first,u=q.top().second;
        q.pop();
        if(f!=dis[u]) continue;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to,w=e[i].w;
            if(dis[u]+w<dis[to]){
                dis[to]=dis[u]+w;
                q.push(mk(dis[to],to));
            }
        }
    }
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            g[u].push_back(mk(v,mk(w,++cnt1)));
            g[v].push_back(mk(u,mk(w,++cnt1)));
        }
        for(auto it:g[1]){
            int id=it.second.second,w=it.second.first;
            add(0,id,w);
        }
        for(auto it:g[n]){
            int id=it.second.second,w=it.second.first;
            add(id^1,1,w);
        }
        for(int i=1;i<=n;++i){
            for(auto it:g[i]){
                int id=it.second.second,w=it.second.first;
                add(id,id^1,w);
            }
        }
        for(int i=1;i<=n;++i){
            if(g[i].empty()) continue;
            sort(g[i].begin(),g[i].end(),cmp);
            for(auto it=g[i].begin()+1;it!=g[i].end();++it){
                int x=it->second.second,y=(it-1)->second.second;
                int nw=it->second.first,lw=(it-1)->second.first;
                add(x,y,0);
                add(y,x,nw-lw);
            }
        }
        dijkstra(0);
        cout<<dis[1]<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}