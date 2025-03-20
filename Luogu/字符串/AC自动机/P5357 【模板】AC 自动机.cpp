#include<bits/stdc++.h>
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
struct node{
    int a[27];
    int flag;
    int ans;
    node(){
        memset(a,0,sizeof(a));
        flag=0;
        ans=0;
    }
}trie[2000010];
int n;
string t;
string s;
int u,cnt=0;
int fail[2000010],vis[200010],in[20000010],pp[2000001];
int get(char a) {return (int)(a-'a');}
queue<int> q;
void insert(string s,int id){
    int len=s.size();
    s='0'+s;
    u=0;
    for(int i=1;i<=len;++i){
        int k=get(s[i]);
        if(!trie[u].a[k]) trie[u].a[k]=++cnt;
        u=trie[u].a[k];
    }
    if(!trie[u].flag) trie[u].flag=id;
    pp[id]=trie[u].flag;
}
void build(){
    for(int i=0;i<26;++i) if(trie[0].a[i]) q.push(trie[0].a[i]);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;++i){
            int v=trie[u].a[i];
            if(v) fail[v]=trie[fail[u]].a[i],in[fail[v]]++,q.push(v);
            else trie[u].a[i]=trie[fail[u]].a[i];
        }
    }
}
void topo(){
    for(int i=1;i<=cnt;++i) if(in[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[trie[u].flag]=trie[u].ans;
        int v=fail[u];in[v]--;
        trie[v].ans+=trie[u].ans;
        if(in[v]==0) q.push(v);
    }
}
void query(string s){
    int len=s.size();
    s='0'+s;
    u=0;
    for(int i=1;i<=len;++i){
        int p=get(s[i]);
        u=trie[u].a[p];
        trie[u].ans++;
    }
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) cin>>t,insert(t,i);
        build();
        cin>>s;
        query(s);
        topo();
        for(int i=1;i<=n;++i) cout<<vis[pp[i]]<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}