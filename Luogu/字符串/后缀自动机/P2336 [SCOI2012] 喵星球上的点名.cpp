#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
template<typename P>
inline void read(P &x){
    P ans2=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        ans2=(ans2<<3)+(ans2<<1)+(ch^48);
        ch=getchar();
    }
    x=ans2*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=2e5+20;

struct node{
    cc_hash_table<int,int> ch;
    int len,fa;
}SAM[N];
int las=1,tot=1;
void insert(int c){
    int p=las,np=las=++tot;
    SAM[np].len=SAM[p].len+1;
    for(;p && !SAM[p].ch[c];p=SAM[p].fa) SAM[p].ch[c]=np;
    if(!p) SAM[np].fa=1;
    else{
        int q=SAM[p].ch[c];
        if(SAM[q].len==SAM[p].len+1) SAM[np].fa=q;
        else{
            int nq=++tot;
            SAM[nq]=SAM[q];
            SAM[nq].len=SAM[p].len+1;
            SAM[q].fa=SAM[np].fa=nq;
            for(;p && SAM[p].ch[c]==q;p=SAM[p].fa) SAM[p].ch[c]=nq;
        }
    }
}

int n,m;
vector<int> G[N];
int c[N],dfx[N],siz[N],cnt,dcnt,pos[N],col[N],Q,l=1,r=1,now;
struct nod{
    int l,r,id;
    bool operator < (const nod &a)const{
        return pos[l]^pos[a.l]?pos[l]<pos[a.l]:(pos[l]&1)?r>a.r:r<a.r;
    }
}q[N];
int ans1[N],ans2[N],num[N],ls[N];

void dfs(int u){
    dfx[u]=++dcnt;col[dcnt]=c[u];siz[u]=1;
    for(auto to:G[u]) dfs(to),siz[u]+=siz[to];
}

void add(int x,int id){
    if(!x) return;
    if(num[x]==0) ++now,ls[x]=id;
    ++num[x];
}
void del(int x,int id){
    if(!x) return;
    --num[x];
    if(num[x]==0) --now,ans2[x]+=(id-ls[x]),ls[x]=0;
}

void init(int i){
    int l;
    read(l);
    for(int x,j=1;j<=l;++j) read(x),insert(x),c[las]=i;
    insert(10001);
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i) init(i),init(i);
    for(int i=1;i<=tot;++i) G[SAM[i].fa].push_back(i);
    dfs(1);
    for(int i=1;i<=m;++i){
        int l,j=1;
        read(l);
        while(l--) {int x;read(x);j=SAM[j].ch[x];}
        if(!j) continue;
        q[++Q]={dfx[j],dfx[j]+siz[j]-1,i};
    }
    int s=sqrt(tot);
    for(int i=1;i<=tot;++i) pos[i]=(i-1)/s+1;
    sort(q+1,q+Q+1);
    for(int i=1;i<=Q;++i){
        while(l>q[i].l) add(col[--l],i);
        while(r<q[i].r) add(col[++r],i);
        while(l<q[i].l) del(col[l++],i);
        while(r>q[i].r) del(col[r--],i);
        ans1[q[i].id]=now;
    }
    for(int i=1;i<=m;++i) cout<<ans1[i]<<endl;
    for(int i=1;i<=n;++i) if(ls[i]) ans2[i]+=Q-ls[i]+1;
    for(int i=1;i<=n;++i) cout<<ans2[i]<<' ';
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}