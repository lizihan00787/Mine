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

const int N=5020,mod=998244353;

int n,m;
int l[N],r[N],f[N][N],inv[N],g[N];
int a[N][N],b[N][N];
void add(int &a,int b) {a=(a+b>=mod)?a+b-mod:a+b;}
void sub(int &a,int b) {a=(a<b)?a-b+mod:a-b;}

inline void solve(){
    read(n);inv[1]=1;
    for(int i=2;i<=n;++i) read(l[i],r[i]),inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    read(m);
    for(int u,v,w,i=1;i<=m;++i){
        read(u,v,w);
        add(f[max(u,v)][min(u,v)],w%mod);
    }
    for(int j=n;j>=1;--j){
        for(int i=n;i>j;--i){
            add(a[i][j],a[i+1][j]);add(f[i][j],a[i][j]);
            add(b[i][j],b[i][j+1]);add(f[i][j],b[i][j]);
            add(g[i],f[i][j]);
            int z=1ll*f[i][j]*inv[r[i]-l[i]+1]%mod;
            if(j<l[i]) add(a[r[i]][j],z),sub(a[l[i]-1][j],z);
            else if(r[i]<j) add(b[j][r[i]],z),sub(b[j][l[i]-1],z);
            else{
                add(a[r[i]][j],z),sub(a[j][j],z);
                add(b[j][j-1],z),sub(b[j][l[i]-1],z);
            }
        }
    }
    for(int i=2;i<=n;++i) cout<<g[i]<<' ';
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}