#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAX = 1e5 + 5;

struct event {
    int head;
    bool type;
    bool operator < (const event &other) const {
        return type > other.type;
    }
};

int f[18][MAX];
vector<event> roof[MAX];
bool hasblank[MAX];
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, L;
    cin >> n >> q >> L;
    for (int x, y, i = 0; i < n; i++) {
        cin >> x >> y;
        roof[x].push_back({x, 1});
        hasblank[x] = true;
        roof[y + 1].push_back({x, 0});
    }

    multiset<int> sech;
    for (int i = 1; i <= L; i++) {
        std::sort(roof[i].begin(), roof[i].end());
        for (auto &[head, type] : roof[i]) {
            if (type == 0) sech.erase(sech.find(head - 1));
            else sech.insert(i - 1);
        }
        if (!sech.empty() && *sech.begin() < i) f[0][i] = *sech.begin();
    }

    for (int j = 1; j <= 17; j++) {
        for (int i = 1; i <= L; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int j = __lg(L); j >= 0; j--) {
            if (f[j][r] >= l) {
                r = f[j][r];
                ans += (1 << j);
            }
        }

        if (hasblank[f[0][r] + 1]) cout << ans + 1 << '\n';
        else cout << "-1\n";
    }
    
    return 0;
}