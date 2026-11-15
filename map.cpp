#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
//#define int long long
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)

using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
using ar3 = array<int,3>;

constexpr int mxN = (int)3e5+10;
constexpr int INF = (int)1e9+10;
constexpr ll LINF = (ll)4e18+10;
constexpr int MOD = (int)1e9+7;

constexpr int K = 12, E = 5, L = 100, MASK = (1<<(2*K))-1;
string genome;
vi head(1<<(2*K),-1), nxt;
struct Hit{ int p = 0, b = 0, d = E+1, cnt = 0; };

int base(char c){
    if(c=='A') return 0;
    if(c=='C') return 1;
    if(c=='G') return 2;
    if(c=='T') return 3;
    return -1;
}

Hit match(string s){
    Hit ans;
    for(int b = 0; b < 2; b++){
        vi cand;
        for(int j = 0; j <= E; j++){
            int off = j*L/(E+1), key = 0;
            for(int k = 0; k < K; k++){
                int x = base(s[off+k]);
                if(x<0){ key = -1; break; }
                key = (key<<2)|x;
            }
            if(key<0) continue;
            for(int p = head[key]; p!=-1; p = nxt[p])
                if(p>=off and p-off+L<=sz(genome)) cand.pb(p-off);
        }
        sort(all(cand));
        cand.erase(unique(all(cand)),cand.end());
        for(int p : cand){
            int d = 0;
            for(int i = 0; i < L and d<=min(E,ans.d); i++)
                d += base(s[i])<0 or s[i]!=genome[p+i];
            if(d>E or d>ans.d) continue;
            if(d<ans.d) ans = {p,b,d,1};
            else ans.cnt++;
        }
        reverse(all(s));
        for(char &c : s){ int x = base(c); c = x<0?'N':"TGCA"[x]; }
    }
    return ans;
}

void solve(){
    ifstream fa("data/reference.fa");
    string s;
    getline(fa,s);
    while(fa >> s) genome+=s;
    int n = genome.size(), key = 0, len = 0;
    nxt.resize(n);
    for(int i = 0; i < n; i++){
        int x = base(genome[i]);
        if(x<0){ key = len = 0; continue; }
        key = ((key<<2)|x)&MASK;
        if(++len>=K){ int p = i-K+1; nxt[p] = head[key]; head[key] = p; }
    }
    vi diff(n+1);
    ll total = 0, mapped = 0, multi = 0, errors = 0;
    while(getline(cin,s)){
        getline(cin,s);
        auto h = match(s);
        getline(cin,s); getline(cin,s); total++;
        if(h.cnt) mapped++, multi+=h.cnt>1, errors+=h.d, diff[h.p]++, diff[h.p+L]--;
    }
    ll covered = 0;
    for(int i = 0, d = 0; i < n; i++){
        d+=diff[i]; covered+=d>0;
    }
    cout << fixed << setprecision(6) << "metric\tvalue\n";
    cout << "reads\t" << total << '\n';
    cout << "mapped\t" << mapped << '\n';
    cout << "mapped_pct\t" << 100.0*mapped/total << '\n';
    cout << "unique_pct_all\t" << 100.0*(mapped-multi)/total << '\n';
    cout << "multi_pct_all\t" << 100.0*multi/total << '\n';
    cout << "identity_pct\t" << 100.0*(mapped*L-errors)/(mapped*L) << '\n';
    cout << "coverage_pct\t" << 100.0*covered/n << '\n';
    cout << "mean_depth\t" << double(mapped*L)/n << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
}
