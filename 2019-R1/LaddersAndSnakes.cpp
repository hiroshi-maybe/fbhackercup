#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
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

const int MAX_V=100;
template<class V> class Dinic {
public:
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }
  
  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      bfs(s);
      if(dist[t]<0) return res; // t is unreachable
      memset(iter,0,sizeof(iter));
      V f;
      while((f=dfs(s,t,Inf))>0) res+=f;
    }
    
    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<Edge> E[MAX_V]; // Graph
  int dist[MAX_V]; // distance from `s`
  int iter[MAX_V];
  
  // initialize shoftest path and store in `level`
  void bfs(int s) {
    memset(dist,-1,sizeof(dist));
    
    queue<int> Q;
    dist[s]=0;
    Q.push(s);
    
    while(Q.size()) {
      int u=Q.front(); Q.pop();
      
      for(int i=0; i<E[u].size(); ++i) {
        Edge &e=E[u][i];
        int v=e.to;
        if(e.cap<=0) continue;
        if(dist[v]>=0) continue; // visited
        
        dist[v]=dist[u]+1;
        Q.push(v);
      }
    }
  }
  
  // find augmenting path in residual network and update f
  V dfs(int u, int t, V f) {
    if(u==t) return f;
    for(int &i=iter[u]; i<E[u].size(); ++i) { // visit E[u] only once
      Edge &e=E[u][i];
      int v=e.to;
      if(e.cap<=0) continue;
      if(dist[u]>=dist[v]) continue;
      
      V d=dfs(v,t,min(f,e.cap));
      if(d<=0) continue;
      e.cap-=d;
      E[v][e.rev].cap+=d; // cancellation increases
      return d;
    }
    
    return 0;
  }
};

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG LaddersAndSnakes.cpp && ./a.out < LaddersAndSnakes.in | diff LaddersAndSnakes.out -

/*
 
 6/29/2019
 
 16:16-17:50 give up
 
 7/3/2019
 
 20:40-21:50 read editorial and got AC
 
 https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2019-round-1-solutions/2835573686458514/
 
 I figured out that this is graph problem though, I completely missed flow out of mind.
 
 */

int N,H;

const int Inf=1e8;

int src=0,sink=99;
map<int,int> G[MAX_V];
void solve() {
  Dinic<LL> F;
  REP(u,MAX_V)FORR(p,G[u]) {
    int v=p.first,w=p.second;
    F.addEdge(u,v,w);
//    dump(u,v,w);
  }
  LL res=F.maxFlow(src, sink);
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    REP(i,MAX_V) G[i].clear();
    
    cin>>N>>H;
    VV<II> X(H+1);
    REP(i,N) {
      int x,a,b; cin>>x>>a>>b;
      FOR(y,a,b) X[y].emplace_back(x,i+1);
    }
    REPE(i,H) sort(ALL(X[i]));
    REPE(y,H) REP(j,SZ(X[y])-1) {
      int u=X[y][j].second,v=X[y][j+1].second;
      G[u][v]++,G[v][u]++;
    }
//    dumpc(X[0]);
//    dumpc(X[H]);
    FORR(p,X[0]) G[src][p.second]=G[p.second][src]=Inf+100;
    FORR(p,X[H-1]) G[sink][p.second]=G[p.second][sink]=Inf+100;
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
