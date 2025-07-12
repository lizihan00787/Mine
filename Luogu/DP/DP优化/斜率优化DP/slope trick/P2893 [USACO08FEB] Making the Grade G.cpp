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

int n, ans1, ans2;
priority_queue<int, vector<int>, less<int> > q1;
priority_queue<int, vector<int>, greater<int> > q2;

inline void solve() {
    read(n);
    while (n--) {
        int x;
        read(x);
        q1.push(x); q2.push(x);
        if (x < q1.top()) {
            ans1 += q1.top() - x;
            q1.pop(); q1.push(x);
        }
        if (x > q2.top()) {
            ans2 += x - q2.top();
            q2.pop(); q2.push(x);
        }
    }
    cout << min(ans1,ans2) << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}