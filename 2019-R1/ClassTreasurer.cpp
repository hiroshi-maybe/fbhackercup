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
const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};
/*
 
 6/29/2019
 
 14:45-16:00 give up
 
 Assign positions to changes: O(2^N) time
 Check validity: O(N^2) time
 
 I transformed to binary representation where B->0,A->1.
 Cost to change from 0 to 1 at `i` is 2^i
 
 I imagined that there is a way to solve this by greedy algorithm.
 However I didn't come up with it.
 
 7/3/2019
 
 14:50-16:50 read editorials and got AC
 
 https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2019-round-1-solutions/2835573686458514/
 https://twitter.com/n_vip/status/1145380104727482368
 
 - Remember largest consecutive sum
  - Kadane's algorithm
  - We can ignore smaller sums
 - Greedy from right to left
  - due to condition 2^x > ∑{i = 1..(x-1) | 2^i}
 
 From condition 2^x>∑{2^i:i=1..x-1}, we want to choose position of B->A as left as possible.
 We want to avoid cnt(B,l,r)-cnt(A,l,r)>K. Thus we look at..
 
  max { cnt(B,l,r)-cnt(A,l,r)>K }
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG ClassTreasurer.cpp && ./a.out < ClassTreasurer.in | diff ClassTreasurer.out -
//const int MAX_N=1e6+1;
string S;
int N,K;
void solve() {
//  dump(N,K,S);
  ModInt res=0;
  LL bal=0;
  for(int i=N-1; i>=0; --i) {
    LL d=(S[i]=='B')?1LL:-1LL;
    bal+=d;
    bal=max(d,bal);
    if(bal>K) res+=ModInt(2).pow(i+1),bal-=2;
    bal=max(0LL,bal);
  }
  cout<<res<<endl;
}
int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>K>>S;
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
