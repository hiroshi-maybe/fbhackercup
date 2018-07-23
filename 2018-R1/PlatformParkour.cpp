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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 7/22/2018 R1 C
 
 19:25-22:00 time is up
 
 7/23/2018
 
 16:10-18:05, 21:30-22:16 read editorials and add solution
 
 Editorials:
  - https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2018-round-1-solutions/2267977239884831/
  - https://www.dropbox.com/sh/ogbmd8ngoij6e6w/AAAPpKjAn6TDgmDrHxuglNa9a?dl=0&preview=platform_parkour.cpp

 Tweets:
  - https://togetter.com/li/1249478
  - https://twitter.com/HIR180/status/1021078100501598208
  - https://twitter.com/rickytheta/status/1021078394077732864
  - https://twitter.com/snuke_/status/1021079856266719232
  - https://twitter.com/ei1333/status/1021077964476198912
  - https://twitter.com/ei1333/status/1021078292932120576
  - https://twitter.com/beet_aizu/status/1021078298967748611

 Key:
  - binary search
  - R-to-L move can be transformed equivalent L-to-R move
  - O(N) check per minimum time by looking at preferred range
   - possible heights are represented in "range" (not specific height)
   - if multiple constraints exist, smaller U[i]/D[i] is harder to satisfy
   - maintain lower bound and upper bound in range format to check validity
 
 Summary:
  - I reached binary search. However I couldn't implement check function for given minimum time
  - My first approach was changing heights toward (max{H} + min{H})/2. However it doesn't necessarily optimal
  - I couldn't figure out that possible height can be verified by "range" 👎
   - keeping range by deltas is typical
   - no valid reasoning that specific value instead of range is sufficient
  - I strongly believe that I've seen similar problem which solves intervals with binary search
   - My learning is something wrong
   - Understanding solution is not enough. I should have reduced to another problem with necessary & sufficient condition
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
// 19:25-
LL MID;
const int MAX_M=25;
int A[MAX_M],B[MAX_M];
LL U[MAX_M],D[MAX_M];
int deltai(int a, int b) {
  return a<b?1:-1;
}
bool f(LL dt, int N, vector<LL> &H, int M) {
  vector<LL> HH(N);
  REP(i,N) {
//    if(H[i]<=MID) { dump3(H[i]+dt,MID,min(H[i]+dt,MID)); }
//    else { dump3(H[i]-dt,MID,max(H[i]-dt,MID)); }
    HH[i]=H[i]<=MID?min(H[i]+dt,MID):max(H[i]-dt,MID);
  }
  dumpAR(HH);
  REP(i,M) {
    bool ok=true;
    
    if(A[i]<B[i]) {
      FORE(j,A[i]+1,B[i]) {
        LL a=HH[j-1],b=HH[j];
        if(a<b) ok&=a+U[i]>=b;
        else if(a>b) ok&=a-D[i]<=b;
        dump4(j,a,b,ok);
      }
    } else {
      for(int j=A[i]-1; j>=B[i]; --j) {
        LL a=HH[j+1],b=HH[j];
        if(a<b) ok&=a+U[i]>=b;
        else if(a>b) ok&=a-D[i]<=b;
        dump4(j,a,b,ok);
      }
    }
    /*
    for(int j=A[i]+deltai(A[i],B[i]); (deltai(A[i],B[i])>0?j<=B[i]:j>=A[i]); j+=deltai(A[i],B[i])) {
      int pre=deltai(A[i],B[i])>0?j-1:j+1;
      LL a=HH[pre],b=HH[j];
      if(a==b) continue;
      else if(a<b) ok&=a+U[i]>=b;
      else ok&=a-D[i]<=b;
      dump4(j,a,b,ok);
    }*/
    if(!ok) return false;
  }
  return true;
}

void solve_wrong(int N, vector<LL> &H, int M) {
//  LL L=*min_element(H.begin(),H.end()),R=*max_element(H.begin(),H.end());
//  MID=(R+L)/2;
//  dump3(L,R,MID);
  LL good=1e7,bad=-1;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool ok=f(mid,N,H,M);
    dump4(good,bad,mid,ok);
    (ok?good:bad)=mid;
  }
//  dump(good);
  assert(f(good,N,H,M));
  double res=0.5*good;
  cout<<setprecision(12)<<fixed<<res<<endl;
}

//int UD[MAX_N];
int isup(int a, int b) {
  assert(a!=b);
  return a<b?1:0;
}

const double Inf=1e7;
const int MAX_N=2e5+10;
double UU[MAX_N],DD[MAX_N];
bool f2(double dt, int N, vector<LL> &H, int M) {
  double L=H[0]-dt,R=H[0]+dt;
  FOR(i,1,N) {
    double l1=max(0.0,L-DD[i-1]),r1=R+UU[i-1];
    double l2=max(0.0,H[i]-dt),r2=H[i]+dt;
    L=max(l1,l2),R=min(r1,r2);
//    dump3(i,L,R);
//    dump4(l1,r1,l2,r2);
    if(L>R) return false;
  }
  return true;
}

void solve(int N, vector<LL> &H, int M) {
  REP(i,M) if(A[i]>B[i]) swap(U[i],D[i]),swap(A[i],B[i]);
  REP(i,N) UU[i]=Inf,DD[i]=Inf;
  REP(i,M) FOR(j,A[i],B[i]) {
    SMIN(UU[j],(double)U[i]);
    SMIN(DD[j],(double)D[i]);
  }
  REP(i,N) dump3(i,UU[i],DD[i]);
  
  double good=1e7,bad=0.0;
  REP(_,100) {
    double mid=(good+bad)/2;
    bool ok=f2(mid,N,H,M);
//    dump4(good,bad,mid,ok);
    (ok?good:bad)=mid;
  }
  //  dump(good);
//  assert(f(good,N,H,M));
  cout<<setprecision(6)<<fixed<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N,M,H1,H2,W,X,Y,Z;
    cin>>N>>M;
    cin>>H1>>H2>>W>>X>>Y>>Z;
    vector<LL> H(N);
    H[0]=H1,H[1]=H2;
    FOR(i,2,N) H[i]=(1LL*W*H[i-2]+1LL*X*H[i-1]+Y)%Z;
//    REP(i,N) H[i]*=2LL;
    dumpAR(H);
    REP(i,M) {
      cin>>A[i]>>B[i]>>U[i]>>D[i];
      A[i]--,B[i]--;
//      U[i]*=2LL,D[i]*=2LL;
    }
    cout << "Case #" << t << ": ";
    solve(N,H,M);
  }
  return 0;
}
