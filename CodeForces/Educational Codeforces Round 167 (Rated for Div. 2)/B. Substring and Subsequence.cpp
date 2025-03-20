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

char a[120],b[120];
unordered_map<char,int> q;

void solve(){
    scanf("%s",a+1);
	scanf("%s",b+1);
	int la=strlen(a+1);
	int lb=strlen(b+1);
	for(int i=1;i<=n;++i){
		
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}


