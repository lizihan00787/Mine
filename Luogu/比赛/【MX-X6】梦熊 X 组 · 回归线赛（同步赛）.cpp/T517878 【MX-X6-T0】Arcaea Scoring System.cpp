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

int p0,p1,f,l;
int n;
int sum;
const int N=1e7+10;

signed main(){
    auto solve=[&](){
        read(p0),read(p1),read(f),read(l);
        n=p0+p1+f+l;
        sum+=(p0*N+p1*N+f*N/2)/n+p0;
        if(sum>=9900000) cout<<"EX+"<<endl;
        else if(sum>=9800000) cout<<"EX"<<endl;
        else if(sum>=9500000) cout<<"AA"<<endl;
        else if(sum>=9200000) cout<<"A"<<endl;
        else if(sum>=8900000) cout<<"B"<<endl;
        else if(sum>=8600000) cout<<"C"<<endl;
        else cout<<"D"<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}