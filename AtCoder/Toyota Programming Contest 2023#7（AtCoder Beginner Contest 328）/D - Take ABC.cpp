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
string s;
stack<char> q;
signed main(){
	auto solve=[&](){
		getline(cin,s);
		int n=s.size();
		for(int i=0;i<n;++i){
			q.push(s[i]);
			if(i>=2 && q.size()>=3){
				string sub;
				int j=1;
				while(j<=3){
					char p=q.top();
					q.pop();
					sub.push_back(p);
					j++;
				}
				if(sub=="CBA"){
					continue;
				}
				else{
					reverse(sub.begin(),sub.end());
					for(int w=0;w<sub.size();++w){
						char p=sub[w];
						q.push(p);
					}
				}
			}
		}
		string ans;
		while(!q.empty()){
			ans.push_back(q.top());
			q.pop();
		}
		reverse(ans.begin(),ans.end());
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


