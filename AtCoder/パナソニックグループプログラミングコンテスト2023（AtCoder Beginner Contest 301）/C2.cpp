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
signed main(){
	auto solve=[&](){
		string s, t;
	    cin >> s >> t;
	    int n = s.size();
	    vector<int> cnts(7), cntt(7);
	    for (int i = 0; i < n; ++i) {
	        if (s[i] == '@') {
	            ++cnts[0];
	        } else if (s[i] == 'a') {
	            ++cnts[1];
	        } else if (s[i] == 't') {
	            ++cnts[2];
	        } else if (s[i] == 'c') {
	            ++cnts[3];
	        } else if (s[i] == 'o') {
	            ++cnts[4];
	        } else if (s[i] == 'd') {
	            ++cnts[5];
	        } else if (s[i] == 'e') {
	            ++cnts[6];
	        }
	        if (t[i] == '@') {
	            ++cntt[0];
	        } else if (t[i] == 'a') {
	            ++cntt[1];
	        } else if (t[i] == 't') {
	            ++cntt[2];
	        } else if (t[i] == 'c') {
	            ++cntt[3];
	        } else if (t[i] == 'o') {
	            ++cntt[4];
	        } else if (t[i] == 'd') {
	            ++cntt[5];
	        } else if (t[i] == 'e') {
	            ++cntt[6];
	        }
	    }
	    bool ok = true;
	    for (int i = 1; i <= 6; ++i) {
	        if (cnts[i] + cntt[i] > n / 2) {
	            ok = false;
	            break;
	        }
	    }
	    cout << (ok ? "Yes" : "No") << endl;
	};
	io();

	while(T--) solve();
	return 0;
}


