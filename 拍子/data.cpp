#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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
mt19937 rnd(time(0));
map<PII,bool> mp; 
signed main(){
    auto solve=[&](){
    	int n,m,k;
    	do{
    		n=rnd()%2000+1,m=rnd()%2000+1,k=rnd()%n+1;
		}while(m>n*(n-1)/2 && k>n);
        cout<<n<<' '<<m<<' '<<k<<endl;
        for(int i=1;i<=m;++i){
        	int u,v,w;
            do{
            	u=rnd()%n+1,v=rnd()%n+1,w=rnd()%1000000000+1;
            	if(u>v) swap(u,v);
			}while(mp[mk(u,v)]);
			mp[mk(u,v)]=1;
            cout<<u<<' '<<v<<' '<<w<<endl;
        }
    };
    //freopen(".in","r",stdin);
    freopen("data.out","w",stdout);
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}
