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

void solve(){
    int x,y;
	read(x,y);
	int nd=abs(x);
	int a=x,b=-abs(x);
	int dis1=abs(b-y);
	int dis2=abs(abs(x)-y);
	if(min(dis1,dis2)<nd) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}


