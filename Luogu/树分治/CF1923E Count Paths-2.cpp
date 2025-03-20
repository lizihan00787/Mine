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

int n;
int col[N];
vector<int> g[N];
int maxp[N],siz[N],fa[N],vis[N];
int rt=1,sum=0;

void getrt(int u,int fa){
    siz[u]=1;
    for(auto to:g[u]){
        if(to==fa || vis[to]) continue;
        getrt(to,u);
        siz[u]+=siz[to];
        maxp[u]=max(maxp[u],siz[to]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}


void sol(){

}

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) read(col[i]);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        sol();
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}