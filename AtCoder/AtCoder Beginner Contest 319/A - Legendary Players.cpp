#include<bits/stdc++.h>
#define int long long
#define endl "\n"
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
signed main(){
	auto solve=[&](){
		string s;
		getline(cin,s);
		if(s=="tourist") cout<<3858<<endl;
		if(s=="ksun48") cout<<3679<<endl;
		if(s=="Benq") cout<<3658<<endl;
		if(s=="Um_nik") cout<<3648<<endl;
		if(s=="apiad") cout<<3638<<endl;
		if(s=="Stonefeang") cout<<3630<<endl;
		if(s=="ecnerwala") cout<<3613<<endl;
		if(s=="mnbvmar") cout<<3555<<endl;
		if(s=="newbiedmy") cout<<3516<<endl;
		if(s=="semiexp") cout<<3481<<endl;
 		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


