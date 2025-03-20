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

int n;
double a[300010];
double f[300010],g[300010],k[300010];

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) scanf("%lf",&a[i]);
        for(int i=1;i<=n;++i){
            g[i]=(g[i-1]+1)*a[i];
            k[i]=(k[i-1]+2*g[i-1]+1)*a[i];
            f[i]=f[i-1]+(3*(g[i-1]+k[i-1])+1)*a[i];
        }
        printf("%.1lf",f[n]);
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}