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

const int N=2010,M=4e6+10;

ll n,x,y;
ll X,Y,S;
ll a[N],ans[N];
bitset<M> f[N];

signed main(){
    auto solve=[&](){
        read(n),read(x),read(y);
        X=x-y,Y=x+y;
        for(int i=1;i<=n;++i) read(a[i]),S+=a[i];
        if(S<abs(X) || S<abs(Y)  || (X+S)%2==1 || (Y+S)%2==1){
            puts("No");
            return;
        }
        X=(X+S)/2;Y=(Y+S)/2;
        f[0][0]=1;
        for(int i=1;i<=n;++i) f[i]=f[i-1]|(f[i-1]<<a[i]);
        if(f[n][X]==0 || f[n][Y]==0){
            puts("No");
            return;
        }
        for(int i=n-1;i>=0;--i){
            ll op=0;
            if(!f[i][X]) {X-=a[i+1],op+=1;}
            if(!f[i][Y]) {Y-=a[i+1],op+=2;}
            ans[i]=op;
        }
        puts("Yes");
        for(int i=0;i<n;++i){
            if(ans[i]==0) cout<<"L";
            if(ans[i]==1) cout<<"D";
            if(ans[i]==2) cout<<"U";
            if(ans[i]==3) cout<<"R";
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}