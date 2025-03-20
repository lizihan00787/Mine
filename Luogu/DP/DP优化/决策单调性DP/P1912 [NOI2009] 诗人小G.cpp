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

const int N=1e5+10;

ll n,L,P,s[N*5],k[N*5];
int pr[N];
long double dp[N*5];
char str[N][33];

ll q[N];

long double qpow(long double a,ll b){
    long double res=1;
    while(b){
        if(b&1ll) res=res*a;
        a=a*a;
        b>>=1ll;
    }
    return res;
}
long double F(int i,int x){
    return dp[i]+qpow(abs(s[x]-s[i]+x-i-1-L),P);
}
int bound(int x,int y){
    if(F(x,n)<F(y,n)) return n+1;
    int l=y,r=n,res=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(F(x,mid)>=F(y,mid)) r=mid-1,res=mid;
        else l=mid+1;
    }
    return res;
}

signed main(){
    auto solve=[&](){
        read(n),read(L),read(P);
        for(int i=1;i<=n;++i){
            scanf("%s",str[i]);
            s[i]=s[i-1]+strlen(str[i]);
            k[i]=0,dp[i]=1e19;
        }
        int h=1,t=1;
        for(int i=1;i<=n;++i){
            while(h<t && bound(q[h],q[h+1])<=i) ++h;
            dp[i]=F(k[i]=q[h],i);
            while(h<t && bound(q[t],i)<=bound(q[t-1],q[t])) --t;
            q[++t]=i;
        }
        if(dp[n]>1e18) puts("Too hard to arrange");
        else{
            printf("%lld\n",(long long)dp[n]);
            int top=0;
            for(int tmp=n;tmp;tmp=k[tmp]) pr[++top]=tmp;
            pr[++top]=0;
            for(int i=top;i>1;--i){
                for(int j=pr[i]+1;j<pr[i-1];++j){
					printf("%s ",str[j]);
                }
                printf("%s\n",str[pr[i-1]]); 
            }
        }
        puts("--------------------");
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}