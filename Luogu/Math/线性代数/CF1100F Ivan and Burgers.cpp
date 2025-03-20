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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=5e5+20;

int n,m;
int a[N],ans[N];
int w[52],pos[52];
struct node{
    int l,r,id;
    bool operator < (const node &a) const{
        return r<a.r;
    }
}q[N];

void insert(int x,int id){
    for(int i=51;~i;--i){
        if(!(x>>i)) continue;
        if(!w[i]) {w[i]=x,pos[i]=id;return;}
        if(pos[i]<id) {swap(pos[i],id),swap(w[i],x);}
        x^=w[i];
    }
}
int query(int l){
    int res=0;
    for(int i=51;~i;--i){
        if(!w[i]) continue;
        if(pos[i]<l) continue;
        res=max(res,res^w[i]);
    }
    return res;
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    read(m);
    for(int i=1;i<=m;++i) read(q[i].l),read(q[i].r),q[i].id=i;
    sort(q+1,q+m+1);
    int rr=0;
    for(int i=1;i<=m;++i){
        while(rr<q[i].r){
            rr++;
            insert(a[rr],rr);
        }
        ans[q[i].id]=query(q[i].l);
    }
    for(int i=1;i<=m;++i) cout<<ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}