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

const int N=2e4+20;

int n,m,s,t;

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

int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void output(int x){
    cout<<x<<' ';
    for(int i=head[x];i;i=e[i].nxt) if(e[i].f==e[i].cap && e[i].v>n) output(e[i].v-n);
}

inline void solve(){
    read(n,m);
    s=0,t=2*n+1;
    for(int i=1;i<=n;++i) add(s,i,1),add(i+n,t,1),fa[i]=i;
    for(int i=1;i<=m;++i){
        int u,v;
        read(u,v);
        add(u,v+n,1);
    }
    int sum=dinic(s,t);
    for(int i=2;i<=cnt;++i)
        if(e[i^1].v>=1 && e[i^1].v<=n && e[i].v>n && e[i].v<t && e[i].f==e[i].cap) fa[find(e[i].v-n)]=find(e[i^1].v);
    for(int i=1;i<=n;++i) if(find(i)==i) output(i),cout<<endl;
    cout<<n-sum<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}