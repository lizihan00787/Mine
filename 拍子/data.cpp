#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define re register
#define PII pair<int, int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define mk(a, b) make_pair(a, b)
#define pqd priority_queue<int, vector<int>, less<int>>
#define pqx priority_queue<int, vector<int>, greater<int>>
using namespace std;
template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    x = res * f;
}
int T = 1;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rnd);
}
map<PII, bool> mp;
signed main() {
    auto solve = [&]() {
        int t, n;
        t = rnd() % 50 + 1;
        cout << t << endl;
        while (t--) {
            n = rnd() % 100 + 1;
            for (int i = 1; i <= n; ++i)
        }
    };
    // freopen(".in","r",stdin);
    freopen("data.out", "w", stdout);
    // io();
    // read(T);
    while (T--) solve();
    return 0;
}
