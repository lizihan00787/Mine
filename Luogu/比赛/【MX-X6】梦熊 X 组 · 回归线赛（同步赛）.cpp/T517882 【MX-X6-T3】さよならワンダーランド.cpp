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
int a[300010],b[300010];

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) read(a[i]),b[min(n+1,max(1,i-a[i]))]=i;
        for(int i=1;i<=n;++i){
            b[i]=max(b[i-1],b[i]);
            if(b[i] && a[i]<=b[i]-i) cout<<1<<' '<<b[i]-i<<endl;
            else cout<<0<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}