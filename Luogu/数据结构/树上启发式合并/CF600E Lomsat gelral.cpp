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

const int N=1e5+10;

int n;
int col[N],cnt[N];
int siz[N],son[N];
struct edge{
    int to,nxt;
}e[N<<1];
int head[N],tot=0;
ll ans[N],sum;
int flag,maxc;

void add(int u,int v){
    e[++tot].to=v;
    e[tot].nxt=head[u];
    head[u]=tot;
}
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa) continue;
        dfs1(to,u);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
    }
}

void count(int u,int fa,int val){
    cnt[col[u]]+=val;
    if(cnt[col[u]]>maxc) maxc=cnt[col[u]],sum=col[u];
    else if(cnt[col[u]]==maxc) sum+=col[u];
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa || to==flag) continue;
        count(to,u,val);
    }
}
void dfs2(int u,int fa,bool kep){
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(to==fa || to==son[u]) continue;
        dfs2(to,u,0); 
    }
    if(son[u]) dfs2(son[u],u,1),flag=son[u];
    count(u,fa,1);
    flag=0;
    ans[u]=sum;
    if(!kep) count(u,fa,-1),sum=maxc=0;
}

signed main(){
    read(n);
    for(int i=1;i<=n;++i) read(col[i]);
    for(int i=1;i<n;++i){
        int u,v;
        read(u),read(v);
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,0,0);
    for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
    cout<<endl;
    return 0;
}