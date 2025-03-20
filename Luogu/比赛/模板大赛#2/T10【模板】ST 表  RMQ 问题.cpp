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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+10;

int n,m;
int st[N][32];

signed main(){
    auto solve=[&](){
        read(n),read(m);
        int x;
        for(int i=1;i<=n;++i) read(x),st[i][0]=x;
        int nl=log2(n);
        for(int j=1;j<=nl;++j){
            for(int i=1;i<=(n-(1<<j)+1);++i){
                st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
        for(int i=1;i<=m;++i){
            int l,r;
            read(l),read(r);
            int len=log2(r-l+1);
            cout<<max(st[l][len],st[r-(1<<len)+1][len])<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}