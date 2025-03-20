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

const int N=100010;

int n,ans,tmp;
int vis[N];
char a[160][80];
char s[N*10];
struct Tire{
    int son[27];
    int fail,flag;
    void clear(){
        memset(son,0,sizeof(son));
        flag=0;
        fail=0;
    }
}t[N*10];

void insert(char *s,int len,int num){
    int u=1;
    for(int i=0;i<len;++i){
        int p=s[i]-'a';
        if(!t[u].son[p]) t[u].son[p]=++tmp;
        u=t[u].son[p];
    }
    t[u].flag=num;
}
void getfail(){
    for(int i=0;i<26;++i) t[0].son[i]=1;
    queue<int> q;
    q.push(1);
    t[1].fail=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        int fail=t[u].fail;
        for(int i=0;i<26;++i){
            int p=t[u].son[i];
            if(!p) {t[u].son[i]=t[fail].son[i];continue;}
            t[p].fail=t[fail].son[i];
            q.push(p);
        }
    }
}
void query(char *s,int len){
    int u=1;
    for(int i=0;i<len;++i){
        int p=s[i]-'a';
        int k=t[u].son[p];
        while(k>1){
            if(t[k].flag) vis[t[k].flag]++;
            k=t[k].fail;
        }
        u=t[u].son[p];
    }
}
void clear(){
    for(int i=0;i<=tmp;++i) t[i].clear();
    for(int i=1;i<=n;++i) vis[i]=0;
    tmp=1,ans=0;
}

signed main(){
    auto solve=[&](){
        while(1){
            read(n);
            if(n==0) break;
            clear();
            for(int i=1;i<=n;++i){
                cin>>a[i];
                insert(a[i],strlen(a[i]),i);
            }
            cin>>s;
            getfail();
            query(s,strlen(s));
            for(int i=1;i<=n;++i) ans=max(ans,vis[i]);
            cout<<ans<<endl;
            for(int i=1;i<=n;++i) if(vis[i]==ans) cout<<a[i]<<endl;
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}