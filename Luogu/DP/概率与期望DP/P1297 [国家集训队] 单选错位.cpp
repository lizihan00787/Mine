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

int n,A,B,C,a[10000100];
double ans;

signed main(){
    auto solve=[&](){
        read(n),read(A),read(B),read(C),read(a[1]);
        for(int i=2;i<=n;++i) a[i]=((ll)a[i-1]*A+B)%100000001;
        for(int i=1;i<=n;++i) a[i]=a[i]%C+1;
        a[n+1]=a[1];
        for(int i=1;i<=n;++i) ans+=1.0/max(a[i],a[i+1])*1.0;
        printf("%.3lf\n",ans);
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}