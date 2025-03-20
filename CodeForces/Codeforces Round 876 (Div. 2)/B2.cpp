#include<bits/stdc++.h>
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
int T=1;
signed main(){
	auto solve=[&](){
		int n;
	    int res = 0;
	    cin >> n;
	    vector<vector<int>> v(n + 1);
	    for (int i = 1; i <= n; ++i) {
	        int x, y;
	        cin >> x >> y;
	        v[x].push_back(y);
	    }
	    for (int i = 1; i <= n; ++i) {
	        std::sort(v[i].begin(), v[i].end(), greater<>());
	        for (int j = 0; j < min(i, (int)v[i].size()); ++j) {
	            res += v[i][j];
	        }
	    }
	    cout << res << endl;
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}


