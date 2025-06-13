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

const int N=520,M=1e5+20;

int n,m,s,t;

struct Netflow{
    struct node{
        int v,nxt,cap,f;
    }e[M];
    int head[N],cnt=1;
    int dep[N],cur[N];

    void add(int u,int v,int f){
        e[++cnt].cap=f;
        e[cnt].nxt=head[u];
        e[cnt].v=v;
        e[cnt].f=0;
        head[u]=cnt;
    };
    bool bfs(){
        queue<int> q;
        memset(dep,0,sizeof(dep));
        dep[s]=1;
        cur[s]=head[s];
        q.push(s);
        while(!q.empty()){
            int u=q.front();
            q.pop(); 
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].v;
                if(!dep[v] && e[i].cap>e[i].f){
                    dep[v]=dep[u]+1,q.push(v);
                    cur[v]=head[v];
                    if(v==t) return 1;
                }
            }
        }
        return 0;
    }
    int dfs(int u,int flow){
        if(u==t) return flow;
        int sum=0;
        for(int &i=cur[u];i && sum<flow;i=e[i].nxt){
            int v=e[i].v;
            if(dep[v]==dep[u]+1 && e[i].cap>e[i].f){
                int dis=dfs(v,min(flow-sum,e[i].cap-e[i].f));
                if(!dis) dep[v]=0;
                sum+=dis;
                e[i].f+=dis;
                e[i^1].f-=dis;
            }
        }
        return sum;
    }
    int dinic() {int maxf=0;while(bfs()) maxf+=dfs(s,0x3f3f3f3f);return maxf;}
    void print(int x){
        for(int i=head[x];i;i=e[i].nxt)
            if(e[i].f!=0 && e[i].v!=s) cout<<e[i].v-m<<' ';
    }
}C;


inline void solve(){
    read(m,n);
    int tot=0;
    s=n+m+1,t=n+m+2;
    for(int i=1,x;i<=m;++i){
        read(x),tot+=x;
        for(int j=1;j<=n;++j) C.add(i,j+m,1),C.add(j+m,i,0);
        C.add(s,i,x),C.add(i,s,0);
    }
    for(int i=1,x;i<=n;++i) read(x),C.add(i+m,t,x),C.add(t,i+m,0);
    if(C.dinic()==tot) puts("1");
    else {puts("0");return;}
    for(int i=1;i<=m;++i){
        C.print(i);
        cout<<endl;
    }
}

signed main(){
    // freopen("P3254_11.in","r",stdin);
    // freopen("ana.out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}