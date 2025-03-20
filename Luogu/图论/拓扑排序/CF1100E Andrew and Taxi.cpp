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
const int N=1e5+10,Max=1e5+10;
struct edge{
    int to,nxt,u,w;
}e[Max<<1];
int head[N],cnt=0;
int n,m;
int in[N];
int mr[N];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].u=u;
    e[cnt].w=w;
    head[u]=cnt;
}
bool vis[N];
int topx[N];
int num=0;
int ans[N],sum=0;
bool check(int x){
    num=0;
    memcpy(in,mr,sizeof(in));
    memset(vis,0,sizeof(vis));
    memset(topx,0,sizeof(topx));
    queue<int> q;
    for(int i=1;i<=m;++i) if(e[i].w<=x) in[e[i].to]--;
    for(int i=1;i<=n;++i) if(in[i]==0) q.push(i),topx[i]=++num;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(e[i].w<=x) continue;
            if(--in[to]==0) q.push(to),topx[to]=++num;
        }
    }
    if(num!=n) return 0;
    sum=0;
    for(int i=1;i<=m;++i) if(topx[e[i].u]>topx[e[i].to] && e[i].w<=x) ans[++sum]=i;
    return 1;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w);
            in[v]++;
            mr[v]++;
        }
        int l=0,r=1e9+10,k=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid))k=mid,r=mid-1;
            else l=mid+1;
        }
        cout<<k<<' '<<sum<<endl;
        for(int i=1;i<=sum;++i){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
