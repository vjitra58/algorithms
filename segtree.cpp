#include <bits/stdc++.h>
using namespace std;
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define int long long
const int infinity = 1e18+2;
const int MOD = 1e9+7;
#define lbit(x) ((x)&(-x))
const int N = 2e5+5;

class segTree{
	int n;
	vector<int> lo, hi, store, delta;
public:
	segTree(int n){
		this->n = n;
		lo.resize(4*n+1);
		hi.resize(4*n+1);
		store.resize(4*n+1);
		delta.resize(4*n+1);//used for lazy propagation
		
		init(1, 0, n-1);
	}
	
	void init(int i, int a, int b){
		lo[i] = a;
		hi[i] = b;
		if(a==b)return;
		int m = a + (b-a)/2;
		init(2*i, a, m);
		init(2*i+1, m+1, b);
	}
	
	//helper functions -----------------------------------------------
	void prop(int i){
		delta[2*i] += delta[i];
		delta[2*i+1] += delta[i];
		delta[i] = 0;					//for min-query
	}
	
	void update(int i){
		store[i] = min(store[2*i] + delta[2*i], store[2*i+1] + delta[2*i+1]);
	}
	//end of helper function -------------------------------------------
	
	void updateRange(int a, int b, int val){
		increment(1, a, b, val);
	}
	
	int query(int a, int b){
		return minimum(1, a, b);
	}
	
	void increment(int i, int a, int b, int val){
		if(b < lo[i] || a > hi[i])return; //outside range of i;
		
		if(lo[i]>=a && hi[i]<=b){//range of i lies comletely inside [a..b]
			delta[i] += val;          //lazy step //for min-query
			return;
		}
		//partial coverage;
		prop(i);
		
		increment(2*i, a, b, val);
		increment(2*i+1, a, b, val);
		
		update(i);
		
	}
	
	int minimum(int i, int a,int b){
		if(a>hi[i] || b < lo[i]){
			return infinity;						//for min-query
		}
		if(a>lo[i] && b<hi[i]){
			return store[i] + delta[i];				//for min-query
		}
		//partial overlap case;
		prop(i);
		
		int minleft = minimum(2*i, a, b);
		int minright = minimum(2*i+1, a, b);
		
		update(i);
		return min(minleft, minright);
	}
	
}



int32_t main(){	
	fast_io;
	
}
