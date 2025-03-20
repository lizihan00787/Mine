#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int N=2e6+10;
char s[N];
vector<int> e[N];
ll sum[N],ans;
int cnt=1,np=1;
struct node{
    int len,fa;
    int a[27];
    node(){
        len=0,fa=0;
        memset(a,0,sizeof(a));
    }
}t[N];
void extend(int c){
    int p=np;np=++cnt;
    t[np].len=t[p].len+1;
    sum[np]=1;
    for(;p && !t[p].a[c];p=t[p].fa) t[p].a[c]=np;
    if(!p) t[np].fa=1;
    else{
        int q=t[p].a[c];
        if(t[q].len==t[p].len+1) t[np].fa=q;
        else{
            int nq=++cnt;
            t[nq].len=t[p].len+1;
            t[nq].fa=t[q].fa;t[q].fa=nq;t[np].fa=nq;
            for(;p && t[p].a[c]==q;p=t[p].fa) t[p].a[c]=nq;
            memcpy(t[nq].a,t[q].a,sizeof(t[q].a));
        }
    }
}
void dfs(int u){
    for(auto it:e[u]){
        dfs(it);
        sum[u]+=sum[it];
    }
    if(sum[u]>1) ans=max(ans,sum[u]*t[u].len);
}
signed main(){
    auto solve=[&](){
        cin>>s+1;
        int n=strlen(s+1);
        for(int i=1;i<=n;++i) extend(s[i]-'a');
        for(int i=2;i<=cnt;++i) e[t[i].fa].push_back(i);
        dfs(1);
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}