#include<iostream>
#include<cstdio>
#define int long long
#define re register
#define PII pair<int,int>
#define PDI pair<double,int>
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

#define lson (rt<<1)
#define rson (rt<<1|1)

const int N=1e5+10;
const double eps=1e-9;
const int mod1=39989,mod2=1e9;

int n,cnt;
struct line{
    double k,b;
}lx[N*2];
double Y(int id,int x){
    return lx[id].k*x+lx[id].b;
}
int cmp(double x,double y){
    if(x-y>eps) return 1;
    if(y-x>eps) return -1;
    return 0;
}

struct Stree{
    int t[N<<2];
    inline void add(int x0,int y0,int x1,int y1){
        cnt++;
        if(x0==x1) lx[cnt].k=0,lx[cnt].b=max(y1,y0);
        else lx[cnt].k=1.0*(y1-y0)/(x1-x0),lx[cnt].b=y0-lx[cnt].k*x0;
    }
    inline void upd(int rt,int l,int r,int id){
        int &id2=t[rt],mid=(l+r)>>1;
        int midval=cmp(Y(id,mid),Y(id2,mid));
        if(midval==1 || (!midval && id<id2)) swap(id,id2);
        int lval=cmp(Y(id,l),Y(id2,l)),rval=cmp(Y(id,r),Y(id2,r));
        if(lval==1 || (!lval && id<id2)) upd(lson,l,mid,id);
        if(rval==1 || (!rval && id<id2)) upd(rson,mid+1,r,id);
    }
    void update(int rt,int l,int r,int L,int R,int id){
        if(L<=l && r<=R){
            upd(rt,l,r,id);
            return;
        }
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,id);
        if(R>mid) update(rson,mid+1,r,L,R,id);
    }
    PDI pmax(PDI x,PDI y){
        if(cmp(x.first,y.first)==-1) return y;
        else if(cmp(x.first,y.first)==1) return x;
        else return x.second<y.second?x:y;
    }
    PDI query(int rt,int l,int r,int x){
        if(r<x || x<l) return mk(0,0);
        int mid=(l+r)>>1;
        double res=Y(t[rt],x);
        if(l==r) return mk(res,t[rt]);
        return pmax(mk(res,t[rt]),pmax(query(lson,l,mid,x),query(rson,mid+1,r,x)));
    }
}Q;
signed main(){
    auto solve=[&](){
        read(n);
        int las=0;
        for(int i=1;i<=n;++i){
            int op;
            read(op);
            if(op==1){
                int x0,y0,x1,y1;
                read(x0),read(y0),read(x1),read(y1);
                x0=(x0+las-1+mod1)%mod1+1;
                x1=(x1+las-1+mod1)%mod1+1;
                y0=(y0+las-1+mod2)%mod2+1;
                y1=(y1+las-1+mod2)%mod2+1;
                if(x0>x1) swap(x0,x1),swap(y0,y1);
                Q.add(x0,y0,x1,y1);
                Q.update(1,1,mod1,x0,x1,cnt);
            }
            else{
                int x;
                read(x);
                x=(x+las-1+mod1)%mod1+1;
                cout<<(las=Q.query(1,1,mod1,x).second)<<endl;
            }
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}