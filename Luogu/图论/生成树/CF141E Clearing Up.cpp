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

const int N=1e3+20,M=1e5+20;

int n,k;
struct edge{
    int u,v,id;
}s[M],m[M];
int f[N];
bool isf[M],ans[M];
int cnts=0,cntm=0;

int find(int x){
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}

inline void solve(){
    read(n,k);
    for(int i=1;i<=n;++i) f[i]=i;
    if(n%2==0) {puts("-1");return;}
    for(int i=1;i<=k;++i){
        int u,v;
        char col;
        read(u,v);
        scanf("%c",&col);
        if(col=='S') s[++cnts]={u,v,i};
        else m[++cntm]={u,v,i};
    }
    int cnt1=0,cnt2=0;
    for(int i=1;i<=cnts;++i){
        int u=find(s[i].u),v=find(s[i].v);
        if(u!=v){
            f[u]=v;
            cnt1++;
        }
    }
    if(cnt1<(n-1)/2) {puts("-1");return;}
    for(int i=1;i<=cntm;++i){
        int u=find(m[i].u),v=find(m[i].v);
        if(u!=v){
            isf[i]=1;
            f[u]=v;
            cnt2++;
        }
    }
    if(cnt1+cnt2<n-1) {puts("-1");return;}
    for(int i=1;i<=n;++i) f[i]=i;
    for(int i=1;i<=cntm;++i){
        if(isf[i]){
            int u=find(m[i].u),v=find(m[i].v);
            if(u!=v) f[u]=v,ans[m[i].id]=1;
        }
    }
    for(int i=1;i<=cntm && cnt2<(n-1)/2;++i){
        if(!isf[i]){
            int u=find(m[i].u),v=find(m[i].v);
            if(u!=v) f[u]=v,ans[m[i].id]=1,cnt2++;
        }
    }
    if(cnt2<(n-1)/2) {puts("-1");return;}
    for(int i=1;i<=cnts;++i){
        int u=find(s[i].u),v=find(s[i].v);
        if(u!=v) f[u]=v,ans[s[i].id]=1;
    }
    cout<<n-1<<endl;
    for(int i=1;i<=k;++i) if(ans[i]) cout<<i<<' ';
    cout<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}