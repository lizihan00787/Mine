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
#define lowbit(x) (x&(-x))
const int N=1e6+10;
int t[N];
int a[N];
int ans[N],vis[N];
struct node{
    int l,r,id;
}s[N];
bool cmp(node a,node b){
    return a.r<b.r;
}
int n,m;
void add(int x,int y){
    while(x<=n){
        t[x]+=y;
        x+=lowbit(x);
    }
    return;
}
int getsum(int x){
    int ans=0;
    while(x){
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            read(a[i]);
        }
        read(m);
        for(int i=1;i<=m;++i){
            read(s[i].l),read(s[i].r);
            s[i].id=i;
        }
        sort(s+1,s+m+1,cmp);
        int pow=1;
        for(int i=1;i<=m;++i){
            for(int j=pow;j<=s[i].r;++j){
                if(vis[a[j]]) add(vis[a[j]],-1);
                add(j,1);
                vis[a[j]]=j;
            }
            pow=s[i].r+1;
            ans[s[i].id]=getsum(s[i].r)-getsum(s[i].l-1);
        }
        for(int i=1;i<=m;++i){
            cout<<ans[i]<<endl;
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}