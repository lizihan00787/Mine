#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
using namespace __gnu_pbds;
template<typename P>
void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
	     if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
int T=1;

const int N=1e6+10;

int n ,m,a[N];
vector<int> g[N];
struct BIT{
	#define lowbit(x) (x&(-x))
	int t[N];
	void add(int x,int val) {for(;x<=n;x+=lowbit(x)) t[x]+=val;}
	int ask(int x) {int res=0;for(;x;x-=lowbit(x)) res+=t[x];return res;}
	void modi(int l,int r,int val) {add(l,val),add(r+1,-val);}
}T;



void solve(){
    
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


