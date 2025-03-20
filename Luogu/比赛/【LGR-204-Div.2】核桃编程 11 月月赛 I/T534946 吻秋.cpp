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

const int N=10020;

int n,m,q;
int a[22][20010];

signed main(){
    auto solve=[&](){
        read(n),read(m),read(q);
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                read(a[i][j]);
            }
        }
        for(int pp=1;pp<=q;++pp){
            int op,x,y;
            read(op),read(x),read(y);
            if(op==1){
                vector<int> q;
                for(int i=1;i<=n;++i) q.push_back(a[x][i]),q.push_back(a[y][i]);
                sort(q.begin(),q.end());
                for(int i=1;i<=n;++i) a[x][i]=q[i-1];
                for(int i=n+1;i<=n*2;++i) a[y][i-n]=q[i-1];
            }
            else{
                cout<<a[x][y]<<endl;
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}