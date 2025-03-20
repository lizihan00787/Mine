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
const int Max=1e5+10,N=2e4+10;
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
int dfx[N],low[N],col,num;
int root;
bool iscut[N];
void tarjan(int u){
    dfx[u]=low[u]=++num;
    int son=0;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(!dfx[to]){
            son++;
            tarjan(to);low[u]=min(low[u],low[to]);
            if((low[to]>=dfx[u] && u!=root) || (u==root && son>1)) iscut[u]=1;
        }
        else low[u]=min(low[u],dfx[to]);
    }
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
                root=i;
                tarjan(i);
            }
        }
        for(int i=1;i<=n;++i) col+=iscut[i];
        cout<<col<<endl;
        for(int i=1;i<=n;++i) if(iscut[i]) cout<<i<<" ";
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}