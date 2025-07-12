#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define ull unsigned long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
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
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) {read(x); read(args...);}
int T = 1;

const int N = 5e5 + 20;

int n, ans;
priority_queue<int, vector<int>, less<int> > q;

inline void solve() {
    read(n);
    while (n--) {
        int x;
        read(x);
        q.push(x);
        if (x < q.top()) {
            ans += q.top() - x;
            q.pop(); q.push(x);
        }
    }
    cout << ans << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}