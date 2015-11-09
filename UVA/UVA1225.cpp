#include <stdio.h>
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int count[10] = {0};
		int num;
		scanf("%d", &num);
		for(int i = 1; i <= num; i++){
			int x = i;
			int y = 0;
			while(x != 0){
				y = x % 10;
				x /= 10;
				count[y] ++;
			}
		}
		for(int i = 0; i < 10; i++){
			if(i!=0){
				printf(" ");
			}
			printf("%d", count[i]);
		}
		printf("\n");
	}
	return 0;
}