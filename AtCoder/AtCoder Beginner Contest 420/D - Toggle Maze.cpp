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

const int N = 520;

int n, m;
char s[N][N];

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    int sx = 0, sy = 0, fx = 0, fy = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == 'S') sx = i, sy = j;
            if (s[i][j] == 'G') fx = i, fy = j;
        }
    }
    queue<tuple<int, int, int, int> > q;
    vector<vector<vector<bool> > > vis(n + 1, vector<vector<bool>>(m + 1, vector<bool>(2, false)));

    q.push({sx, sy, 0, 0});
    vis[sx][sy][0] = 1;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    while(!q.empty()) {
        auto [x, y, door, step] = q.front();
        q.pop();
        if (x == fx && y == fy) return (void)(printf("%d\n", step));
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                char c = s[nx][ny];
                int nxt = door;
                bool mov = 0;
                if (c == '.' || c == 'S' || c == 'G') mov = 1;
                else if (c == '#') mov = 0;
                else if (c == 'o') {
                    if (door == 0) mov = 1;
                    else mov = 0;
                }
                else if (c == 'x') {
                    if (door == 0) mov = 0;
                    else mov = 1;
                }
                else if (c == '?') mov = 1, nxt = door ^ 1;
                if (mov && !vis[nx][ny][nxt]) {
                    vis[nx][ny][nxt] = 1;
                    q.push({nx, ny, nxt, step + 1});
                }
            }
        }
    }
    puts("-1");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
