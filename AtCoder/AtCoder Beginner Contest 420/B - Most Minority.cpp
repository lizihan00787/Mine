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

int n, m;
char s[120][120];
int c[120];

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; ++j) {
        int cnt0 = 0, cnt1 = 0;
        for (int i = 1; i <= n; ++i) {
            cnt0 += (s[i][j] == '0');
            cnt1 += (s[i][j] == '1');
		}
        int minn = min(cnt0 ,cnt1);
        int f = 0;
        if (cnt1 == cnt0 && cnt1 == 0) f = 2;
        else if (minn == cnt0) f = 0;
        else if (minn == cnt1) f = 1;
        for (int i = 1; i <= n; ++i) {
            if (f == 2) c[i]++;
            else if(f == 1 && (s[i][j] == '1')) c[i]++;
            else if(f == 0 && (s[i][j] == '0')) c[i]++;
        }
	}
    int maxx = 0;
    for (int i = 1; i <= n; ++i) maxx = max(maxx, c[i]);
    for (int i = 1; i <= n; ++i) if (c[i] == maxx) printf("%d ", i);
    puts("");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
