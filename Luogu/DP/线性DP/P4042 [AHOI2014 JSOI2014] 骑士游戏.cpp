#include<bits/stdc++.h>
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=2e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
int in[N];
ll dis[N],sum[N];
struct edge{
    ll nxt,to;
}e[2000010];
int head[N],cnt=0;
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}

struct node{
    int to;
    ll dis;
    friend bool operator < (node a,node b){
        return a.dis>b.dis;
    }
};
priority_queue<node> q;
bool vis[N];

void dijkstra(){
    while(!q.empty()){
        auto u=q.top().to;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            in[to]--;
            sum[to]=min(inf,sum[to]+dis[u]);
            if(!in[to]){
                if(sum[to]<dis[to]){
                    dis[to]=sum[to];
                    q.push({to,dis[to]});
                }
            }
        }
    }
}

signed main(){
    read(n);
    for(int i=1;i<=n;++i){
        int m;
        read(sum[i]),read(dis[i]),read(m);
        q.push({i,dis[i]});
        in[i]=m;
        for(int j=1;j<=m;++j){
            int x;
            read(x);
            add(x,i);
        }
    }
    dijkstra();
    cout<<dis[1]<<endl;
    return 0;
}