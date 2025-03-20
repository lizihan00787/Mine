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

const int N=1e8+10,M=1e8+10;

int n,k;
int cnt=0;
int p[N];
bool isnp[M];

void Init(int n){
    isnp[1]=1;
    for(int i=2;i<=n;++i){
        if(!isnp[i]) p[++cnt]=i;
        for(int j=1;j<=cnt && i*p[j]<=n;++j){
            isnp[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}

signed main(){
    auto solve=[&](){
        read(n),read(k);
        Init(n);
        for(int i=1;i<=k;++i){
            int x;
            read(x);
            cout<<p[x]<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}