#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=520,k=2333;

int n,m,h,w;
int a[N][N];

inline void solve(){
    read(n,m,h,w);
    int res=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(i%h==0 && j%w==0) a[i][j]=-(k*(h*w-1)+1);
            else a[i][j]=k;
            res+=a[i][j];
        }
    }
    if(res<=0) puts("No");
    else{
        puts("Yes");
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cout<<a[i][j]<<' ';
            }
            cout<<endl;
        }
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}