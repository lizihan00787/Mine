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

int n,k;
int w[N],son[N],f[N],vis[N],val[N];
vector<int> g[N];
vector<int> s;
int ans=0;

void dfs(int u,int fa){
    f[u]=fa;
    for(auto to:g[u]){
        if(to==fa) continue;
        dfs(to,u);
        if(val[to]>val[son[u]]) son[u]=to;
    }
    val[u]=val[son[u]]+w[u];
}

signed main(){
    auto solve=[&](){
        read(n),read(k);
        for(int i=1;i<=n;++i) read(w[i]);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1,0);
        for(int i=1;i<=n;++i) vis[son[i]]=1;
        for(int i=1;i<=n;++i) if(!vis[i]) s.push_back(val[i]);
        nth_element(s.begin(),s.begin()+k,s.end(),greater<int>());
        int siz=s.size();
        for(int i=0;i<=min(siz,k)-1;++i) ans+=s[i];
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}