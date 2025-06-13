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

const int N=120,M=1e4+20;

int n,m,s,t,flow;
struct node{
    int v,nxt,f;
}e[M<<1];
int head[N],cnt=1;
int dep[N],ans1[N],ans2[N],cur[N];

bool bfs(){
    queue<int> q;
    memset(dep,0,sizeof(dep));
    q.push(s);
    dep[s]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cur[u]=head[u];
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v,f=e[i].f;
            if(!dep[v] && f) dep[v]=dep[u]+1,q.push(v);
        }
    }
    if(dep[t]>0) return 1;
    return 0;
}
int dfs(int u,int f){
    if(u==t) return f;
    for(int &i=cur[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(dep[v]==dep[u]+1 && e[i].f){
            int dis=dfs(v,min(f,e[i].f));
            if(dis>0){
                e[i].f-=dis;
                e[i^1].f+=dis;
                return dis;
            }
        }
    }
    return 0;
}


inline void solve(){
    auto add=[&](int u,int v,int f){
        e[++cnt].nxt=head[u];
        e[cnt].f=f;
        e[cnt].v=v;
        head[u]=cnt;
    };
    auto dinic=[&](){
        while(bfs()) flow+=dfs(s,0x3f3f3f3f);
    };
    read(m,n);
    s=0,t=n+1;
    while(1){
        int u,v;
        read(u,v);
        if(u==-1 && v==-1) break;
        add(u,v,1);
        add(v,u,0);
    }
    for(int i=1;i<=m;++i) add(s,i,1),add(i,s,0);
    for(int i=m+1;i<=n;++i) add(i,t,1),add(t,i,0);
    dinic();
    if(flow==0) {puts("No Solution");return;}
    cout<<flow<<endl;
    for(int i=2;i<=cnt;i+=2){
        if(e[i].v!=s && e[i^1].v!=s)
        if(e[i].v!=t && e[i^1].v!=t)
        if(e[i^1].f!=0) cout<<e[i^1].v<<' '<<e[i].v<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}