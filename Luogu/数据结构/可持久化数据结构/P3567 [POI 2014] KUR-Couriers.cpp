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

const int N=5e5+20,M=710;

int n,m;

#define lson (t[rt].l)
#define rson (t[rt].r)
int root[N],cnt;
struct node{
    int sum,l,r;
}t[N*21];
void insert(int &rt,int l,int r,int x){
    t[++cnt]=t[rt];rt=cnt;
    t[rt].sum++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(x<=mid) insert(lson,l,mid,x);
    else insert(rson,mid+1,r,x);
}
int query(int i,int j,int len,int l=1,int r=n){
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(2*(t[t[j].l].sum-t[t[i].l].sum)>len) return query(t[i].l,t[j].l,len,l,mid);
    if(2*(t[t[j].r].sum-t[t[i].r].sum)>len) return query(t[i].r,t[j].r,len,mid+1,r);
    return 0;
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i){
        int x;
        read(x);
        insert(root[i]=root[i-1],1,n,x);
    }
    for(int i=1;i<=m;++i){
        int l,r;
        read(l,r);
        cout<<query(root[l-1],root[r],r-l+1)<<endl;
    }
}

signed main(){
    // freopen("P4168_1.in","r",stdin);
    // freopen("P4168_1.ans","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}