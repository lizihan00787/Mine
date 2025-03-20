#include<bits/stdc++.h>
#define endl '\n'
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=1e5+20;

int n;
int a[N],in[N];
vector<int> g[N];

int dfs(int u,int fa){
    int snum=0,maxx=0,s=0;
    for(auto to:g[u]){
        if(to==fa) continue;
        int t=dfs(to,u);
        s+=t;
        maxx=max(maxx,t);
        snum++;
    }
    if(snum==0) return a[u];
    if(maxx>a[u]) {puts("NO");exit(0);}
    if(2*a[u]<s || a[u]>s) {puts("NO");exit(0);}
    return (2*a[u]-s);
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    if(n==2) {cout<<(a[1]==a[2]?"YES":"NO")<<endl;return;}
    int rt=1,maxin=1;
    for(int i=1;i<n;++i){
        int u,v;
        read(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
        in[u]++;in[v]++;
        if(in[u]>maxin) maxin=in[u],rt=u;
        if(in[v]>maxin) maxin=in[v],rt=v;
    }
    if(dfs(rt,0)!=0) puts("NO");
    else puts("YES");
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}