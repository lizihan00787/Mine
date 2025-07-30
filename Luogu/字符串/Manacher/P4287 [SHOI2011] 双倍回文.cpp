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

const int N = 5e5 + 20;

int n, len;
char s[N << 1], str[N << 1], c;
int d[N << 1];

inline void solve() {
    read(n);
    s[0] = '$', s[1] = '#', s[(len = n * 2 + 1) + 1] = '*';
    for (int i = 1; i <= n; ++i) scanf("%c", &c), s[i * 2] = c, s[i * 2 + 1] = '#';
    auto manacher = [&]() {
        int id = 0, mx = 0, ans = 0; // id:当前区间中点， mx:当前区间右端点
        for (int i = 1; i <= len; ++i) {
            d[i] = (i < mx ? min(d[2 * id - i], mx - i) : 1);
            while (s[i + d[i]] == s[i - d[i]]) {
                d[i]++;
                if (s[i] == '#' && (d[i] - 1) % 4 == 0 && d[i - d[i] / 2] > d[i] / 2) ans = max(ans, d[i] - 1);
            }
            if (i + d[i] > mx) mx = i + d[i], id = i;
        }
        return ans;
    };
    printf("%d\n", manacher());
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}