#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef complex<double> cd;
typedef vector<cd> vcd;
#define endl '\n'
#define rp(x, i, j) for (int x = (i); x < (j); ++x)
#define rpr(x, i, j) for (int x = (j) - 1; x >= i; --x)
#define rpe(e, arr) for (auto& e : arr)
#define all(x) begin(x), end(x)
#define FASTIO cin.tie(nullptr)->sync_with_stdio(false)
int INF = 1e9;
ll LINF = 1e18;
int dy[]{0, -1, 0, 1};
int dx[]{-1, 0, 1, 0};

struct Seg {
    vector<int> t;
    int n;
    Seg(int n) : n(n) {
        t.resize(n << 1);
    }
    void build() {
        rpr(i, 1, n)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, int value) {
        for (t[p += n] = value, p >>= 1; p > 0; p >>= 1)
            t[p] = t[p << 1] + t[p << 1 | 1];
    }
    int query(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
};
