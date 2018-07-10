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
 
 7/7/2018
 
 19:00-20:00 analysis watching turtle's hatch
 
 7/8/2018
 
 10:00-10:30 implement, submit and got ACC
 
 Editorial:
  - https://www.facebook.com/notes/2249775598371662
  - https://www.dropbox.com/sh/h68xcs9kniokeiu/AAALoB9pZq0FoLSs-nKBClzKa?dl=0
 
 Summary:
  - I could simplify more
   - Once `l` is determined, we can just iterate (l+i)%N for i=0..K-1
   - After get right list by sorting by visited order
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
void solve(LL N, LL K, LL V, vector<string> &A) {
//  dumpAR(A);
  LL l=(V-1)*K%N,r=V*K%N;
  vector<string> res;
  if(l>r) {
    REP(i,r) res.push_back(A[i]);
    FOR(i,l,N) res.push_back(A[i]);
  } else if(l<r) {
    FOR(i,l,r) res.push_back(A[i]);
  } else {
    REP(i,N) res.push_back(A[i]);
  }
//  dump2(l,r);
  assert(SZ(res)==K);
  REP(i,K) cout<<res[i]<<(i==K-1?'\n':' ');
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N,K; LL V;
    cin>>N>>K>>V;
    vector<string> A(N);
    REP(i,N) cin>>A[i];
    
    cout << "Case #" << t << ": ";
    solve(N,K,V,A);
  }
  return 0;
}
