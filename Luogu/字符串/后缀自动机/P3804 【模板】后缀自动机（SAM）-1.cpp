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

const int N=2e6+20;

struct node{
    int ch[26];
    int fa,len;
}SAM[N];
ll siz[N];

int las=1,tot=1;
void insert(int c){
    int p=las,np=las=++tot;
    siz[np]++;
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

char s[N];
int n;
vector<int> G[N];
ll ans;

void dfs(int u){
    for(auto to:G[u]) dfs(to),siz[u]+=siz[to];
    if(siz[u]>1) ans=max(ans,siz[u]*SAM[u].len);
}

inline void solve(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;++i) insert(s[i]-'a');
    for(int i=1;i<=tot;++i) G[SAM[i].fa].push_back(i);
    dfs(1);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}