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

const int N=520,M=1e5+2e4+5e3+20;
const double eps=1e-10;

int n,m;
vector<int> G[N];
double a[N][N],g[M],ans;
int d[N],u[M],v[M];

void gauss(){
    for(int i=1;i<=n;++i){
        int max=i;
        for(int j=i+1;j<=n;++j) if(fabs(a[j][i])>fabs(a[max][i])) swap(max,j);
        if(max!=i) for(int j=1;j<=n+1;++j) swap(a[i][j],a[max][j]);
        if(fabs(a[i][i])<eps) continue;
        for(int j=1;j<=n;++j){
            if(j!=i){
                double tmp=a[j][i]/a[i][i];
                for(int k=i+1;k<=n+1;++k) a[j][k]-=tmp*a[i][k];
            }
        }
    }
    for(int i=1;i<=n;++i) a[i][n+1]/=a[i][i];
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
        read(u[i],v[i]);
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
        d[u[i]]++,d[v[i]]++;
    }
    n--;a[1][n+1]=-1.0;
    for(int u=1;u<=n;++u){
        a[u][u]=-1.0;
        for(auto v:G[u]){
            if(v!=n+1) a[u][v]=1.0/d[v];
        }
    }
    gauss();
    for(int i=1;i<=m;++i) g[i]=a[u[i]][n+1]/d[u[i]]+a[v[i]][n+1]/d[v[i]];
    sort(g+1,g+m+1);
    for(int i=1;i<=m;++i) ans+=g[i]*(m-i+1);
    printf("%.3lf\n",ans);
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}