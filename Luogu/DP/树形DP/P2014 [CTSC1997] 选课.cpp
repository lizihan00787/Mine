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
const int Max=320;
int n,m;
struct edge{
    int to,nxt;
}e[Max<<1];
int head[Max],cnt=0;
void add(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
int dp[Max][Max];
void work(int u){
    for(int i=head[u];i;i=e[i].nxt) work(e[i].to);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        for(int j=m;j>0;--j){
            for(int k=0;k<j;++k){
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[to][k]);
            }
        }
    }
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        ++m;
        for(int i=1;i<=n;++i){
            int fa;
            read(fa),read(dp[i][1]);
            add(fa,i);
        }
        work(0);
        cout<<dp[0][m]<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}