#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
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
const int Max=1e6+10;
int n;
struct edge{
    int to,nxt;
}e[Max<<1];
int head[Max],cnt=0;
void add(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
int siz[Max];
int dp[Max];
void dfs1(int u,int fa,int dep){
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa) continue;
        dfs1(to,u,dep+1);
        siz[u]+=siz[to];
    }
    dp[1]+=dep;
}
void dfs2(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa) continue;
        dp[to]=max(dp[to],dp[u]-siz[to]*2+siz[1]);
        dfs2(to,u);
    }
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
            add(v,u);
        }
        dfs1(1,0,0);
        dfs2(1,0);
        int maxx=*max_element(dp+1,dp+n+1);
        for(int i=1;i<=n;++i) if(dp[i]==maxx) {cout<<i<<endl;break;}
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}