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

const int N=5e5+10;

struct node{
    int ch[26];
    int len,fa;
}SAM[N];
int tot=1,las=1;
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

int n;
int ans=0;
int c[N],b[N];

inline void sort(){
    for(int i=1;i<=tot;++i) ++c[SAM[i].len];
    for(int i=1;i<=tot;++i) c[i]+=c[i-1];
    for(int i=1;i<=tot;++i) b[c[SAM[i].len]--]=i;
}

int mx[N],mi[N];

void calc(char *s){
    int p=1,len=0;
    int n=strlen(s);
    for(int i=0;i<n;++i){
        int c=s[i]-'a';
        if(SAM[p].ch[c]) len++,p=SAM[p].ch[c];
        else{
            for(;p && !SAM[p].ch[c];p=SAM[p].fa);
            if(p) len=SAM[p].len+1,p=SAM[p].ch[c],mx[p]=max(mx[p],len);
            else len=0,p=1;
        }
        mx[p]=max(mx[p],len);
    }
    for(int i=tot;i>=1;--i){
        int u=b[i],f=SAM[u].fa;
        mx[f]=max(mx[f],min(mx[u],SAM[f].len));
        mi[u]=min(mi[u],mx[u]);mx[u]=0;
    }
}

char s[N];
inline void solve(){
    scanf("%s",s);
    n=strlen(s);
    for(int i=0;i<n;++i) insert(s[i]-'a');
    memset(mi,0x3f,sizeof(mi));
    sort();
    while(~scanf("%s",s)) calc(s);
    for(int i=1;i<=tot;++i) ans=max(ans,mi[i]);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}