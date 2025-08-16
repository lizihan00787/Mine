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

const int N=1e6+20;

namespace Min_Cut{
    struct node{
        int nxt,v,cap,f;
    }e[N];
    int head[N],cnt=1;
    int dep[N],cur[N];

    void add(int u,int v,int f){
        e[++cnt]=(node){head[u],v,f,0};head[u]=cnt;
        e[++cnt]=(node){head[v],u,0,0};head[v]=cnt;
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
                if(!dep[v] && e[i].cap>e[i].f){
                    dep[v]=dep[u]+1;
                    q.push(v);
                    cur[v]=head[v];
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
            if(dep[v]==dep[u]+1 && e[i].cap>e[i].f){
                int tmp=dfs(v,t,min(flow-sum,e[i].cap-e[i].f));
                if(!tmp) dep[v]=0;
                sum+=tmp;
                e[i].f+=tmp;
                e[i^1].f-=tmp;
            }
        }
        return sum; 
    }
    int dinic(int s,int t) {int maxf=0;while(bfs(s,t)) maxf+=dfs(s,t,0x3f3f3f3f);return maxf;}
}
using namespace Min_Cut;

int n,s,t;
int x[N],y[N],z[N],v[N],tot=0;
map<PII,int> q;
bool vis[N];

inline void solve(){
    auto id=[&](int i) {return ((x[i]+y[i]+z[i])%3+3)%3;};
    read(n);
    s=0,t=N-1;
    int ans=0;
    for(int i=1;i<=n;++i){
        int c;
        read(x[i],y[i],z[i],c);
        if(((x[i]+y[i]+z[i])%3+3)%3==0) c*=11;
        else c*=10;
        ans+=c;
        if(!q[mk(x[i]-z[i],y[i]-z[i])]) q[mk(x[i]-z[i],y[i]-z[i])]=++tot;
        v[q[mk(x[i]-z[i],y[i]-z[i])]]+=c;
    }
    for(int i=1;i<=n;++i){
        int now=q[mk(x[i]-z[i],y[i]-z[i])];
        if(vis[now]) continue;
        vis[now]=1;
        if(id(i)==1) add(s,now,0x3f3f3f3f);
        else if(id(i)==0){
            int ss;
            ss=q[mk(x[i]-z[i]-1,y[i]-z[i]-1)];if(ss) add(ss+n,now,0x3f3f3f3f);
            ss=q[mk(x[i]-z[i]+1,y[i]-z[i])];if(ss) add(ss+n,now,0x3f3f3f3f);
            ss=q[mk(x[i]-z[i],y[i]-z[i]+1)];if(ss) add(ss+n,now,0x3f3f3f3f);
            ss=q[mk(x[i]-z[i]+1,y[i]-z[i]+1)];if(ss) add(now+n,ss,0x3f3f3f3f);
            ss=q[mk(x[i]-z[i]-1,y[i]-z[i])];if(ss) add(now+n,ss,0x3f3f3f3f);
            ss=q[mk(x[i]-z[i],y[i]-z[i]-1)];if(ss) add(now+n,ss,0x3f3f3f3f);
        }
        else add(now+n,t,0x3f3f3f3f);
        add(now,now+n,v[now]);
    }   
    ans-=dinic(s,t);
    cout<<fixed<<setprecision(1)<<double(ans)/10<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}