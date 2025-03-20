#include<bits/stdc++.h>
#define int long long
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int Max=2e6+10,N=5e5+10;
int n,m;
struct edge{
    int to,nxt,u;
}e[Max<<1];
int head[N],cnt=0;
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].u=u;
    head[u]=cnt;
}
int dfx[N],low[N],ans,num;
int st[N],tp=0;
vector<int> bcc[N];
int root;
void tarjan(int u,int fa){
    int son=0;
    dfx[u]=low[u]=++num;
    st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(!dfx[to]){
            son++;
            tarjan(to,u);
            low[u]=min(low[u],low[to]);
            if(low[to]>=dfx[u]){
                ans++;
                while(st[tp+1]!=to) bcc[ans].push_back(st[tp--]);
                bcc[ans].push_back(u);
            }
        }
        else if(to!=fa) low[u]=min(low[u],dfx[to]);
    }
    if(fa==0 && son==0) bcc[++ans].push_back(u);
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v);
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;++i){
            if(!dfx[i]){
                tp=0;
                tarjan(i,0);
            }
        }
        cout<<ans<<endl;
        for(int i=1;i<=ans;++i){
            cout<<bcc[i].size()<<' ';
            for(auto it:bcc[i]) cout<<it<<' ';
            cout<<endl;
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}