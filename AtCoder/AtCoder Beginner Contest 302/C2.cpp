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
#define mk(a,b) make_pair(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int N, M;
bool check(vector<string>& perm) {
    for (int i = 0; i < N - 1; i++) {
        int diff = 0;
        for (int j = 0; j < M; j++) {
            if (perm[i][j] != perm[i+1][j]) {
                diff++;
            }
        }
        if (diff != 1) {
            return false;
        }
    }
    return true;
}
signed main(){
	auto solve=[&](){
	    cin >> N >> M;
	    vector<string> S(N);
	    for (int i = 0; i < N; i++) {
	        cin >> S[i];
	    }
	    vector<int> perm(N);
	    for (int i = 0; i < N; i++) {
	        perm[i] = i;
	    }
	    do {
	        vector<string> T(N);
	        for (int i = 0; i < N; i++) {
	            T[i] = S[perm[i]];
	        }
	        if (check(T)) {
	            cout << "Yes" << endl;
	            return 0;
	        }
	    } while (next_permutation(perm.begin(), perm.end()));
	    cout << "No" << endl;
	};
	io();

	while(T--) solve();
	return 0;
}


