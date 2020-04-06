#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

tli ext_euc(i64 a, i64 b) {
    if (b == 0) return {a, 1, 0};
    auto[g, x, y] = ext_euc(b, a % b);
    return {g, y, x - (a / b) * y};
}

class strHash {
private:
    size_t len;
    i64 mod, hs, inv;
    vector<i64> hm, exp;
    list<i64> str;
public:
    strHash() {
        mod = 1e9 + 9;
        len = hs = inv = 0;
    }

    strHash(const vector<i64> &_hm, int maxLength, i64 p = 11, i64 _mod = 1e9 + 9) {
        hm = _hm;
        mod = _mod;
        exp.emplace_back(1);
        for (int i = 0; i < maxLength; i++) exp.emplace_back(exp.back() * p), exp.back() %= mod;
        inv = get<1>(ext_euc(p, mod));
        len = hs = 0;
    }

    void emplace_front(char c) {
        hs *= exp[1];
        hs += hm[c - 'a'];
        hs %= mod;
        str.emplace_front(c);
        len++;
    }

    void emplace_back(char c) {
        hs += hm[c - 'a'] * exp[len];
        hs %= mod;
        str.emplace_back(c);
        len++;
    }

    char pop_front() {
        auto c = str.front();
        hs -= hm[c - 'a'];
        hs *= inv;
        hs %= mod;
        if (hs < 0) hs += mod;
        str.pop_front();
        len--;

        return c;
    }

    char pop_back() {
        auto c = str.back();
        hs -= hm[c - 'a'] * exp[len - 1];
        hs %= mod;
        if (hs < 0) hs += mod;
        str.pop_back();
        len--;

        return c;
    }

    bool operator==(const strHash &tar) {
        return hs == tar.hs;
    }

    size_t operator+(const strHash &tar) {
        return len + tar.len;
    }

    void print() {
        copy(iterall(str), ostream_iterator<char>(cout, ""));
        cout<<endl;
    }
};

const vector<i64> hm = {6455536, 8266088, 8148826, 4806171, 5649282, 6090469, 8112641, 9019150, 8063633, 6084972,
                        3230053, 8319456, 1232075, 5334896, 3918192, 5261805, 2865199, 2248845, 5811111, 1280309,
                        9237435, 1079389, 4800858, 4388579, 8407711, 3002864};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    string s;
    cin >> s;

    auto hl1 = strHash(hm, N / 2), hl2 = strHash(hm, N / 2);
    auto hr1 = strHash(hm, N / 2), hr2 = strHash(hm, N / 2);
    for (int i = 0; i < N / 2; i++) {
        hl1.emplace_back(s[i]);
        hr1.emplace_back(s[i + (N + 1) / 2]);
    }

    int cur = N / 2;
    size_t res = 0;
    for (int i = N / 2; i; --i) {
        if (hl1 == hr1) res = max(res, hl1 + hl2);

        hl2.emplace_front(hl1.pop_back());
        hr2.emplace_back(hr1.pop_front());

        if (cur < N / 2) hl2.emplace_back(s[cur]), hr2.emplace_front(s[N - 1 - cur]), ++cur;
        while (!(hl2 == hr2)) hl2.pop_back(), hr2.pop_front(), --cur;
    }

    cout << res << endl;
    return 0;
}