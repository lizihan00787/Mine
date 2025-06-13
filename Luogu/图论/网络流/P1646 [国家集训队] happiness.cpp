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

const int N=8e4+20,M=4e6+20;

int m,n;

struct Min_Cut{
    struct node{
        int nxt,v,cap,f;
    }e[M<<1];
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
}C;

const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};

inline void solve(){
    auto id=[&](int x,int y) {return (x-1)*m+y;};
    read(n,m);
    int s=0,t=n*m+1,opt=n*m+1,sum=0;
    for(int i=1;i<=n;++i){
        for(int j=1,x;j<=m;++j){
            read(x);
            sum+=x;
            C.add(s,id(i,j),x);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1,x;j<=m;++j){
            read(x);
            sum+=x;
            C.add(id(i,j),t,x);
        }
    }
    for(int i=1;i<n;++i){
        for(int j=1,x;j<=m;++j){
            read(x);
            sum+=x;
            C.add(s,++opt,x);
            C.add(opt,id(i,j),0x3f3f3f3f);
            C.add(opt,id(i+1,j),0x3f3f3f3f);
        }
    }
    for(int i=1;i<n;++i){
        for(int j=1,x;j<=m;++j){
            read(x);
            sum+=x;
            C.add(++opt,t,x);
            C.add(id(i,j),opt,0x3f3f3f3f);
            C.add(id(i+1,j),opt,0x3f3f3f3f);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1,x;j<m;++j){
            read(x);
            sum+=x;
            C.add(s,++opt,x);
            C.add(opt,id(i,j),0x3f3f3f3f);
            C.add(opt,id(i,j+1),0x3f3f3f3f);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1,x;j<m;++j){
            read(x);
            sum+=x;
            C.add(++opt,t,x);
            C.add(id(i,j),opt,0x3f3f3f3f);
            C.add(id(i,j+1),opt,0x3f3f3f3f);
        }
    }
    cout<<sum-C.dinic(s,t)<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}