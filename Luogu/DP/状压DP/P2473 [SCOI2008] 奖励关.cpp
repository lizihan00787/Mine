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

const int N=16;

int n,K;
int p[N],sta[N];
double f[105][(1<<N)];

inline void solve(){
    read(K,n);
    for(int i=1;i<=n;++i){
        read(p[i]);
        while(1){
            int x;
            read(x);
            if(!x) break;
            sta[i]=sta[i]|(1<<(x-1));
        }
    }
    for(int i=K;i>=1;--i) for(int j=0;j<(1<<n);++j){
        for(int k=1;k<=n;++k){
            if((j& sta[k])==sta[k]) f[i][j]+=max(f[i+1][j],f[i+1][j | (1<<(k-1))]+p[k]);
            else f[i][j]+=f[i+1][j];
        }
        f[i][j]/=n;
    }
    printf("%.6lf",f[1][0]);

}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}