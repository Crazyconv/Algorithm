//区间最值 单点替换
#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l , m , rt << 1    
#define rson m + 1 , r , rt << 1 | 1   
#define root 1 , N , 1    
const int maxn = 200000+10;    
bool reduce[maxn<<2];    
int MAX[maxn<<2];    
void PushUp(int rt) {    
    MAX[rt] = max(MAX[rt<<1], MAX[rt<<1|1]);    
}      
void build(int l, int r, int rt) {        
    if (l == r) {    
        scanf("%d",&MAX[rt]);    
        return ;    
    }    
    int m = (l + r) >> 1;    
    build(lson);    
    build(rson);    
    PushUp(rt);    
}    
void update(int p, int c, int l, int r, int rt) {    
    if (l == r) {      
        MAX[rt] = c;    
        return ;    
    }       
    int m = (l + r) >> 1;    
    if (p <= m) update(p, c, lson);    
    else update(p, c, rson);    
    PushUp(rt);    
}    
int query(int L, int R, int l, int r, int rt) {    
    if (L <= l && r <= R) {    
        return MAX[rt];    
    }      
    int m = (l + r) >> 1;    
    int ret = 0;    
    if (L <= m) ret = max(ret, query(L , R , lson));    
    if (m < R) ret = max(ret, query(L , R , rson));    
    return ret;    
}    

int main() {
    int n , m;
    while (~scanf("%d%d",&n,&m)) {
        build(1 , n , 1);
        while (m --) {
            char op[2];
            int a , b;
            scanf("%s%d%d",op,&a,&b);
            if (op[0] == 'Q') printf("%d\n",query(a , b , 1 , n ,
                1));
                else update(a , b , 1 , n , 1);
        }
    }
    return 0;
}
