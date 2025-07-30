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

const int N = 220;

struct Int {
    #define max_size (501)
    int val[max_size];
    int len;
    const int base = 10; // 压位的部分就先不管了
    Int(int _val = 0) {
        len = 1;
        for (int i = 0; i < max_size; i++) val[i] = 0;
        *this = _val;
    }
    Int(const char s[max_size]) { init(s); }
    Int(char s[max_size]) { init(s); }
    int &operator[](const int id) { return val[id]; }
    void operator=(int _val) {
        for (int i = 0; i <= len; i++) val[i] = 0;
        len = 0;
        while (_val) val[++len] = _val % 10, _val /= 10;
    }
    void operator=(Int pos) {
        *this = 0;
        len = pos.len;
        for (int i = 1; i <= len; i++) val[i] = pos.val[i];
    }
    void carry_bit() {
        for (int i = 1; i <= len; i++) {
            if (val[i] > 9) {
                val[i + 1] += val[i] / 10;
                val[i] %= 10;
                if (i == len) len++;
            }
        }
    }
    void eat_zero() {
        for (; !val[len] && len > 1; len--);
        if (!len) len = 0, val[len] = 0;
    }
    Int operator+(int _val) {
        Int now = *this;
        now[1] += _val;
        now.carry_bit();
        return now;
    }
    Int operator+(Int _val) {
        Int now = *this;
        now.len = max(now.len, _val.len);
        for (int i = 1; i <= _val.len; i++) now[i] += _val[i];
        now.carry_bit();
        return now;
    }
    Int operator*(int _val) {
        Int now = *this;
        for (int i = 1; i <= len; i++) now[i] *= _val;
        now.carry_bit();
        return now;
    }
    Int operator*(Int _val) {
        Int now;
        now.len = len + _val.len - 1;
        for (int i = 1; i <= now.len; i++) {
            for (int j = 1; j <= _val.len; j++) {
                now[i + j - 1] += val[i] * _val[j];
            }
        }
        now.eat_zero();
        now.carry_bit();
        return now;
    }
    Int operator/(int _val) {
        Int now = *this;
        for (int i = len; i >= 1; i--) {
            if (i) now[i - 1] += base * (now[i] % _val);
            now[i] /= _val;
        }
        now.eat_zero();
        return now;
    }
    bool operator<(Int _val) const {
        if (len != _val.len) return len < _val.len;
        for (int i = len; i >= 1; i--) {
            if (val[i] != _val[i]) return val[i] < _val[i];
        }
        return 0;
    }
    bool operator==(Int _val) const {
        if (len != _val.len) return 0;
        for (int i = len; i >= 1; i--) {
            if (val[i] != _val[i]) return 0;
        }
        return 1;
    }
    bool operator>(Int _val) const {
        if (len != _val.len) return len > _val.len;
        for (int i = len; i >= 1; i--) {
            if (val[i] != _val[i]) return val[i] > _val[i];
        }
        return 0;
    }
    bool operator<=(Int _val) const { return !(*this > _val); }
    bool operator>=(Int _val) const { return !(*this < _val); }
    void init(const char s[max_size]) {
        len = 0;
        int begin = 0;
        for (int i = 1; s[i] >= '0' && s[i] <= '9'; i++) {
            if (!begin && s[i] == 48) continue;
            if (!begin) {
                begin = i;
            }
            len++;
        }
        if (!begin) {
            len = 0, val[1] = 0;
            return;
        }
        for (int i = 1; i <= len; i++) {
            val[i] = s[len - i + begin] - 48;
        }
    }
    void operator=(const char s[max_size]) { this->init(s); }
    void print() {
        eat_zero();
        if (!len)
            putchar(48);
        else
            for (int i = len; i >= 1; i--) putchar(val[i] + 48);
        putchar('\n');
    }
};

int n, k, a[N], b[N];
Int dp[2][N];

inline void solve() {
    read(n, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int Alpha = 0, id = i & 1;
        for (int j = 0; j <= i; ++j) dp[id][j] = 0;
        if (a[i] >= b[i]) {
            for (int j = 1; j <= i; ++j) Alpha += (a[j] >= b[i]);
            for (int j = 0; j <= i; ++j) dp[id][j] = dp[id][j] + dp[id ^ 1][j] * (j + Alpha);
            for (int j = 1; j <= i - Alpha; ++j) dp[id][j] = dp[id][j] + dp[id ^ 1][j - 1] * (i - Alpha - (j - 1));
        }
        else {
            for (int j = 1; j < i; ++j) Alpha += (b[j] > a[i]);
            for (int j = Alpha; j <= i; ++j) dp[id][j] = dp[id][j] + dp[id ^ 1][j] * (j - Alpha);
            for (int j = 1; j <= i; ++j) dp[id][j] = dp[id][j] + dp[id ^ 1][j - 1] * (i - ((j - 1) - Alpha));
        }
    } 
    Int ans = 0;
    for (int i = 0; i <= k; ++i) ans = (ans + dp[n & 1][i]);
    ans.print();
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}