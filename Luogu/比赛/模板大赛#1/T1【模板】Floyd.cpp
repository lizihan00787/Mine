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

const int N=110;

int dis[N][N];
int n,m;
int a[N][N];

signed main(){
    auto solve=[&](){
        read(n),read(m);
        memset(dis,0x3f,sizeof(dis));
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            dis[u][v]=dis[v][u]=min(w,dis[u][v]);
        }
        for(int i=1;i<=n;++i) dis[i][i]=0;
        for(int k=1;k<=n;++k){
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cout<<dis[i][j]<<' ';
            }
            cout<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}