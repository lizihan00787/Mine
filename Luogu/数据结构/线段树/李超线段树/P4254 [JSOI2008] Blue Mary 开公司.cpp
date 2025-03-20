#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
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
int n;
struct line{
    double k,b;
}lx[N*2];
double Y(int id,int x){
    return lx[id].k*(x-1)+lx[id].b;
}
struct Stree{
    int t[N<<2];
    inline void update(int rt,int l,int r,int id){
        if(Y(id,l)>Y(t[rt],l) && Y(id,r)>Y(t[rt],r)) {t[rt]=id;return;}
        if(Y(id,l)<=Y(t[rt],l) && Y(id,r)<=Y(t[rt],r)) return;
        int mid=(l+r)>>1;
        if(lx[t[rt]].k<lx[id].k){
            if(Y(id,mid)>Y(t[rt],mid)) update(lson,l,mid,t[rt]),t[rt]=id;
            else update(rson,mid+1,r,id); 
        }
        else{
            if(Y(id,mid)>Y(t[rt],mid)) update(rson,mid+1,r,t[rt]),t[rt]=id;
            else update(lson,l,mid,id); 
        }
    }
    double query(int rt,int l,int r,int x){
        if(l==r) return Y(t[rt],x);
        int mid=(l+r)>>1;
        double ty=Y(t[rt],x);
        if(x<=mid) return max(ty,query(lson,l,mid,x));
        else return max(ty,query(rson,mid+1,r,x));
    }
}Q;
signed main(){
    auto solve=[&](){
        read(n);
        int cnt=0;
        for(int i=1;i<=n;++i){
            char s[10];
            cin>>s;
            if(s[0]=='P'){
                cnt++;
                scanf("%lf%lf",&lx[cnt].b,&lx[cnt].k);
                Q.update(1,1,50005,cnt);
            }
            else{
                int x;
                read(x);
                printf("%lld\n",(int)Q.query(1,1,50005,x)/100);
            }
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}