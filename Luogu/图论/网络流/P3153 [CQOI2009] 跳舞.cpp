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

const int N=1020,M=1e6+20;

namespace Min_Cut{
    struct node{
        int v,nxt,cap,flow;
    }e[M<<3];
    int head[M<<2],cnt=1;
    int dep[M],cur[M];
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
    int dinic(int s,int t) {int maxf=0;while(bfs(s,t)) maxf+=dfs(s,t,0x3f3f3f3f);return maxf;}
}
using namespace Min_Cut;

int n,k;
int islike[N][N];

bool work(int x){
    int s=0,t=6*n+1;
    for(int i=1;i<=n;++i) add(s,i,x),add(i,i+n,0x3f3f3f3f),add(i,i+2*n,k);
    for(int i=5*n+1;i<=6*n;++i) add(i,t,x),add(i-n,i,0x3f3f3f3f),add(i-2*n,i,k);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(islike[i][j]) add(i+n,j+4*n,1);
            else add(i+2*n,j+3*n,1);
        }
    }
    int maxf=dinic(s,t);
    clear();
    return maxf==x*n?1:0;
}

inline void solve(){
    read(n,k);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            char op;
            cin>>op;
            if(op=='Y') islike[i][j]=1;
        }
    }
    int l=0,r=0x3f3f3f3f,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(work(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}