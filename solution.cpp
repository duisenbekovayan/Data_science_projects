#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> bit;
    int n;
    Fenwick(int n): n(n), bit(n+1, 0) {}
    void add(int idx, int delta) {
        for (int i = idx; i<=n; i += i & -i) bit[i]+=delta;
    }
    int sumPrefix(int idx) const {
        int res=0;
        for (int i=idx; i>0; i-= i & -i) res += bit[i];
        return res;
    }
    // total sum
    int sumAll() const {
        return sumPrefix(n);
    }
    // find smallest idx such that prefix sum >= target (1-indexed). If total < target returns n+1.
    int lower_bound_prefix(int target) const {
        int idx=0;
        int mask = 1<<20; // since n <= 2e5 < 1<<18, safe.
        while(mask){
            int next = idx + mask;
            if(next<=n && bit[next] < target){
                target -= bit[next];
                idx = next;
            }
            mask >>=1;
        }
        return idx+1; // 1-indexed answer
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; if(!(cin>>t)) return 0;
    while(t--){
        int n,m; cin>>n>>m;
        int totalQueries = 2*m;
        vector<pair<int,int>> queries(totalQueries);
        // store queries by l
        vector<vector<int>> byL(n+2);
        for(int i=0;i<totalQueries;i++){
            int l,r;cin>>l>>r;
            queries[i]={l,r};
            byL[l].push_back(r);
        }
        Fenwick bit(n); // BIT over r from 1..n
        int totalInserted=0;
        int foundX=-1,foundY=-1;
        for(int x=1; x<=n-1 && foundX==-1; ++x){
            // insert queries with l == x
            for(int r: byL[x]){
                bit.add(r,1);
                ++totalInserted;
            }
            if(totalInserted < m) continue; // not enough to reach m yes queries
            int k = totalInserted - m; // need exactly k queries with r < y
            if(k<0 || k>totalInserted) continue; // impossible
            // we need y such that prefix_sum(y-1) == k
            // Use binary search via BIT lower_bound to find first idx with prefix >= k
            int y_minus1;
            if(k==0){
                y_minus1 = 0; // prefix at 0 is 0, we need y = 1
            }else{
                int idx = bit.lower_bound_prefix(k); // prefix >=k
                int pref = bit.sumPrefix(idx);
                if(pref != k){
                    continue; // no y such that prefix==k
                }
                y_minus1 = idx; // prefix at idx == k -> y = idx+1
            }
            int y = y_minus1 + 1;
            if(y > n) continue; // cannot exceed n
            if(y <= x) continue; // must be after x (at least x+1)
            foundX=x;
            foundY=y;
            break;
        }
        if(foundX==-1){
            cout<<-1<<"\n";
            continue;
        }
        vector<int> a(n+1);
        for(int i=1;i<=n;i++) a[i]=i;
        a[foundY]=a[foundX];
        for(int i=1;i<=n;i++){
            if(i>1) cout<<' ';
            cout<<a[i];
        }
        cout<<"\n";
    }
    return 0;
}