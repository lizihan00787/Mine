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
    int to,nxt,u,flag;
}e[Max<<1],ed[Max<<1];
int head[N],cnt=0,h[N],s=0;
void add(int u,int v,int flag){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].u=u;
    e[cnt].flag=flag;
    head[u]=cnt;
}
int dfx[N],low[N],st[N],tp,scc[N],num=0,col=0;
int las;
vector<int> ans[N];
void tarjan(int u,int las){
    dfx[u]=low[u]=++num;
    st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(e[i].flag==(las^1)) continue;
        if(!dfx[to]){
            tarjan(to,e[i].flag);
            low[u]=min(low[u],low[to]);
        }
        else low[u]=min(low[u],dfx[to]);
    }
    if(low[u]==dfx[u]){
        col++;
        ans[col].push_back(u);
        while(st[tp]!=u){
            ans[col].push_back(st[tp]);
            --tp;
        }
        --tp;
    }   
}
signed main(){
    read(n),read(m);   
    for(int i=1;i<=m;++i){
        int u,v;
        read(u),read(v);
        add(u,v,i<<1);
        add(v,u,i<<1|1);
    }
    for(int i=1;i<=n;++i) if(!dfx[i]) tarjan(i,0);
    cout<<col<<endl;
    for(int i=1;i<=col;++i){
        cout<<ans[i].size()<<' ';
        for(auto it:ans[i]) cout<<it<<' ';
        cout<<endl;
    }
    return 0;
}