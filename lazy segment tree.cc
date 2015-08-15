#include <algorithm>
#include <bitset>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string.h>
#include <vector>

using namespace std;
#define SZ 1000

struct Node{
    int sum ;
    int acw ;
    void leafSetUp(int value){
        sum = value;
        acw = 0;
    }

}t[SZ*3];

int n;
int  a[100000+1];

void build(int node, int b, int e){
    if( b == e ){t[node].sum = a[b];return;}
    int mid = (b + e) >> 1;
    int lson = node << 1;
    build(lson, b, mid);
    build(lson|1, mid+1, e);
    t[node].sum = t[lson].sum + t[lson|1].sum  + (e - b +1)*t[node].acw;

}
int query(int node, int b, int e, int from, int to, int carry = 0){
    if( b > to || e < from) return 0;
    if(b >= from && e <= to) return t[node].sum + (e - b + 1)*carry ;
    int mid = (b + e) >> 1;
    int lson = node << 1;
    int ret = 0;
    ret += query(lson, b, mid, from, to, carry+t[node].acw);
    ret+= query(lson|1, mid+1, e, from, to, carry+t[node].acw);
    return ret;

}
void update(int node, int b, int e, int from, int to, int w){

    if( b > to || e < from)return;
    if(b >= from && e <= to){
        t[node].sum += (e - b +1)*w;
        t[node].acw += w;
        return;
    }
    int lson = node << 1;
    int mid = (b + e) >> 1;

        update(lson, b, mid, from, to, w);
        update(lson|1, mid+1, e, from, to, w);
        t[node].sum = t[lson].sum + t[lson|1].sum + (e - b + 1)*t[node].acw;
    }
int main(){
    int op;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int from, to, w,q;
    while(scanf("%d", &n) == 1){
        for(int k = 1; k <= n; k++ )
            scanf("%d", &a[k]);
	//you should reset t for every test case
        build(1,1,n);
        scanf("%d", &q);
        while(q--){
            scanf("%d", &op);
            if(op){
                scanf("%d %d", &from, &to);
                printf("%d\n", query(1, 1, n, from, to));
            }
            else{
                scanf("%d %d %d", &from, &to, &w);
                update(1,1,n,from,to,w);
            }
        }
    }
	return 0;
}
