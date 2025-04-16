#include<bits/stdc++.h>
#define endl '\n'
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=1e5+20,mod=998244353;

int n;
struct node{
    int l,r,v;
};
vector<node> V[N];
int a[N];
int f[N][8],g[N][8];
int sumf[N][8],sumg[N][8];
int st[N][21];

void add(int &a,int b) {b=(b%mod+mod)%mod,(a+b>=mod)?a+=b-mod:a+=b;}

int gcd(int a,int b){
    if(!b) return a;
    return gcd(b,a%b);
}
int cc(int l,int r){
    int k=log2(r-l+1);
    return gcd(st[l][k],st[r-(1<<k)+1][k]);
}
void calcg(int k){
    for(int i=1;i<=n;++i){
        add(g[i][k],sumg[i-1][k-1]);
        add(sumg[i][k],sumg[i-1][k]+g[i][k]);
    }
}
void calcf(int k){
    for(int i=1;i<=n;++i){
        add(f[i][k],sumf[i-1][k-1]);
        for(auto it:V[i]){
            int l=it.l,r=it.r,v=it.v;
            add(f[i][k],v*(sumg[r-1][k-1]-sumg[l-2][k-1])%mod);
        }
        add(sumf[i][k],sumf[i-1][k]+f[i][k]);
    }
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i){
        read(a[i]);
        st[i][0]=a[i];
    }
    for(int j=1;j<=20;++j){
        for(int i=1;i+(1<<(j-1))<=n;++i){
            st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
    for(int i=1;i<=n;++i){
        int r=i,v=a[i];
        while(r>=2){
            v=gcd(v,a[r]);
            int L=2,R=r,ans=r;
            while(L<=R){
                int mid=(L+R)>>1;
                if(cc(mid,i)!=v) L=mid+1;
                else R=mid-1,ans=mid;
            }
            V[i].push_back({ans,r,v});
            r=ans-1;
        }
    }
    for(int i=1;i<=n;++i){
        f[i][1]=gcd(f[i-1][1],a[i]);
        add(sumf[i][1],sumf[i-1][1]+f[i][1]);
        g[i][1]=1;
        sumg[i][1]=i;
    }
    for(int k=2;k<=7;++k) calcg(k);
    for(int k=2;k<=7;++k) calcf(k);
    int ans=0;
    for(int i=1;i<=n;++i) add(ans,f[i][7]);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}