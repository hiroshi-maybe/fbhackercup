#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<LL,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 6/29/2019
 
 13:59-14:40 submit and got AC
 
 https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2019-round-1-solutions/2835573686458514/
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG GraphsAsAService.cpp && ./a.out < GraphsAsAService.in | diff GraphsAsAService.out -
const int MAX_N=51+1;
int N,M;

const LL Inf=1e14;

vector<III> ds;
LL mx[MAX_N][MAX_N];
void solve() {
  FORR(t,ds) {
    int u,v; LL w; tie(w,u,v)=t;
    mx[u][v]=mx[v][u]=w;
  }
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx[i][j],mx[i][k]+mx[k][j]);
  FORR(t,ds) {
    int u,v; LL w; tie(w,u,v)=t;
    if(mx[u][v]!=w) {
      cout<<"Impossible"<<endl;
      return;
    }
  }
  cout<<M<<endl;
  FORR(t,ds) {
    int u,v; LL w; tie(w,u,v)=t;
    cout<<(u+1)<<" "<<(v+1)<<" "<<w<<endl;
  }
}

int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>M;
    REP(i,N)REP(j,N) mx[i][j]=(i==j?0:Inf);
    ds=vector<III>(M);
    REP(i,M) {
      int u,v,w; cin>>u>>v>>w;
      --u,--v;
      ds[i]={w,u,v};
    }
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
