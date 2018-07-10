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
 
 13:00-14:00 analysis beside beach in Ogasawara
 
 7/9/2018
 
 18:00-20:00 implement, test and submit and got AC
 
 Editorial:
  - https://www.facebook.com/notes/2249775598371662
  - https://www.dropbox.com/sh/h68xcs9kniokeiu/AAALoB9pZq0FoLSs-nKBClzKa?dl=0
 
 Summary:
  - Inspired by KMP, my solution is unnecessarily complex
  - Actually the first solution `solve_old()` was not bad. Analysis of periodic prefix was missing.. 😞
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
vector<int> buildPrefixFunction(const string P) {
  int L = P.size();
  vector<int> pi(L+1, 0);
  
  if (L==0) return pi;
  
  int j=0;
  for(int i=2; i<L; ++i) {
    j = pi[i-1];
    while(true) {
      if (P[j]==P[i-1]) {
        // matched
        pi[i] = j+1; break;
      }
      // unmatced below
      
      // reached to head
      if (j==0) {
        pi[i] = 0; break;
      }
      j = pi[j];
    }
  }
  
  return pi;
}

int SMT[2024][26];
void buildSMT(string P) {
  memset(SMT, 0, sizeof SMT);
  int L=P.size();
  for(int i=0; i<=L; ++i) {
    for(int j=0; j<26; ++j) {
      char c = 'A'+j;
      if (i<L&&c==P[i]) {
        // matched
        SMT[i][j]=i+1;
      } else {
        // unmatched
        string suf = P.substr(0,i)+c;
        int SL=(int)suf.size();
        // find longest prefix P[0..<k]
        for(int k=1; k<=i; ++k) if(P.substr(0,k)==suf.substr(SL-k)) SMT[i][j]=k;
      }
    }
  }
//  REP(i,SZ(P)) REP(j,26) dump3(i,j,SMT[i][j]);
}

int doKMP(string s, string p) {
  int i = 0, j = 0, L = s.size(), M = p.size();
  
  vector<int> pi = buildPrefixFunction(p);
  while (i<L) {
    if (s[i]==p[j]) {
      i++; j++;
      if (j==M) return i-M;
    } else if (j > 0) {
      j = pi[j];
    } else {
      i++;
    }
  }
  
  return -1;
}

bool contains(string &A, string &B) {
  /*
   int l1=SZ(A),l2=SZ(B);
   assert(l1<=l2);
   return B.substr(l2-l1,l1)==A;
   */
  int x=doKMP(B,A);
  return x!=-1;
}

bool ets(string &A, string &B) {
  int i=0,j=0;
  while(true) {
    if(i>=SZ(A)) return true;
    if(j>=SZ(B)) return false;
    if(A[i]==B[j]) {
      ++i,++j;
    } else if(i==0) {
      ++j;
    } else {
      i=0;
    }
  }
}

const string no="Impossible";
string solve(string &A) {
  auto P = buildPrefixFunction(A);
//  dumpAR(P);
  
  string res=no;
  REP(i,SZ(A)) if(P[i]>0) {
    int p=P[i];
    if(A[p]==A[i]) continue;
    res=A.substr(0,i)+A[p];
    
    res+=A.substr(p+1);
    break;
  }
  
  if(res!=no) {
    if(ets(A,res)||!contains(A,res)) dump2(A,res);
    assert(contains(A,res));
    assert(ets(A,res)==false);
  }
  
  return res;
}

string solve_slow(string &A) {
  buildSMT(A);

  string res=no;
  REP(i,SZ(A)) {
    REP(j,26) if(SMT[i][j]>=2&&SMT[i][j]!=i+1) {
//      dump2(i,j);
      char c='A'+j;
      res=A.substr(0,i)+c;
      res+=A.substr(SMT[i][j]);
      goto last;
    }
  }
last:
  
  return res;
}

string solve_old(string &A) {
  int N=SZ(A);
  if(N==2) return no;
  FOR(i,2,N-1) if(A[i]==A[0]&&A[i+1]!=A[1]) {
    string P=A.substr(0,i),Q=A.substr(i,N-i);
    return P+P+Q;
  }
  return no;
}

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

string genRandStr(int size) {
  string res;
  REP(_,size) {
    res.push_back('A'+genRandNum(0,26));
  }
  return res;
}

pair<string,string> gen() {
  int LA=genRandNum(1,2000);
  string A=genRandStr(LA);
  int LB=genRandNum(LA,2*LA);
  string B=A;
  REP(i,LB-LA) {
    char c='A'+genRandNum(0,26);
    assert('A'<=c&&c<='Z');
    if(genRandNum(0,2)) B.push_back(c);
    else B=c+B;
  }
  return {A,B};
}

void stress_test() {
  int c=0;
  while(c<100) {
    string A,B;
    tie(A,B)=gen();
    //    if(A[0]==A[1]) continue;
    assert(contains(A,B));
    string res=solve(A);
//    string res2=solve_slow(A);
//    if(res!=res2) dump3(A,res,res2);
//    assert(res==res2);
    dump3(A,B,res);
    if(ets(A,B)==false) {
      assert(res!=no);
    } else {
      if(res!=no) assert(ets(A,res)==false);
    }
    ++c;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    string A; cin>>A;
    cout << "Case #" << t << ": ";
    string res=solve(A);

    cout<<res<<endl;
  }

//  stress_test();
  
  return 0;
}
