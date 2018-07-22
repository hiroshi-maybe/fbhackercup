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

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const int MAX_N=2005;
VI G[MAX_N];
VI S1,S2;
struct UF {
public:
  int groupNum;
  vector<int> uf;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }
  
  int find(int i) {
    return uf[i]==i?i:uf[i]=find(uf[i]);
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return;
    groupNum--;
    
    if (rank[x]==rank[y]) {
      uf[x]=y;
      rank[y]++;
      return;
    }
    
    if (rank[x]<rank[y]) {
      uf[x]=y;
    } else {
      uf[y] =x;
      if(rank[x]==rank[y]) ++rank[x];
    }
  }
private:
  vector<int> rank;
};

void preord(int u) {
  if(u>-1) {
    S1.push_back(u);
    assert(SZ(G[u])==2);
    preord(G[u][0]),preord(G[u][1]);
  }
}
void postord(int u) {
  if(u>-1) {
    assert(SZ(G[u])==2);
    postord(G[u][0]),postord(G[u][1]);
    S2.push_back(u);
  }
}

const string no="Impossible";

int ngcnt=0;
void assertTree(int N, UF &uf, MAPII &M) {
  VI SS1(N),SS2(N);
  REP(i,N) {
//    dump3(i,)
    SS1[i]=M[uf.uf[S1[i]]]+1;
    SS2[i]=M[uf.uf[S2[i]]]+1;
  }
  int ng=0;
  REP(i,N) {
    if(SS1[i]!=SS2[i]) {
      ng++;
//      dump3(i,SS1[i],SS2[i]);
//      dumpAR(SS1);
//      dumpAR(SS2);
    }
//    assert(SS1[i]==SS2[i]);
  }
  if(ng>0) ++ngcnt;
}

void solve(int N, int K) {
  preord(0),postord(0);
  assert(SZ(S1)==SZ(S2));
  UF uf(N);
  REP(i,N) uf.unite(S1[i],S2[i]);
  if(uf.groupNum<K) {
    cout<<no<<endl;
  } else {
    VI res(N);
    int x=0;
    MAPII M;
    REP(i,N) {
      int g=uf.uf[i];
      if(M.count(g)==0) M[g]=(x++)%K;
      cout<<M[g]+1<<(i==N-1?'\n':' ');
    }
    assertTree(N,uf,M);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    dump(t);
    REP(i,MAX_N) G[i].clear();
    S1.clear(),S2.clear();
    int N,K; cin>>N>>K;
    dump2(N,K);
    REP(i,N) {
      int u=i,v1,v2;
      cin>>v1>>v2;
      --v1,--v2;
//      dump3(u,v1,v2);
      G[u].push_back(v1);
      G[u].push_back(v2);
    }
    cout << "Case #" << t << ": ";
    solve(N,K);
  }
  dump(ngcnt);
  return 0;
}
