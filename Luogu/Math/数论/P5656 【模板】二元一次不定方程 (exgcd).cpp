#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
int a,b,c;
int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int exgcd(int a,int b,int &x,int &y){
    if(b==0) {x=1,y=0;return a;}
    int d=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-(a/b)*y;
    return d;
}
signed main(){
    auto solve=[&](){
        read(a),read(b),read(c);
        int x,y;
        int g=gcd(a,b);
        if(c%g!=0){
            puts("-1");
            return;
        }
        a/=g,b/=g,c/=g;
        x=y=0;
        exgcd(a,b,x,y);
        x*=c,y*=c;
        int p=b,q=a,k;
        if(x<0) k=ceil((1.0-x)/p),x+=p*k,y-=q*k;
        else if(x>=0) k=(x-1)/p,x-=p*k,y+=q*k;
        if(y>0){
            printf("%lld %lld %lld %lld %lld",(y-1)/q+1,x,(y-1)%q+1,x+(y-1)/q*p,y);
        }
        else{
            printf("%lld %lld",x,y+q*(int)ceil((1.0-y)/q));
        }
        puts("");
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}