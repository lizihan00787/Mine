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

const int N=120;
const int inf=1e13;

int n,m;
int dis[N][N],mp[N][N];

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(i!=j) dis[i][j]=mp[i][j]=inf;
            }
        }
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            dis[u][v]=min(dis[u][v],w);
            dis[v][u]=min(dis[v][u],w);
            mp[u][v]=min(mp[u][v],w);
            mp[v][u]=min(mp[v][u],w);
        }
        int ans=inf;
        for(int k=1;k<=n;++k){
            for(int i=1;i<k;++i){
                for(int j=i+1;j<k;++j){
                    ans=min(ans,dis[i][j]+mp[i][k]+mp[k][j]);
                }
            }
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                    dis[j][i]=dis[i][j];
                }
            }
        }
        if(ans!=inf) cout<<ans<<endl;
        else cout<<"No solution."<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}