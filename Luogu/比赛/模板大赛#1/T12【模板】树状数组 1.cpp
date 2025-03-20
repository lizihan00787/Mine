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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=5e5+10;

int n,m;
int x;

struct BIT{
    #define lowbit(x) (x&(-x))
    int sum[N];
    void add(int x,int k){
        while(x<=n){
            sum[x]+=k;
            x+=lowbit(x);
        }
    }
    int get(int x){
        int res=0;
        while(x){
            res+=sum[x];
            x-=lowbit(x);
        }
        return res;
    }
    void adds(int l,int r,int k){
        add(l,k),add(r+1,-k);
    }
    int gets(int l,int r){
        return get(r)-get(l-1);
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(x),Q.add(i,x);
        for(int i=1;i<=m;++i){
            int op;
            read(op);
            if(op==1){
                int x,k;
                read(x),read(k);
                Q.add(x,k);
            }
            else{
                int l,r;
                read(l),read(r);
                cout<<Q.gets(l,r)<<endl;
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}