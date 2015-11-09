#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 1000+10;
int MIN[maxn<<2];

void PushUP(int rt) {
    MIN[rt] = min(MIN[rt<<1], MIN[rt<<1|1]);
}

void build(int l,int r,int rt) {
    if (l == r) {
        scanf("%d",&MIN[rt]);
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUP(rt);
}

void update(int p,int sc,int l,int r,int rt) {
    if (l == r) {
        MIN[rt] = sc;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p , sc , lson);
    else update(p , sc , rson);
    PushUP(rt);
}

int queryL(int L,int R,int l,int r,int rt, int value) {
    if (L <= l && r <= R) {
        if(MIN[rt] > value) return -1;
        if(l == r) return l;
    }
    int m = (l + r) >> 1;
    if(L > m) return queryL(L, R, rson, value);
    if(R <= m) return queryL(L, R, lson, value);
    int left = queryL(L , R , lson, value);
    if(left != -1) return left;
    else return queryL(L , R , rson, value);
}

int queryR(int L,int R,int l,int r,int rt, int value) {
    if (L <= l && r <= R) {
        if(MIN[rt] > value) return -1;
        if(l == r) return r;
    }
    int m = (l + r) >> 1;
    if(L > m) return queryR(L, R, rson, value);
    if(R <= m) return queryR(L, R, lson, value);
    int right = queryR(L , R , rson, value);
    if(right != -1) return right;
    else return queryR(L , R , lson, value);
}


int main(){
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	build(1, n, 1);
	int pos = 0;
	int target = -1;
	int turn = 0;
	char direction = 'R';
	for(int i = 0; i < n; i++){
		if(direction == 'R'){
			// right first then left
			if(pos != n && (target = queryL(pos+1, n, 1, n, 1, i)) != -1){
				pos = target;
			} else {
				pos = target = queryR(1, pos-1, 1, n, 1, i);
				turn ++; 
				direction = 'L';
			}
		} else {
			// left first then right
			if(pos != 1 && (target = queryR(1, pos-1, 1, n, 1, i)) != -1){
				pos = target;
			} else {
				pos = target = queryL(pos+1, n, 1, n, 1, i);
				turn ++;
				direction = 'R';
			}
		}
		update(target, maxn, 1, n, 1);
		target = -1;
	}
	printf("%d\n", turn);
	return 0;
}