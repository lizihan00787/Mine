#include<bits/stdc++.h>
#define endl '\n'
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=1e6+20;

int n,w,s;
vector<int> k[N],val[N];
int f[50][5000],g[50][5000];

void init(){
    s=0;
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    for(int i=0;i<=50;++i) val[i].clear(),k[i].clear();
}

inline void solve(){
    while(read(n,w),n!=-1 && w!=-1){
        init();
        for(int i=1;i<=n;++i){
            int x,y,t=0;
            read(x,y);
            while(((x>>t)&1)==0) t++;
            val[t].emplace_back(y);
            k[t].emplace_back((x>>t));
        }
        while((w>>s)) s++;
        s--;
        for(int i=0;i<=s;++i){
            int len=k[i].size();
            if(len==0) continue;
            for(int j=0;j<len;++j)
                for(int p=1000;p>=k[i][j];--p)
                    g[i][p]=max(g[i][p],g[i][p-k[i][j]]+val[i][j]);
        }
        for(int i=0;i<=s;++i){
            for(int j=1000;j>=0;--j){
                for(int p=0;p<=j;++p){
                    if(i==0) f[i][j]=max(f[i][j],g[i][p]);
                    else f[i][j]=max(f[i][j],f[i-1][(j-p)*2+((w>>(i-1))&1)]+g[i][p]);
                }
            }
        }
        cout<<f[s][1]<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}