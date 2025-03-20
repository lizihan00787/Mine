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

int n,m;
int a[N]; 
int cnt=0;
int rtt[N];

struct Stree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int l,r,sum;
    }t[N<<5];
    void build(int &rt,int l,int r){
        rt=++cnt;
        if(l==r) {t[rt].sum=a[l];return;}
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
    }
    void update(int &rt,int l,int r,int k,int val){
        t[++cnt]=t[rt];
        rt=cnt;
        if(l==r) {t[rt].sum=val;return;}
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k,val);
        else update(rson,mid+1,r,k,val);
    }
    int query(int rt,int l,int r,int k){
        if(l==r) return t[rt].sum;
        int mid=(l+r)>>1;
        if(k<=mid) return query(lson,l,mid,k);
        else return query(rson,mid+1,r,k);
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        Q.build(rtt[0],1,n);
        for(int i=1;i<=m;++i){
            int op,ver,k,val;
            read(ver);read(op);
            if(op==1){
                read(k),read(val);
                rtt[i]=rtt[ver];
                Q.update(rtt[i],1,n,k,val);
            }
            else{
                read(k);
                cout<<Q.query(rtt[ver],1,n,k)<<endl;
                rtt[i]=rtt[ver];
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}