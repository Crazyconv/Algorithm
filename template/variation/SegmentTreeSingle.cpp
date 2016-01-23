//单点增减 区间和
#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l , m , rt << 1    
#define rson m + 1 , r , rt << 1 | 1   
#define root 1 , N , 1    
const int maxn = 50000+10;       
int sum[maxn<<2];    
void PushUp(int rt) {    
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];    
}      
void build(int l, int r, int rt) {      
    if (l == r) {    
        scanf("%d",&sum[rt]);    
        return ;    
    }    
    int m = (l + r) >> 1;    
    build(lson);    
    build(rson);    
    PushUp(rt);    
}    
void update(int p, int c, int l, int r, int rt) {    
    if (l == r) {       
        sum[rt] += c;    
        return ;    
    }        
    int m = (l + r) >> 1;    
    if (p <= m) update(p, c , lson);    
    else update(p, c , rson);    
    PushUp(rt);    
}    
int query(int L,int R,int l,int r,int rt) {    
    if (L <= l && r <= R) {    
        return sum[rt];    
    }     
    int m = (l + r) >> 1;    
    int ret = 0;    
    if (L <= m) ret += query(L , R , lson);    
    if (m < R) ret += query(L , R , rson);    
    return ret;    
}    

int main() {
    int T, n;
    scanf("%d", &T);
    for(int cas = 1; cas <= T; cas ++) {
        printf("Case %d:\n", cas);
        scanf("%d", &n);
        build(1, n, 1);
        char op[10];
        while (scanf("%s", op)) {
            if(op[0] == 'E') break;
            int a, b;
            scanf("%d%d", &a, &b);
            if (op[0] == 'Q') 
                printf("%d\n",query(a, b, 1, n, 1));
            else if (op[0] == 'S') 
                update(a, -b, 1, n, 1);
            else
                update(a, b, 1, n, 1);
        }
    }
    return 0;
}
