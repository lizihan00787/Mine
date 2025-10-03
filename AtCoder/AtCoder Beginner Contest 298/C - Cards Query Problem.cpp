#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
//#define int long long
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
//vector<int> box[200005];
priority_queue<int,vector<int>,greater<int> > box[200005];
set<int> card[200005];
signed main(){
	auto solve=[&](){
	    int n, q;
	    cin>>n>>q;
	    while(q--){
	        int type;
	        cin>>type;
	        if(type==1){
	            int i,j;
	            cin>>i>>j;
	            box[j].push(i);
	            card[i].insert(j);
	        }
			else if(type==2){
	            int i;
	            cin>>i;
	            vector<int> l;
	            while(!box[i].empty()){
	                cout<<box[i].top()<< " ";
	                l.push_back(box[i].top());
	                box[i].pop();
	            }
	            for(int j=0;j<l.size();++j){
	            	box[i].push(l[j]);
				}
	            cout<<endl;
	        }
			else{
	            int i;
	            cin>>i;
	            int prev=-1;
	            set<int>::iterator it;
				for(it=card[i].begin();it!=card[i].end();++it){
					cout<<*it<<' ';
				}
	            cout<<endl;
	        }
	    }
	};
	io();solve();
	return 0;
}

