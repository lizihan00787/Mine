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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=5020,M=2e5+10;

int n,m;
int fa[N];
struct edge{
    int u,to,w;
    bool operator < (const edge &a) const{
        return w<a.w;
    }
}e[M<<1];
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
    int x=find(a),y=find(b);
    if(fa[x]!=y) fa[x]=y;
}

int Kruskal(){
    int cnt=n-1;
    int sum=0;
    for(int i=1;i<=m;++i){
        auto tmp=e[i];
        int u=tmp.u,v=tmp.to,w=tmp.w;
        if(find(u)!=find(v)) unionn(u,v),sum+=w,cnt--;
        if(!cnt) return sum;
    }
    if(cnt) return -1;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int i=1;i<=m;++i){
            read(e[i].u),read(e[i].to),read(e[i].w);
        }
        sort(e+1,e+m+1);
        int num=Kruskal();
        if(num!=-1) cout<<num<<endl;
        else cout<<"orz"<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}