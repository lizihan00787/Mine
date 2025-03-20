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
const int Max=1e5+10,N=1e4+10;
int n,m;
struct edge{
    int to,nxt,u;
}e[Max<<1];
int head[N],cnt=0;
void add(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].u=u;
    head[u]=cnt;
}
int dfx[N],low[N],st[N],tp,scc[N],sccsize[N],num=0,col=0;
vector<int> ans[N];
void tarjan(int u){
    dfx[u]=low[u]=++num;
    st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(!dfx[to]){
            tarjan(to);
            low[u]=min(low[u],low[to]);
        }
        else if(!scc[to]){
            low[u]=min(low[u],dfx[to]);
        }
    }
    if(low[u]==dfx[u]){
        col++;
        ++sccsize[col];
        ans[col].push_back(u);
        while(st[tp]!=u){
            ++sccsize[col];
            ans[col].push_back(st[tp]);
            scc[st[tp]]=col;
            --tp;
        }
        --tp;
        scc[u]=col;
    }
}
bool vis[N];
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
        }
        for(int i=1;i<=n;++i) if(!dfx[i]) tarjan(i);
        cout<<col<<endl;
        for(int i=1;i<=col;++i) sort(ans[i].begin(),ans[i].end());
        for(int i=1;i<=n;++i){
            if(vis[scc[i]]) continue;
            vis[scc[i]]=1;
            for(auto it:ans[scc[i]]){
                cout<<it<<' ';
            }
            cout<<endl;
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
