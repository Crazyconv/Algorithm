//区间最大值
#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l , m , rt << 1    
#define rson m + 1 , r , rt << 1 | 1   
#define root 1 , N , 1    
const int maxn = 1000+10;    
bool reduce[maxn<<2];    
int MIN[maxn<<2];    
void PushUp(int rt) {    
    MIN[rt] = min(MIN[rt<<1], MIN[rt<<1|1]);    
}    
void PushDown(int rt,int m) {    
    if (reduce[rt]) {    
        reduce[rt<<1] = true;
        reduce[rt<<1|1] = true;  
        MIN[rt<<1] --;   
        MIN[rt<<1|1] --;   
        reduce[rt] = false;    
    }    
}    
void build(int l,int r,int rt) {    
    reduce[rt] = false;    
    if (l == r) {    
        scanf("%lld",&MIN[rt]);    
        return ;    
    }    
    int m = (l + r) >> 1;    
    build(lson);    
    build(rson);    
    PushUp(rt);    
}    
void update(int L,int R,int c,int l,int r,int rt) {    
    if (L <= l && r <= R) {    
        add[rt] += c;    
        MIN[rt] += (LL)c * (r - l + 1);    
        return ;    
    }    
    PushDown(rt , r - l + 1);    
    int m = (l + r) >> 1;    
    if (L <= m) update(L , R , c , lson);    
    if (m < R) update(L , R , c , rson);    
    PushUp(rt);    
}    
LL query(int L,int R,int l,int r,int rt) {    
    if (L <= l && r <= R) {    
        return MIN[rt];    
    }    
    PushDown(rt , r - l + 1);    
    int m = (l + r) >> 1;    
    LL ret = 0;    
    if (L <= m) ret += query(L , R , lson);    
    if (m < R) ret += query(L , R , rson);    
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
