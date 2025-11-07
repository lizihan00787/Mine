#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
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
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;

const int N = 1e8 + 10;

int n, k, cnt = 0;
int pri[N];
bool isnp[N];

void Init(int n) {
    isnp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!isnp[i]) pri[++cnt] = i;
        for (int j = 1; j <= cnt && i * pri[j] <= n; ++j) {
            isnp[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}

inline void solve() {
    read(n, k);
    Init(n);
    for (int i = 1, x; i <= k; ++i) read(x), printf("%d\n", pri[x]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}