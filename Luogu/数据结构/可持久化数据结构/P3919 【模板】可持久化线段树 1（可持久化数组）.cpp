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

const int N=1e6+10;

int n,m;
int a[N];
int rtt[N];

struct stree{
    #define lson(rt) (t[rt].ls)
    #define rson(rt) (t[rt].rs)
    #define val(rt) (t[rt].val)
    struct node{
        int val,ls,rs;
    }t[N<<5];
    int cnt=0;
    int clone(int rt){
        t[++cnt]=t[rt];
        return cnt;
    }
    int build(int rt,int l,int r){
        rt=++cnt;
        if(l==r){
            t[rt].val=a[l];
            return cnt;
        }
        int mid=(l+r)>>1;
        lson(rt)=build(lson(rt),l,mid);
        rson(rt)=build(rson(rt),mid+1,r);
        return rt;
    }
    int update(int rt,int l,int r,int k,int x){
        rt=clone(rt);
        if(l==r) val(rt)=x;
        else{
            int mid=(l+r)>>1;
            if(k<=mid) lson(rt)=update(lson(rt),l,mid,k,x);
            else rson(rt)=update(rson(rt),mid+1,r,k,x);
        }
        return rt;
    }
    int query(int rt,int l,int r,int k){
        if(l==r) return val(rt);
        int mid=(l+r)>>1;
        if(k<=mid) return query(lson(rt),l,mid,k);
        else return query(rson(rt),mid+1,r,k);
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        rtt[0]=Q.build(0,1,n);
        for(int i=1;i<=m;++i){
            int ver,op,k,x;
            read(ver),read(op),read(k);
            if(op==1){
                read(x);
                rtt[i]=Q.update(rtt[ver],1,n,k,x);
            }
            else{
                cout<<Q.query(rtt[ver],1,n,k)<<endl;
                rtt[i]=rtt[ver];
            }
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}