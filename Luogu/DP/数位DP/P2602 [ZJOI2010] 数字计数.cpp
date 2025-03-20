#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
int a,b;
int f[15][2][15][2];
int num[15];
int dfs(int now,int x,int sum,bool op0,bool lim){
    int res=0;
    if(now==0) return sum;
    if(f[now][lim][sum][op0]!=-1) return f[now][lim][sum][op0];
    for(int i=0;i<=9;++i){
        if(lim && i>num[now]) break;
        res+=dfs(now-1,x,sum+((!op0 || i) && (i==x)),(op0) && (i==0),!((!lim) || (i<num[now])));
    }
    f[now][lim][sum][op0]=res;
    return res;
}
int work(int sum,int x){
    int len=0;
    while(sum){
        num[++len]=sum%10;
        sum/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(len,x,0,1,1);
}
signed main(){
    read(a),read(b);
    for(int i=0;i<=9;++i){
        cout<<work(b,i)-work(a-1,i)<<' ';
    }
    return 0;
}