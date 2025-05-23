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

const int N=(1e5+10)*2;

struct node{
    int ch[26];
    int len,fa;
}SAM[N];

int tot=1,las=1;
ll siz[N];
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
ll tt[N],A[N],sum[N];

void dfs(int u,int k){
    if(k<=siz[u]) return;
    k-=siz[u];
    for(int i=0;i<26;++i){
        int v=SAM[u].ch[i];
        if(!v) continue;
        if(k>sum[v]) {k-=sum[v];continue;}
        putchar(i+'a');
        dfs(v,k);
        return;
    }
}

int n,m;
int k;

inline void solve(){
    scanf("%s",s+1);
    n=strlen(s+1);
    read(m);
    for(int i=1;i<=n;++i) insert(s[i]-'a');
    for(int i=1;i<=tot;++i) tt[SAM[i].len]++;
    for(int i=1;i<=tot;++i) tt[i]+=tt[i-1];
    for(int i=1;i<=tot;++i) A[tt[SAM[i].len]--]=i;
    for(int i=tot;i>=1;--i) siz[SAM[A[i]].fa]+=siz[A[i]];
    for(int i=1;i<=tot;++i) sum[i]=siz[i]=1;
    siz[1]=sum[1]=0;

    for(int i=tot;i>=1;--i)
        for(int j=0;j<26;++j)
            if(SAM[A[i]].ch[j]) sum[A[i]]+=sum[SAM[A[i]].ch[j]];
    while(m--){
        read(k);
        if(sum[1]<k) cout<<-1<<endl;
        else dfs(1,k),cout<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}