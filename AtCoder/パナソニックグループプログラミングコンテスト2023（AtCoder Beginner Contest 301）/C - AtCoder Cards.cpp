#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
map<char,bool> q;
char s[200010];
char t[200010];
map<char,int> p1,p2;
queue<char> o1,o2;
signed main(){
	auto solve=[&](){
		cin>>s+1;
		cin>>t+1;
		q['a']=q['t']=q['c']=q['o']=q['d']=q['e']=q['r']=1;
		int n=strlen(s+1);
		int num1=0,num2=0;
		for(int i=1;i<=n;++i){
			if(s[i]!='@') p1[s[i]]++;
			else num1++;
			if(t[i]!='@') p2[t[i]]++;
			else num2++;
		}
		for(int i=1;i<=n;++i){
			if(p2[s[i]]!=p1[s[i]] && s[i]!='@'){
				if(!q[s[i]]){
					cout<<"No"<<endl;
					return;
				}
				int k=abs(p1[s[i]]-p2[s[i]]);
				while(k--) o2.push(s[i]);
			}
			if(p2[t[i]]!=p1[t[i]] && t[i]!='@'){
				if(!q[t[i]]){
					cout<<"No"<<endl;
					return;
				}
				int k=abs(p1[t[i]]-p2[t[i]]);
				while(k--) o1.push(t[i]);
			}
		}
		if(o1.size()>num1 || o2.size()>num2 || o1.size()+o2.size()>num1+num2){
			cout<<"No"<<endl;
			return;
		}
		cout<<"Yes"<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}


