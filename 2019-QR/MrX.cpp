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

/*
 
 6/15/2019
 
 20:14-20:55 pause
 
 6/17/2019
 
 16:45-17:31 read editorial and add solution
 
 https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2019-qualification-round-solutions/2797355073613709/
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG MrX.cpp && ./a.out < MrX.in | diff MrX.out -
string S;
set<char> lits={'X','x','0','1'};
set<char> ops={'&','|','^'};
map<char,char> inv={{'x','X'},{'X','x'},{'1','0'},{'0','1'}};
int findop(int l, int r) {
  int b=0;
  FORE(i,l,r) {
    if(b==0&&ops.count(S[i])) return i;
    if(S[i]=='(') ++b;
    else if(S[i]==')') --b;
  }
  dump(l,r,S.substr(l,r-l+1));
  assert(false);
}
char apply(char l, char op, char r) {
  assert(lits.count(l));
  assert(lits.count(r));
  assert(ops.count(op));
  if(op=='|') {
    if(l=='1'||r=='1') return '1';
    if(l=='0') return r;
    if(r=='0') return l;
    if(l==r) return l;
    return '1';
  }
  if(op=='&') {
    if(l=='1') return r;
    if(r=='1') return l;
    if(l=='0'||r=='0') return '0';
    if(l==r) return l;
    return '0';
  }
  if(op=='^') {
    if(l=='1') return inv[r];
    if(r=='1') return inv[l];
    if(l=='0') return r;
    if(r=='0') return l;
    if(l!=r) return '1';
    return '0';
  }
  assert(false);
}
char parse(int l, int r) {
  if(l==r) return S[l];
  char lexp,rexp,op;
  if(S[l]=='(') {
    assert(S[r]==')');
    int oppos=findop(l+1,r-1);
    op=S[oppos];
    lexp=parse(l+1,oppos-1),rexp=parse(oppos+1,r-1);
  } else {
    assert(r-l+1==3);
    lexp=S[l],rexp=S[r],op=S[l+1];
  }
  return apply(lexp,op,rexp);
}
void solve() {
  char res=parse(0, SZ(S)-1);
//  dump(res);
  int ans=1;
  if(res=='0'||res=='1') ans=0;
  cout<<ans<<endl;
}
int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>S;
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
