#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

vector<int> one;
vector<int> lazyflip;

int from;
int to;
void update (int node,int left,int right ){
	if ( left>to || right <from){
		return;
	}
	else if (left>=from && right<=to){
		one[node]=(right - left + 1) - one[node] ;
		 
		lazyflip[node]+=1;
		if ( lazyflip[node] > 1){
			lazyflip[node]-=2;		 
		}
		return;
	}
	update (node<<1, left, (left+right)/2);
	update ((node<<1)+1, (left+right)/2 + 1, right);
	one [node] = one [node<<1] + one [(node<<1)+1];
	 
	if (lazyflip[node]==1){
		one[node]=right - left + 1 - one[node] ;
	}
	return;
}

int query (int node, int left , int right, int flag ){
	if (left > to || right <from ){
		return 0;
	}
	else if ( left >= from && right <= to){
		if (flag == 0)
			return one[node] ;
		else
			return right-left + 1 - one[node];	 
	}
	int newflag= flag + lazyflip[node];
	if (newflag>1){
		newflag-=2;
	}
	return query ( node<<1, left, (left+right)/2,newflag) + query ((node<<1)+1,(left+right)/2 +1,right , newflag);
}

int main(){
	int N,M,a,b,type;
	cin >> N >> M;
	one.resize(1000001);
	lazyflip.resize(1000001);

	while(M--){
		cin >> type >> a >> b;
		from = a+1;
		to = b+1;
		if (type==0)
			update(1,1,N);
		else
			cout << query(1,1,N,0) << endl;
	}
}