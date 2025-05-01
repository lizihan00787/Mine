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
}SAM[N<<1];
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

int n1,n2;
char s[N],t[N];
int len=0,ans=0;

void calc(int n){
    int p=1;
    for(int i=1;i<=n;++i){
        int c=t[i]-'a';
        if(SAM[p].ch[c]) len++,p=SAM[p].ch[c];
        else{
            for(;p && !SAM[p].ch[c];p=SAM[p].fa);
            if(p) len=SAM[p].len+1,p=SAM[p].ch[c];
            else len=0,p=1;
        }
        ans=max(ans,len);
    }
}

inline void solve(){
    scanf("%s",s+1);
    scanf("%s",t+1);
    n1=strlen(s+1),n2=strlen(t+1);
    for(int i=1;i<=n1;++i) insert(s[i]-'a');
    calc(n2);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}