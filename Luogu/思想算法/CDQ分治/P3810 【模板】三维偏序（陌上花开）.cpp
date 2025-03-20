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
int n,k;
struct node{
    int a,b,c,t,ans;
    bool operator < (const node &m)const{
        return m.a<a;
    }
}w[100010];
#define lowbit(x) (x&(-x))
int t[100010];
int getsum(int x){
    int ans;
    while(x){
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
void add(int x,int k){
    while(x<=n){
        t[x]+=k;
        x+=lowbit(x);
    }
}
node pa[100010];
void CDQ(int l,int r){
    int mid=(l+r)>>1,ll=1,rr=mid+1,nown=l;
    if(mid!=l) CDQ(l,mid),CDQ(mid+1,r);
    while(ll<=mid && rr<=r){
        if(w[ll].b<=w[rr].b){
            add(w[i].c,w[i].t);
            pa[nown]=w[ll];ll++;
        }
        else{
            ans[w[rr].num]
        }
    }
}
signed main(){
    auto solve=[&](){
        read(n),read(k);
        for(int i=1;i<=n;++i){
            read(w[i].a),read(w[i].b),read(w[i].c);
            w[i].t=i;
        }
        sort(w+1,w+n+1);
        CDQ(1,n);
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}