#include <bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int mod = 998244353;

int n, k;
const int N = 1e6 + 20;
const int M = 3 * N + 5;

int fac[M];
int invfac[M];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int inv(int n) { return qpow(n, mod - 2) % mod; }

void init() {
    fac[0] = 1;
    invfac[0] = 1;
    for (int i = 1; i < M; i++) {
        fac[i] = (fac[i - 1] * i) % mod;
        invfac[i] = inv(fac[i]);
    }
}

int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}

int calc(int m, int cnt) { // m项系数 x ^ (2i + j)     2i + j = m
    if (m < 0 || cnt < 0) return 0;
    if (cnt == 0) return (m == 0) ? 1 : 0;
    int res = 0;
    for (int i = 0; i <= cnt; ++i) {
        if (3ll * i > m) break;
        int tmp = (C(cnt, i) * C(m - 3 * i + cnt - 1, cnt - 1)) % mod;
        if (i % 2 == 1) res = (res - tmp + mod) % mod;
        else res = (res + tmp) % mod;
    }
    return res;
}

int calcval(int k, vector<int> &s, int cnt) {
    if (k < 0) return 0;
    int res = 0;
    int n = (int)(s.size());
    for (int i = 0; i < n; ++i) {
        if (k >= i) {
            int g_val = calc(k - i, cnt);
            int tmp = (s[i] * g_val) % mod;
            res = (res + tmp) % mod;
        }
    }
    return res;
}

inline void solve() {
    read(n, k);
    if (k == 1 || k == 2 * n + 1) {
        cout << (n + 1) / 2 << endl;
        return;
    }
    if (n == 1) {
        if (k >= 0 && k <= 4) cout << 1 << endl;
        else cout << 0 << endl;
        return;
    }
    vector<int> s = {1, 2, 3, 4, 3, 2, 1};
    int tot1 = calcval(k, s, n - 2);

    int tot2 = 0;
    if (n % 2 == 0) {
        if (k % 2 == 0) {
            int m = n / 2;
            // 偶数，对称数组的前半部分等于后半部分
            // 前半部分：A_1 (0-3), A_2...A_{m-1} (0-2), A_m (0-2)
            vector<int> w = {1, 1, 1, 1};
            tot2 = calcval(k / 2, w, m - 1);
        }
    }
    else {
        // 奇数，中间元素可以是0,1,2
        int m = (n - 1) / 2;
        for (int c = 0; c <= 2; ++c) {
            if (k >= c && (k - c) % 2 == 0) {
                int p = (k - c) / 2;
                // 前半部 A_1 (0-3), A_2...A_m (0-2)
                vector<int> w = {1, 1, 1, 1};
                int ways = calcval(p, w, m - 1);
                tot2 = (tot2 + ways) % mod;
            }
        }
    }

    int sum = (tot1 + tot2) % mod;
    int ans = (sum * inv(2)) % mod;

    cout << ans << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    init();
    read(T);
    while (T--) solve();
    return 0;
}