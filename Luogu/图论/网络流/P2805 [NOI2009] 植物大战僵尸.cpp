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

const int N=1e3+20,M=1e6+20;

namespace Min_Cut{
    struct node{
        int v,nxt,cap,flow;
    }e[M<<1];
    int head[N],cnt=1;
    int dep[N],cur[N];
    void clear(){
        for(int i=2;i<=cnt;++i) e[i]={0,0,0,0};
        cnt=1;
        memset(head,0,sizeof(head));
        memset(cur,0,sizeof(cur));
    }
    void add(int u,int v,int f){
        e[++cnt]={v,head[u],f,0};head[u]=cnt;
        e[++cnt]={u,head[v],0,0};head[v]=cnt;
    }
    bool bfs(int s,int t){
        queue<int> q;
        memset(dep,0,sizeof(dep));
        dep[s]=1;
        q.push(s);
        cur[s]=head[s];
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].v;
                if(!dep[v] && e[i].cap>e[i].flow){
                    cur[v]=head[v];
                    q.push(v);
                    dep[v]=dep[u]+1;
                    if(v==t) return 1;
                }
            }
        }
        return 0;
    }
    int dfs(int u,int t,int flow){
        if(u==t) return flow;
        int sum=0;
        for(int &i=cur[u];i && sum<flow;i=e[i].nxt){
            int v=e[i].v;
            if(dep[v]==dep[u]+1 && e[i].cap>e[i].flow){
                int tmp=dfs(v,t,min(flow-sum,e[i].cap-e[i].flow));
                if(!tmp) dep[v]=0;
                sum+=tmp;
                e[i].flow+=tmp;
                e[i^1].flow-=tmp;
            }
        }
        return sum;
    }
    int Dinic(int s,int t) {int maxf=0;while(bfs(s,t)) maxf+=dfs(s,t,0x3f3f3f3f);return maxf;}
}
using namespace Min_Cut;

int n,m,s=N-1,t=N-2;
int in[N],vis[N],score[N];
vector<int> out[N];

int id(int x,int y) {return x*31+y;}

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(in[id(i,j)]==0){
                q.push(id(i,j));
                vis[id(i,j)]=1;
            }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:out[u])
            if(--in[v]==0 && vis[v]==0) q.push(v),vis[v]=1;
    }
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i){
        int num,x,y;
        for(int j=1;j<=m;++j){
            read(score[id(i,j)]);
            read(num);
            while(num--){
                read(x,y);x++,y++;
                out[id(i,j)].push_back(id(x,y));
                in[id(x,y)]++;
            }
            if(j<m){
                out[id(i,j+1)].push_back(id(i,j));
                in[id(i,j)]++;
            }
        }
    }
    toposort();
    int sum=0;
    for(int i=1;i<=n;++i){  
        for(int j=1;j<=m;++j){
            if(in[id(i,j)]==0){
                int u=id(i,j);
                if(!vis[u]) continue;
                if(score[u]>=0) add(s,u,score[u]),sum+=score[u];
                else add(u,t,-score[u]);
                for(int v:out[u]) if(vis[v]) add(v,u,0x3f3f3f3f);
            }
        }
    }
    cout<<sum-Dinic(s,t)<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}