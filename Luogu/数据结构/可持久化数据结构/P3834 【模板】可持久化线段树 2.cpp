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

const int N=3e5+10;

int n,m;
int a[N],b[N];
int rtt[N];

struct Stree{
    #define lson(x) (t[x].l)
    #define rson(x) (t[x].r)
    #define sum(x) (t[x].sum)
    struct node{
        int sum,l,r;
    }t[N<<5];
    int cnt=0;
    int clone(int rt){
        t[++cnt]=t[rt];
        sum(cnt)=sum(rt)+1;
        return cnt;
    }
    int build(int rt,int l,int r){
        rt=++cnt;
        sum(rt)=0;
        if(l==r) return cnt;
        int mid=(l+r)>>1;
        lson(rt)=build(lson(rt),l,mid);
        rson(rt)=build(rson(rt),mid+1,r);
        return rt;
    }
    int update(int rt,int l,int r,int x){
        int rrt=clone(rt);
        if(l==r) return rrt;
        int mid=(l+r)>>1;
        if(x<=mid) lson(rrt)=update(lson(rt),l,mid,x);
        else rson(rrt)=update(rson(rt),mid+1,r,x);
        return rrt;
    }
    int query(int u,int v,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,x=sum(lson(v))-sum(lson(u));
        if(x>=k) return query(lson(u),lson(v),l,mid,k);
        else return query(rson(u),rson(v),mid+1,r,k-x);
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
        sort(b+1,b+n+1);
        int k=unique(b+1,b+n+1)-(b+1);
        rtt[0]=Q.build(0,1,k);
        for(int i=1;i<=n;++i){
            int t=lower_bound(b+1,b+k+1,a[i])-b;
            rtt[i]=Q.update(rtt[i-1],1,k,t);
        }
        while(m--){
            int x,y,z;
            read(x),read(y),read(z);
            int t=Q.query(rtt[x-1],rtt[y],1,k,z);
            cout<<b[t]<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}