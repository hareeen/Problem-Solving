#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define M_iterai64(container) container.begin(), container.end()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

class matrix
{
public:
  vector<vector<i64>> Matrix;
  matrix(int N, int M)
  {
    Matrix.resize(N, vector<i64>(M));
  }
  matrix(vector<vector<i64>> _mat)
  {
    this->Matrix = _mat;
  }
  void print()
  {
    for (auto i : Matrix)
    {
      for (auto j : i)
      {
        printf("%lld ", j);
      }
      printf("\n");
    }
  }
  i64 get(int n, int m) {
    if(n>=0 && n<this->Matrix.size() && m>=0 && m<this->Matrix[0].size()) return this->Matrix[n][m];
    else throw;
  }
  matrix operator*(const matrix &rhs);
  matrix &operator=(const matrix &rhs);
};

matrix matrix::operator*(const matrix &rhs)
{
  matrix result = matrix(this->Matrix.size(), rhs.Matrix[0].size());
  for (int i = 0; i < this->Matrix.size(); i++)
  {
    for (int j = 0; j < rhs.Matrix[0].size(); j++)
    {
      for (int k = 0; k < rhs.Matrix.size(); k++)
      {
        result.Matrix[i][j] += (this->Matrix[i][k] * rhs.Matrix[k][j]);
        // result.Matrix[i][j] %= MOD;
      }
    }
  }
  return result;
}

matrix &matrix::operator=(const matrix &rhs)
{
  this->Matrix = rhs.Matrix;
  return *this;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int M;
  cin >> M;

  vector<matrix> MatL;
  vector<vector<i64>> mat;
  
  mat.resize(1);
  mat[0].push_back(8);
  mat[0].push_back(6);
  matrix initial(mat);
  
  mat.resize(2);
  mat[0].push_back(1);
  mat[0].push_back(1);
  mat[1].push_back(1);
  mat[1].push_back(0);
  MatL.push_back(matrix(mat));

  
  return 0;
}
