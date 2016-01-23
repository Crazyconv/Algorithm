// http://www.hawstein.com/posts/binary-indexed-trees.html
// http://blog.csdn.net/u013548531/article/details/40381729
#include <cstdio>
#include <string>
using namespace std;

const int maxn = 50005;
int num[maxn];
int tree[maxn];
int N;

void initialize(){
    memset(num, 0, sizeof(num));
    memset(tree, 0, sizeof(tree));
}

int low_bit(int index){
    return index & (-index);
}

int sum(int index){
    int ans = 0;
    while(index > 0){
        ans += tree[index];
        index -= low_bit(index);
    }
    return ans;
}

void update(int index, int value){
    while(index <= N){
        tree[index] += value;
        index += low_bit(index);
    }
}

// if we do not store the original array
void single(int index){
    int sum = tree[index];
    if(index > 0){
        int z = index - low_bit(index);
        index --;
        whlie(index > z){
            sum -= tree[index];
            index -= low_bit(index);
        }
    }
    return sum;
}

int main(){
    int T, a, b;
    char op[10];

    scanf("%d", &T);
    for(int t = 1; t <= T; t++){
        initialize();
        scanf("%d", &N);
        for(int i = 1; i <= N; i++){
            scanf("%d", &num[i]);
            update(i, num[i]);
        }
        printf("Case %d:\n", t);
        bool end = false;
        while(!end && scanf("%s", op) != EOF){
            switch(op[0]){
                case 'Q':
                    scanf("%d%d", &a, &b);
                    printf("%d\n", sum(b)-sum(a-1));
                    break;
                case 'A':
                    scanf("%d%d", &a, &b);
                    update(a, b);
                    break;
                case 'S':
                    scanf("%d%d", &a, &b);
                    update(a, -b);
                    break;
                case 'E':
                    end = true;
                    break;
            }
        }
    }

    return 0;
}