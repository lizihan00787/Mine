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

const int N=1510,M=4e6+20;

int n,m,q,las=1,cnt;
int fa[M];
int id[N][N];

int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
    if((a=find(a))==(b=find(b))) return (void)(las=0,puts("NIE"));
    return (void)(fa[a]=b,las=1,puts("TAK"));
}


inline void solve(){
    read(n,q);
    m=(n-1)*(n-1)+1;
    for(int i=1;i<=m;++i) fa[i]=i;
    for(int i=0;i<=n;++i) for(int j=0;j<=n;++j) id[i][j]=m;
    for(int i=1;i<n;++i) for(int j=1;j<n;++j) id[i][j]=++cnt;
    while(q--){
        int a,b;
        char op[5];
        scanf(las?"%d%d%s%*d%*d%*s":"%*d%*d%*s%d%d%s",&a,&b,op);
        if(op[0]=='E') unionn(id[a][b-1],id[a][b]);
        else unionn(id[a-1][b],id[a][b]);
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}