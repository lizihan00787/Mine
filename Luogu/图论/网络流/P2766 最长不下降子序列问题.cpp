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

const int N=1e3+20,M=2e6+20;

int n;
int a[N];

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

int dp[N];

inline void solve(){
    read(n);
    int s=0,t=2*n+1,ans=0,sum=0;
    for(int i=1;i<=n;++i) read(a[i]),dp[i]=1;
    if(n==1) {cout<<"1\n1\n1\n";return;}
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j) if(a[j]<=a[i]) dp[i]=max(dp[i],dp[j]+1);
    for(int i=1;i<=n;++i) ans=max(ans,dp[i]);
    cout<<ans<<endl;
    for(int i=1;i<=n;++i){
        if(dp[i]==1) C.add(s,i,1);
        if(dp[i]==ans) C.add(i+n,t,1);
    }
    for(int i=1;i<=n;++i) C.add(i,i+n,1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j) if(a[j]<=a[i] && dp[j]+1==dp[i]) C.add(j+n,i,1);
    cout<<(sum=C.dinic(s,t))<<endl;
    C.add(1,1+n,0x3f3f3f3f),C.add(s,1,0x3f3f3f3f);
    if(dp[n]==ans) C.add(n,n+n,0x3f3f3f3f),C.add(n+n,t,0x3f3f3f3f);
    cout<<sum+C.dinic(s,t)<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}