#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
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

const int N=500,M=1e6+20;

gp_hash_table<string,int> q;
int n,m,s,t;
struct edge{
    int to,nxt,w,flow;
}e[M<<1],ed[M<<1];
int head[N],cnt=1,val;
int dis[N],pre[N],flow[N],maxf,maxc;
bool vis[N];

void add(int u,int v,int f,int w){
    e[++cnt].flow=f;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    e[cnt].to=v;
    head[u]=cnt;
}


bool SPFA(int s,int t){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push(s),vis[s]=1,dis[s]=0,flow[s]=1<<30;
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to,w=e[i].w,f=e[i].flow;
            if(f>0 && dis[to]>dis[u]+w){
                dis[to]=dis[u]+w;
                pre[to]=i;
                flow[to]=min(flow[u],f);
                if(!vis[to]){
                    vis[to]=1;
                    q.push(to);
                }
            }
        }
    }
    if(dis[t]==0x3f3f3f3f) return 0;
    return 1;
}

void mcmf(){
    while(SPFA(s,t)){
        int now=t;
        maxf+=flow[t];
        maxc+=flow[t]*dis[t];
        int p;
        while(now!=s){
            p=pre[now];
            e[p].flow-=flow[t];
            e[p^1].flow+=flow[t];
            now=e[p^1].to;
        }
    }
}

string ss[N];
string a,b;

void dfs1(int x){
    cout<<ss[x]<<endl;
    vis[x]=1;
    for(int i=head[x];i;i=e[i].nxt)
        if(e[i].to>n && e[i].to<=2*n && e[i].flow==0) {dfs1(e[i].to-n);break;}
}
void dfs2(int x){
    vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to>n && e[i].to<=2*n && e[i].flow==0 && !vis[e[i].to-n]){dfs2(e[i].to-n);}
    cout<<ss[x]<<endl;
}

inline void solve(){
    read(n,m);
    s=0,t=2*n+1;
    for(int i=1;i<=n;++i) cin>>ss[i],q[ss[i]]=i;
    bool f=0;
    for(int i=1;i<=m;++i){
        cin>>a>>b;
        int x=q[a],y=q[b];
        if(x>y) swap(x,y);
        if(x==1 && y==n) f=1;
        add(x,y+n,1,0),add(y+n,x,0,0);
    }
    add(s,n+1,0x3f3f3f3f,0),add(n+1,s,0,0);
    add(n,t,0x3f3f3f3f,0),add(t,n,0,0);
    for(int i=1;i<=n;++i)
        if(i!=1 && i!=n) add(i+n,i,1,-1),add(i,i+n,0,1);
        else add(i+n,i,2,-1),add(i,i+n,0,1);
    mcmf();
    if(maxf==2) cout<<-maxc-2<<endl;
    else if(maxf==1 && f) return (void)(cout<<2<<endl<<ss[1]<<endl<<ss[n]<<endl<<ss[1]<<endl);
    else return (void)(printf("No Solution!\n"));
    memset(vis,0,sizeof(vis));
    dfs1(1),dfs2(1);
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}