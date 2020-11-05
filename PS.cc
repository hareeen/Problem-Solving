#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

const int X = 29;

void resort(vector<int> &arr, int M) {
    const int N = arr.size();

    int p = N;
    for (int i = 0; i < N; i++) {
        if (p == N && arr[i] >= M) p = i;
        arr[i] %= M;
    }

    if (p == N) {
        arr.erase(unique(iterall(arr)), arr.end());
        return;
    }

    auto sit1 = arr.begin(), eit1 = arr.begin() + p;
    auto sit2 = arr.begin() + p, eit2 = arr.end();

    vector<int> res;
    while (sit1 != eit1 || sit2 != eit2) {
        if (sit1 == eit1)
            res.emplace_back(*sit2), sit2++;
        else if (sit2 == eit2)
            res.emplace_back(*sit1), sit1++;
        else if (*sit2 < *sit1)
            res.emplace_back(*sit2), sit2++;
        else
            res.emplace_back(*sit1), sit1++;
    }

    copy(iterall(res), arr.begin());
    arr.erase(unique(iterall(arr)), arr.end());
}

void doubleit(vector<int> &arr, int M) {
    const int N = arr.size();
    for (int i = 0; i < N; i++) arr.emplace_back(arr[i] + M);
}

void halfit(vector<int> &arr) {
    const int N = arr.size() >> 1;
    arr.erase(arr.begin() + N, arr.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
        cin >> B[i];

    sort(iterall(A));
    sort(iterall(B));

    vector<bitset<X>> Ab(N), Bb(N);
    for (int i = 0; i < N; i++) {
        Ab[i] = decltype(Ab)::value_type(A[i]);
        Bb[i] = decltype(Bb)::value_type(B[i]);
    }

    {
        i64 ans = 0;
        i64 m = 1;

        for (int i = 0; i < X; i++) {
            auto prediction = [i](const bitset<X> &bit) { return bit[i]; };
            i64 Act = count_if(iterall(Ab), prediction) % 1999;
            i64 Bct = count_if(iterall(Bb), prediction) % 1999;

            ans += Act * Bct * m;
            ans %= 1999;
            m <<= 1;
            m %= 1999;
        }

        cout << ans << " ";
    }

    {
        bitset<X + 1> ans;
        i64 m = (1 << X) >> 1;

        vector<int> &arr = A;
        vector<int> &brr = B;

        for (int i = X - 1; i >= 0; i--) {
            resort(arr, 2 * m);
            resort(brr, 2 * m);
            doubleit(brr, 2 * m);

            /*
            cout << 2 * m << endl;
            for (auto el : arr) cout << el << " ";
            cout << endl;
            for (auto el : brr) cout << el << " ";
            cout << endl;
            */

            bool res = true;
            auto sit = lower_bound(iterall(brr), 2 * m - arr.back());
            auto eit = lower_bound(iterall(brr), 3 * m - arr.back());

            for (int j = arr.size() - 1; j >= 0; j--) {
                auto el = arr[j];
                while (sit != brr.end() && *sit < 2 * m - el) ++sit;
                while (eit != brr.end() && *eit < 3 * m - el) ++eit;

                if (sit != eit) {
                    res = false;
                    break;
                }
            }
            if (res)
                ans.set(i);

            m >>= 1;
            halfit(brr);
        }

        {
            auto prediction = [](const bitset<X> &bit) { return bit[X - 1]; };
            if (all_of(iterall(Ab), prediction) && all_of(iterall(Bb), prediction))
                ans.set(X);
        }

        cout << ans.to_ullong() << endl;
    }

    return 0;
}
