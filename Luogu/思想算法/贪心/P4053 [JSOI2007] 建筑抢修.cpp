#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
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

const int N=1e5+5e4+20;

int n;

struct node{
	int t1,t2;
}a[N];

priority_queue<ll> q;

void solve(){
    read(n);
	for(int i=1;i<=n;++i) read(a[i].t1,a[i].t2);
	sort(a+1,a+n+1,[](node a,node b){
		return a.t2<b.t2;
	});
	ll sum=0,ans=0;
	for(int i=1;i<=n;++i){
		sum+=a[i].t1;
		q.push(a[i].t1);
		if(sum<=a[i].t2) ans++;
		else{
			sum-=q.top();
			q.pop();
		}
	}
	cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}

