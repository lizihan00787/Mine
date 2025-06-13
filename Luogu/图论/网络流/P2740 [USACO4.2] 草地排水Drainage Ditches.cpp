#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=20010;
int n,m,s,t,u,v;
int w,ans=0,dis[N];
int cnt=0,now[N],head[N];
struct node{
    int to,nxt,w;
}e[N];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}
int bfs(){
    for(int i=1;i<=n;++i) dis[i]=inf;
    queue<int> q;
    q.push(s);
    dis[s]=1;
    now[s]=head[s];
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].nxt){
            int to=e[i].to;
            if(e[i].w>0 && dis[to]==inf){
                q.push(to);
                now[to]=head[to];
                dis[to]=dis[x]+1;
                if(to==t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int x,int sum){
    if(x==t) return sum;
    int k,res=0;
    for(int i=now[x];i&&sum;i=e[i].nxt){
        now[x]=i;
        int to=e[i].to;
        if(e[i].w>0 && dis[to]==dis[x]+1){
            k=dfs(to,min(sum,e[i].w));
            if(k==0) dis[to]=inf;
            e[i].w-=k;
            e[i^1].w+=k;
            res+=k;
            sum-=k;
        }
    }
    return res;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        s=1,t=m;
        for(int i=1;i<=n;++i){
            read(u),read(v),read(w);
            add(u,v,w);
            add(v,u,0);
        }
        while(bfs()){
            ans+=dfs(s,inf);
        }
        cout<<ans<<endl;
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}