#include<bits/stdc++.h>
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
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
int T=1;
int n;
int a,b,c1,c2;
const int Max=2e5+20;
struct edge{
    int to,nxt,w1,w2;
}e[Max<<1];
int head[Max],dep[Max],cnt=0,ans=0;
int f[Max][33];
int val[Max];
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    f[u][0]=fa;
    for(int i=1;i<=30;++i){
        f[u][i]=f[f[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(to==fa) continue;
            dfs(to,u);
    }
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=31;i>=0;--i){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    }
    if(x==y) return x;
    for(int i=31;i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
void work(int x){
    int u;
    for(int i=head[x];i;i=e[i].nxt){
        int to=e[i].to;
        if(to^f[x][0]){
            work(to);
            val[x]+=val[to];
        }
        else u=i;
    }
    if(e[u].w1*val[x] < e[u].w2) ans+=e[u].w1*val[x];
    else ans+=e[u].w2;
    return;
}
signed main(){
    auto add=[&](int u,int v,int w1,int w2){
        e[++cnt].to=v;
        e[cnt].nxt=head[u];
        e[cnt].w1=w1;
        e[cnt].w2=w2;
        head[u]=cnt;
    };
    auto solve=[&](){
        cin>>n;
        for(int i=1;i<n;++i){
            cin>>a>>b>>c1>>c2;
            add(a,b,c1,c2);
            add(b,a,c1,c2);
        }
        dfs(1,0);
        for(int i=1;i<n;++i){
            val[i]++;
            val[i+1]++;
            val[lca(i,i+1)]-=2;
        }
        work(1);
        cout<<ans<<endl;
        return;
    };
    io();
    //cin>>T;
    while(T--) solve();
    return 0;
}