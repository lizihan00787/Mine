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

const int N=1e6+20,M=1e6+20;

struct node{
    int nxt,v,w,flow;
}e[M<<1];
int dis[N],pre[N],flow[N],maxf,minc,cnt=1,head[N],s,t;
bool vis[N];
void clear(){
    for(int i=1;i<=cnt;++i) e[i].w=e[i].flow=e[i].nxt=e[i].v=0;
    memset(head,0,sizeof(head));
    minc=maxf=0;
    cnt=1;
}
void add(int u,int v,int f,int w){
    e[++cnt]=(node){head[u],v,w,f};head[u]=cnt;
    e[++cnt]=(node){head[v],u,-w,0};head[v]=cnt;
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
            int v=e[i].v,w=e[i].w,f=e[i].flow;
            if(f>0 && dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                pre[v]=i;
                flow[v]=min(flow[u],f);
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
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
        minc+=flow[t]*dis[t];
        int p;
        while(now!=s){
            p=pre[now];
            e[p].flow-=flow[t];
            e[p^1].flow+=flow[t];
            now=e[p^1].v;
        }
    }
}

int n,m;
int c[20][100];


inline void solve(){
	read(n,m),s=2*n+1;t=s+1;
	for(int i=1,w;i<=n;i++){read(w);add(s,i,1,0),add(s,i+n,1,w),add(i+n,t,1,0);}
	for(int i=1,u,v,w;i<=m;i++) 
	{
		read(u,v,w);
		if(u<v) add(u,v+n,1,w);
		if(u>v) add(v,u+n,1,w);
	}
    mcmf();
    printf("%d",minc);
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}