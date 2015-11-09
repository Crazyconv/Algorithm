#include <stdio.h>
int count[10][10000];
int main(){
	for(int i = 1; i < 10000; i++){
		int last = i;
		int y;
		if(i > 1){
			for(int j = 0; j < 10; j++){
				count[j][i-1] = count[j][i-2];
			}
		}
		while(last > 0){
			y = last % 10;
			last /= 10;
			count[y][i-1] ++;
		}
	}
	int T;
	scanf("%d", &T);
	while(T--){
		int num;
		scanf("%d", &num);
		for(int i = 0; i < 10; i++){
			if(i!=0){
				printf(" ");
			}
			printf("%d", count[i][num-1]);
		}
		printf("\n");
	}
	return 0;
}