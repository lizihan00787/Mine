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

const int N=2e5+20,M=2e6+20;

int n,m;

struct Min_Cut{
    struct node{
        int nxt,v,cap,f;
    }e[M<<1];
    int head[N],cnt=1;
    int dep[N],cur[N];

    void add(int u,int v,int f){
        e[++cnt].cap=f;
        e[cnt].v=v;
        e[cnt].nxt=head[u];
        e[cnt].f=0;
        head[u]=cnt;
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

int idk[210][210];

int dx[8]={-2,-1,1,2,2,1,-1,-2};
int dy[8]={1,2,2,1,-1,-2,-2,-1};

inline void solve(){
    read(n,m);
    int id=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) 
            id++,idk[i][j]=id;
    for(int i=1,x,y;i<=m;++i) read(x,y),idk[x][y]=0;
    int s=0,t=n*n+1;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(!idk[i][j]) continue;
            if((i+j)%2==0){
                C.add(s,idk[i][j],1),C.add(idk[i][j],s,0);
                for(int k=0;k<8;++k){
                    int x=i+dx[k],y=j+dy[k];
                    if(x>=1 && x<=n && y>=1 && y<=n && idk[x][y])
                        C.add(idk[i][j],idk[x][y],0x3f3f3f3f),C.add(idk[x][y],idk[i][j],0);
                }
            }
            else C.add(idk[i][j],t,1),C.add(t,idk[i][j],0);
        }
    }
    cout<<n*n-m-C.dinic(s,t)<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}