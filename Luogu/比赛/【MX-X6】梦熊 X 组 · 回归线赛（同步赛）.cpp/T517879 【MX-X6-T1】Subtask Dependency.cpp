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

const int N=120;

int n,m;
int a[N][N];
int vis[N];

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            int d;
            read(d);
            for(int j=1;j<=d;++j){
                int k;
                read(k);
                a[i][k]=1;
            }
        }
        read(m);
        for(int i=1;i<=m;++i){
            int sum=0;
            for(int j=1;j<=n;++j){
                read(vis[j]);
                for(int k=1;k<=n;++k){
                    if(a[j][k]) vis[j]&=vis[k];
                }
                sum+=vis[j];
            }
            cout<<sum<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}