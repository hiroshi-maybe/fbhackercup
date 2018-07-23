#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 7/22/2018 R1 A
 
 16:45-17:11 submit and got AC
 
 7/23/2018
 
 14:05-14:30 add greedy solution
 
 Editorials:
  - https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2018-round-1-solutions/2267977239884831/
  - https://www.dropbox.com/sh/ogbmd8ngoij6e6w/AAAPpKjAn6TDgmDrHxuglNa9a?dl=0
 
 Tweets:
  - https://togetter.com/li/1249478
  - dp
   - https://twitter.com/ei1333/status/1021077964476198912
   - http://naoyat.hatenablog.jp/entry/FHC2018R1
   - https://twitter.com/beet_aizu/status/1021078298967748611
   - https://twitter.com/rickytheta/status/1021078394077732864
  - greedy
   - https://twitter.com/pazzle1230/status/1021078140657926146
 
 Summary:
  - dp is straightforward
  - greedy is nice
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const LL MOD=1e9+7;
const int MAX_N=1005;
LL dp[3][MAX_N];
void solve_org(int N, vector<string> &A) {
  ZERO(dp);
  dp[0][0]=1LL;
  REP(j,N)REP(i,3) {
    if(i>0&&A[i][j]=='.'&&A[i-1][j]=='.') (dp[i-1][j+1]+=dp[i][j])%=MOD;
    if(i<2&&A[i][j]=='.'&&A[i+1][j]=='.') (dp[i+1][j+1]+=dp[i][j])%=MOD;
  }
  cout<<dp[2][N]<<endl;
}

void solve(int N, vector<string> &A) {
  LL res=1;
  if(SZ(A[0])%2==1||A[0][0]=='#'||A[1][0]=='#'||A[1][N-1]=='#'||A[2][N-1]=='#') {
    res=0;
  } else {
    for(int j=1; j<N-1; j+=2) {
      int j1=j,j2=j+1;
      LL x=0;
      if(A[1][j1]=='#'||A[1][j2]=='#') {
        x=0;
      } else {
        if(A[0][j1]!='#'&&A[0][j2]!='#') ++x;
        if(A[2][j1]!='#'&&A[2][j2]!='#') ++x;
      }
      res*=x,res%=MOD;
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N; cin>>N;
    vector<string> A(3);
    REP(i,3) cin>>A[i];
    
    cout << "Case #" << t << ": ";
    solve(N,A);
  }
  return 0;
}
