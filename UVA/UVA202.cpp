#include <stdio.h>
#define LOCAL

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int x, y, tag = 0;
	int result[100000], mod[100000];
	while(scanf("%d %d", &x, &y) == 2){
		if(tag){
			printf("\n");
		} else {
			tag = 1;
		}

		int current = 0, start = 0, stop = 0;
		printf("%d/%d = %d.", x, y, x/y);
		x = x%y;
		while(1){
			result[current] = x * 10 / y;
			mod[current] = (x * 10) % y;
			for (start = 0; start < current; start++){
				if(result[current] == result[start] && mod[current] == mod[start]){
					stop = 1;
					break;
				}
			}
			if(stop){
				break;
			}
			x = mod[current];
			current ++;
		}
		for(int i = 0; i < current; i++){
			if(i == start){
				printf("(");
			}
			printf("%d", result[i]);
			if(i >= 49){
				printf("...");
				break;
			}
		}
		printf(")\n");
		printf("   %d = number of digits in repeating cycle\n", current - start);
	}
	printf("\n");
}