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
 
 7/8/2018
 
 9:00-9:30 analysis eating shark burger
 10:30-11:00 implement, submit and got AC
 
 Editorial:
  - https://www.facebook.com/notes/2249775598371662
  - https://www.dropbox.com/sh/h68xcs9kniokeiu/AAALoB9pZq0FoLSs-nKBClzKa?dl=0
 
 Summary:
  - Looks like analysis of negative p for x^p is redundant. This problem is well defined? 🤔
  - Anyway test cases passed
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
void solve(int N, vector<int> &P) {
//  dumpAR(P);
  vector<double> res(0);
  REP(i,N) {
    int a=P[N-i]+i+1;
    if(a<0) break;
  }
  if(N%2==1) res.push_back(0.0);
  cout<<SZ(res)<<endl;
  if(!res.empty()) REP(i,SZ(res)) cout<<setprecision(8)<<fixed<<res[i]<<(i==SZ(res)-1?'\n':' ');
}
int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N; cin>>N;
    vector<int> P(N+1);
    REP(i,N+1) cin>>P[i];
    
    cout << "Case #" << t << ": ";
    solve(N,P);
  }
  return 0;
}
