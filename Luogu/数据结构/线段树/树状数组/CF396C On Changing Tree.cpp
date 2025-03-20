#include<bits/stdc++.h>
#define int long long
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
const int mod=1e9+7;

int n,q;
int dfxl[N],dfxr[N],dep[N],tot=0;
vector<int> g[N];

struct ts{
    #define lowbit(x) (x&(-x))
    int sum[N];
    void addsingle(int x,int k){
        while(x<=n){
            sum[x]+=k;
            sum[x]%=mod;
            x+=lowbit(x);
        }
    }
    int gets(int x){
        int ans=0;
        while(x>=1){
            ans+=sum[x];
            ans%=mod;
            x-=lowbit(x);
        }
        return ans;
    }
    void add(int dfxl,int dfxr,int k){
        addsingle(dfxl,k),addsingle(dfxr+1,-k);
    }
}t1,t2;

void dfs(int u){
    dfxl[u]=++tot;
    for(auto it:g[u]) dep[it]=dep[u]+1,dfs(it);
    dfxr[u]=tot;
}

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=2;i<=n;++i){
            int u;
            read(u);
            g[u].push_back(i);
        }
        dfs(1);
        read(q);
        for(int i=1;i<=q;++i){
            int op;
            read(op);
            if(op==1){
                int u,x,k;
                read(u),read(x),read(k);
                t1.add(dfxl[u],dfxr[u],k%mod);
                t2.add(dfxl[u],dfxr[u],(x+(dep[u]*k))%mod);
            }
            else{
                int u;
                read(u);
                int q1=t1.gets(dfxl[u]);
                int q2=t2.gets(dfxl[u]);
                int ans=(-dep[u]*q1%mod+q2)%mod;
                ans=(ans+mod)%mod;
                cout<<ans<<endl;
            }
        }
    };
    //freopen(.in,'dfxr',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}