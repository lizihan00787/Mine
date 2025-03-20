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

int n,m,k;

signed main(){
    auto solve=[&](){
        read(n),read(m),read(k);
        bool flag=0;
        if(n&1){
            for(int i=1;i*i<=m;++i){
                if(m%i==0){
                    if((i>1 && m/i>=k) || (m/i>1 && i>=k)){
                        flag=1;
                        break;
                    }
                }
            }
        }
        if(flag) cout<<"Timur"<<endl;
        else cout<<"Marsel"<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}