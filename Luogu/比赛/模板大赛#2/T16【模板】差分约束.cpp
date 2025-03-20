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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=5e3+10;

int n,m;
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}

int dis[N],num[N];
bool vis[N];
queue<int> q;

bool SPFA(int u){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[u]=0;
    vis[u]=1;
    q.push(u);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(dis[to]>dis[u]+e[i].w){
                dis[to]=dis[u]+e[i].w;
                if(!vis[to]){
                    if(++num[to]>=n+1) return 0;
                    vis[to]=1;
                    q.push(to);
                }
            }
        }
    }
    return 1;
}

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) add(0,i,0);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(v,u,w);
        }
        if(!SPFA(0)) cout<<"NO"<<endl;
        else{
            for(int i=1;i<=n;++i) cout<<dis[i]<<' ';
            cout<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}