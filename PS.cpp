#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> ti;

#define MOD 1000000007

class matrix {
public:
  vector<vector<ll> > Matrix;
  matrix(int N, int M) {
    Matrix.resize(N, vector<ll>(M));
  }
  matrix(vector<vector<ll> > _mat) {
    Matrix=_mat;
  }
  void print() {
    for(auto i:Matrix) {
      for(auto j:i) {
        printf("%lld ", j);
      }
      printf("\n");
    }
  }
  matrix operator*(const matrix &rhs);
  matrix& operator=(const matrix &rhs);
};

matrix matrix::operator*(const matrix &rhs) {
  matrix result=matrix(this->Matrix.size(), rhs.Matrix[0].size());
  for(int i=0; i<this->Matrix.size();i++) {
    for(int j=0;j<rhs.Matrix[0].size();j++) {
      for(int k=0;k<rhs.Matrix.size();k++) {
        result.Matrix[i][j]+=(this->Matrix[i][k] * rhs.Matrix[k][j]);
        result.Matrix[i][j] %= MOD;
      }
    }
  }
  return result;
}

matrix& matrix::operator=(const matrix &rhs) {
  this->Matrix=rhs.Matrix;
  return *this;
}

ll N;
int M;
vector<matrix> Mlist;

matrix generate_basic_matrix(int N) {
  matrix result=matrix(N, N);
  result.Matrix[0][0]=1;
  result.Matrix[0][N-1]=1;
  for(int i=1;i<N;i++) result.Matrix[i][i-1]=1;
  return result;
}

int main() {
  cin>>N>>M;
  Mlist.push_back(generate_basic_matrix(M));
  for(ll i=0;i<ceil(log2((long double)(N)));i++)
    Mlist.push_back(Mlist.back()*Mlist.back());

  if(N<M) {
    cout<<1<<endl;
    return 0;
  }
  auto targ=N-M+1;
  ll cnt=0;
  matrix res=matrix(M, 1);
  for(int i=0;i<M;i++) {
    res.Matrix[i][0]=1;
  }
  while(targ!=0) {
    if(targ%2==1) {
      res=Mlist[cnt]*res
    }
    cnt++;
    targ/=2;
  }
  cout<<res.Matrix[0][0]<<endl;
  return 0;
}
