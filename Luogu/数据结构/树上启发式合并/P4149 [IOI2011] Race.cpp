#include<bits/stdc++.h>
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=2e5+10;

int n,k,sum=1e9;
int son[N],fa[N],siz[N],flag,dfx[N],tot,id[N],dep[N];
int ww[N];
int dis[N],s[N];
unordered_map<ll,int> dpt;
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}

void dfs1(int u,int f){
    fa[u]=f;
    siz[u]=1;
    dfx[u]=++tot;
    dep[u]=dep[f]+1;
    id[tot]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==f) continue;
        dfs1(to,u);
        ww[to]=e[i].w+ww[u];
        siz[u]+=siz[to];
        if(siz[son[u]]<siz[to]) son[u]=to;
    }
}
void upd(int x,int k){
    int d=ww[x];
    if(k==-1) dpt[d]=0;
    else{
        int tmp=dpt[d];
        if(tmp==0) tmp=1e9;
        dpt[d]=min(tmp,dep[x]);
    }
}
void dfs(int u,int f,bool kep){
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==f || to==son[u]) continue;
        dfs(to,u,0);
    }
    if(son[u]) dfs(son[u],u,1);
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==f || to==son[u]) continue;
        for(int j=0;j<=siz[to]-1;++j){
            int p=id[dfx[to]+i];
            int res=k+2*ww[u]-ww[p];
            if(dpt[res]) sum=min(sum,dpt[res]+dep[p]-2*dep[u]);
        }
        for(int j=0;j<=siz[to]-1;++j) upd(id[dfx[to]+i],1);
    }
    upd(u,1);
    if(dpt[ww[u]+k]) sum=min(sum,dpt[ww[u]+k]-dep[u]);
    if(!kep){
        for(int i=0;i<=siz[u]-1;++i){
            upd(id[dfx[u]+i],-1);
        }
    }
}

signed main(){
    auto solve=[&](){
        read(n),read(k);
        for(int i=1;i<n;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w),add(v,u,w);
        }
        dep[0]=1;
        dfs1(0,0);
        dfs(0,0,0);
        if(sum==1e9) sum=-1;
        cout<<sum<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}