
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

const int N=1e6+1e5+10;

int n;
int cnt[N];
double p[N];

void solve(){
    read(n);
	double ans=0;
	for(int i=0;i<(1<<n);++i) scanf("%lf",&p[i]);
	for(int i=1;i<(1<<n);++i) cnt[i]=cnt[i-(i&(-i))]+1;
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);++j){
			if((j & i) && p[j]) break;
			if(j==(1<<n)){
				puts("INF");
				return;
			}
		}
	}
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);++j){
			if(j & i) p[j]+=p[j^i];
		}
	}
	for(int i=1;i<(1<<n);++i) ans+=((cnt[i]&1)?1:-1)/(1-p[(1<<n)-1-i]);
	printf("%.8lf\n",ans);
}
signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}

