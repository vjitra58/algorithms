#include <bits/stdc++.h>
using namespace std;
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define int long long
const int infinity = 1e18+2;
const int MOD = 1e9+7;
#define lbit(x) ((x)&(-x))
const int N = 2e5+5;

int n, q;
int a[N];

struct node{
	int mn,sm, lz;
}st[1<<20];

void apply(int i, int val, int lo, int hi){
	st[i].mn += val;
	st[i].sm += (hi-lo+1)*val;
	st[i].lz += val;
}

void push(int i, int lo, int m, int hi){
	apply(2*i, st[i].lz, lo, m);
	apply(2*i+1, st[i].lz, m+1, hi);
	st[i].lz = 0;
}


void update(int ind, int val, int i=1, int lo=0, int hi=n-1){
	if(lo == hi){
		st[i].mn = val;
		st[i].sm = val;
		return;
	}
	int m = (lo + hi)/2;
	push(i, lo, m, hi);
	if(ind <= m){//call left
		update(ind, val, 2*i, lo, m);
	}else{
		update(ind, val, 2*i+1, m+1, hi);
	}
	st[i].mn = min(st[2*i].mn, st[2*i+1].mn);
	st[i].sm = st[2*i].sm + st[2*i+1].sm;
}

void update2(int a, int b, int val, int i=1, int lo=0, int hi=n-1){
	if(lo>=a && hi<=b){
		apply(i, val, lo, hi);
		return;
	}
	int m = (lo+hi)/2;
	push(i, lo, m, hi);
	if(a <= m){
		update2(a, b, val, 2*i, lo, m);
	}
	if(b > m){
		update2(a, b, val, 2*i+1, m+1, hi);
	}
	st[i].mn = min(st[2*i].mn, st[2*i+1].mn);
	st[i].sm = st[2*i].sm + st[2*i+1].sm;
}

int query(int a, int b, int i=1 , int lo=0, int hi=n-1){
	if(lo>=a && hi<=b){
		return st[i].sm;
	}
	int m = (lo+hi)/2;
	push(i, lo, m, hi);
	int left=0, right = 0;
	if(a <= m){
		left = query(a, b, 2*i, lo, m);
	}
	if(b > m){
		right = query(a, b, 2*i+1, m+1, hi);
	}
	return left + right;
}

int32_t main(){	
	fast_io;
	cin>>n>>q;
	for(int i=0; i<n; i++){
		cin>>a[i];
		update(i, a[i]);
	}
	
	while(q--){
		int op;cin>>op;
		if(op==1){
			int a, b, u;cin>>a>>b>>u;
			a--, b--;
			update2(a, b, u);
		}else{
			int k;cin>>k;
			k--;
			int ans = query(k, k);
			cout<<ans<<endl;
		}
	}
	
	
	// for(int i=0; i<4*n+1; i++){
	// 	cout<<"["<<lo[i]<<" "<<hi[i]<<"] ---> "<<store[i]<<endl;
	// }
}
