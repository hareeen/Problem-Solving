#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstring>

#define iterall(container) container.begin(), container.end()

using namespace std;

using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

template <class T>
class Matrix : public vector<vector<T>> {
 public:
  Matrix() { this->clear(); }

  Matrix(const int M, const int N) {
    this->clear();
    this->resize(M);
    for (auto it = this->begin(); it != this->end(); it++) it->resize(N);
  }

  Matrix(const vector<vector<T>>& arr) {
    const int M = arr.size();
    const int N = arr[0].size();

    this->clear();
    this->resize(M);
    for (int i = 0; i < M; i++) {
      this->at(i).resize(N);
      for (int j = 0; j < N; j++) {
        this->at(i).at(j) = arr[i][j];
      }
    }
  }

  Matrix(initializer_list<initializer_list<T>> arr) {
    const int M = arr.size();

    this->clear();
    this->resize(M);

    int i = 0;
    for (auto el : arr) {
      this->at(i) = vector<T>(el);
      i++;
    }
  }

  T& at2(const int m, const int n) { return this->at(m).at(n); }

  const T& at2(const int m, const int n) const { return this->at(m).at(n); }

  pi size2() const noexcept {
    return {static_cast<int>(this->size()),
            static_cast<int>(this->at(0).size())};
  }

  void modulo(const T mod) {
    for (auto it = this->begin(); it != this->end(); it++) {
      for (auto& el : (*it)) el %= mod;
    }
  }

  Matrix<T> operator*(const Matrix<T>& rhs) {
    auto lsz = this->size2();
    auto rsz = rhs.size2();

    if (lsz.second != rsz.first) throw;

    Matrix<T> newMatrix(lsz.first, rsz.second);

    for (int i = 0; i < lsz.first; i++) {
      for (int j = 0; j < rsz.second; j++) {
        T _s{};
        for (int k = 0; k < lsz.second; k++)
          _s += (this->at2(i, k) * rhs.at2(k, j));
        newMatrix.at2(i, j) = _s;
      }
    }

    return newMatrix;
  }
};

const i64 mod = 1000LL;

vector<Matrix<i64>> tf;
const auto transform_base = Matrix<i64>({{6, -4}, {1, 0}});

void initialize(const int n) {
  tf.push_back(transform_base);
  for (int i = 0; i < n; i++) {
    tf.push_back(tf.back() * tf.back());
    tf.back().modulo(mod);
  }
}

int get_nth(int n) {
  int cur = 0, mul = 1;
  Matrix<i64> base = {{6}, {2}};

  n--;
  while (n) {
    if (n % 2) base = tf[cur] * base;
    base.modulo(mod);
    cur++, mul *= 2;
    n /= 2;
  }

  return base.at2(0, 0);
}

void print(const int n, const int r) {
  int res = (r + mod) % mod;

  string atFront;
  if (res < 10)
    atFront = "00";
  else if (res < 100)
    atFront = "0";

  cout << "Case #" << n << ": " << atFront << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  initialize(31);

  int tc;
  cin >> tc;

  for (int i = 0; i < tc; i++) {
    int t;
    cin >> t;
    print(i + 1, get_nth(t) - 1);
  }

  return 0;
}