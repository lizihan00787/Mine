#include<bits/stdc++.h>
#define endl '\n'
#define int __int128
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
inline void read(int &n){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    n=x*f;
}
inline void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n % 10 + '0');
}
int T=1;

const int N=16;

int n;
int p[N];
int w[N];
int MM;


void exgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b,x,y);
    int z=x;
    x=y,y=z-y*(a/b);
}

int qmul(int a,int b){
    int res=0;
    while(b){
        if(b&1) res=(res+a);
        a=(a+a);
        b>>=1;
    }
    return res;
}

signed main(){
    auto solve=[&](){
        read(n);
        MM=1;
        for(int i=1;i<=n;++i){
            read(p[i]),read(w[i]);
            MM=qmul(MM,p[i]);
        }
        int sum=0;
        for(int i=1;i<=n;++i){
            int a=0,b=0;
            int tmp=MM/p[i];
            exgcd(tmp,p[i],a,b);
            sum+=qmul(w[i],qmul(tmp,((a<0)?(a+p[i]):a)));
            sum=(sum+MM+MM)%MM;
        }
        print((sum+MM+MM)%MM);
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}