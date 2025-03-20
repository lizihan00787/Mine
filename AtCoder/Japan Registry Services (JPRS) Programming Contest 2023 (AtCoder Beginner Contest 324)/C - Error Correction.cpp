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
int n;
string t;
string s;
vector<int> ans;
signed main(){
	auto solve=[&](){
		cin>>n;
		cin.ignore();
		getline(cin,t);
		int cnt=0;
		for(int k=1;k<=n;++k){
			getline(cin,s);
			if(s==t){
				cnt++;
				ans.push_back(k);
			}
			else if(s.size()==t.size()+1){
				map<char,int> sp,tp;
				for(int i=0;i<s.size();++i) sp[s[i]]++;
				for(int i=0;i<t.size();++i) tp[t[i]]++;
				int cnt1=0;
				for(auto it:sp) if(it.first>='a' && it.first<='z') cnt1+=abs(tp[it.first]-sp[it.first]);
				if(cnt1==1){
					cnt++;
					ans.push_back(k);
				}
			}
			else if(s.size()==t.size()-1){
				for(int i=0;i<t.size();++i){
					string sub=t;
					sub.erase(sub.begin()+i);
					if(sub==s){
						cnt++;
						ans.push_back(k);
						break;
					}
				}
			}
			else if(s.size()==t.size()){
				int cnp=0;
				for(int i=0;i<s.size();++i){
					if(s[i]!=t[i] && s[i]>='a' && s[i]<='z') cnp++;
				}
				if(cnp==1){
					cnt++;
					ans.push_back(k);
				}
			}
		}
		cout<<cnt<<endl;
		for(auto it:ans){
			cout<<it<<' ';
		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


