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

const int N=1e6+10;

struct Stree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int cov,ans,l,r,len;
    }t[N<<2];
    void pushup(int rt){
        if(t[rt].cov) t[rt].ans=t[rt].len;
        else t[rt].ans=t[lson].ans+t[rson].ans;
    }
    void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l && r<=R) {t[rt].cov+=x,pushup(rt);return;}
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        pushup(rt);
    }
};

signed main(){
    auto solve=[&](){
        
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}