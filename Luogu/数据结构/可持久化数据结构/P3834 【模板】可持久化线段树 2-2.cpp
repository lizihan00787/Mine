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

const int N=2e5+10;

int n,m,cnt=0;
int a[N],b[N];
int rtt[N];

struct Stree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int l,r,sum;
    }t[N<<5];
    void build(int &rt,int l,int r){
        rt=++cnt;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
    }
    void update(int &rt,int l,int r,int k){
        t[++cnt]=t[rt],rt=cnt,t[rt].sum++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k);
        else update(rson,mid+1,r,k);
    }
    int query(int rt1,int rt2,int l,int r,int k){
        int res=0,mid=(l+r)>>1,x=t[t[rt2].l].sum-t[t[rt1].l].sum;
        if(l==r) return l;
        if(x>=k) res=query(t[rt1].l,t[rt2].l,l,mid,k);
        else res=query(t[rt1].r,t[rt2].r,mid+1,r,k-x);
        return res;
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
        sort(b+1,b+n+1);
        int nn=unique(b+1,b+n+1)-b-1;
        Q.build(rtt[0],1,nn);
        for(int i=1;i<=n;++i){
            int p=lower_bound(b+1,b+nn+1,a[i])-b;
            rtt[i]=rtt[i-1];
            Q.update(rtt[i],1,nn,p);
        }
        for(int i=1;i<=m;++i){
            int l,r,k;
            read(l),read(r),read(k);
            int lp=Q.query(rtt[l-1],rtt[r],1,nn,k);
            cout<<b[lp]<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}