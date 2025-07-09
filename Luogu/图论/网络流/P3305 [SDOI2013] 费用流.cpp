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

const int N=1e4+20;

namespace Min_Cut{
    struct node{
        int v,nxt;
        double f,cap;
    }e[N<<1],ed[N<<1];
    int head[N],cnt=1;
    int dep[N],cur[N];

    void add(int u,int v,double f){
        ed[++cnt]={v,head[u],0,f};head[u]=cnt;
        ed[++cnt]={u,head[v],0,0};head[v]=cnt;
    }
    bool bfs(int s,int t){
        memset(dep,0,sizeof(dep));
        queue<int> q;
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
                    cur[v]=head[v];
                    q.push(v);
                    if(v==t) return 1;
                }
            }
        }
        return 0;
    }
    double dfs(int u,int t,double flow){
        if(u==t) return flow;
        double sum=0;
        for(int &i=cur[u];i && flow>sum;i=e[i].nxt){
            int v=e[i].v;
            if(dep[v]==dep[u]+1 && e[i].cap>e[i].f){
                double tmp=dfs(v,t,min(e[i].cap-e[i].f,flow-sum));
                if(!tmp) dep[v]=0;
                e[i].f+=tmp;
                e[i^1].f-=tmp;
                sum+=tmp;
            }
        }
        return sum;
    }
    double Dinic(int s,int t) {double maxf=0;while(bfs(s,t)) maxf+=dfs(s,t,0x3f3f3f3f);return maxf;}
}
using namespace Min_Cut;

int n,m,p;

inline void solve(){
    read(n,m,p);
    double l=0,r=0;
    for(int i=1;i<=m;++i){
        int u,v,f;
        read(u,v,f);
        add(u,v,f*1.0);
        r=max(r,f*1.0);
    }
    for(int i=2;i<=cnt;++i) e[i]=ed[i];
    double ans=Dinic(1,n);
    printf("%.0lf\n",ans);
    while(r-l>1e-4){
        double mid=(l+r)/2;
        for(int i=2;i<=cnt;++i) e[i].cap=ed[i].cap<mid?ed[i].cap:mid,e[i].f=0.0;
        if(fabs(Dinic(1,n)-ans)>1e-5) l=mid;
        else r=mid;
    }
    printf("%.4lf\n",l*1.0*p);
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}