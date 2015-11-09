#include <stdio.h>
#include <ctype.h>
#define LOCAL
int main(){
// #ifdef LOCAL
// 	freopen("input.in", "r", stdin);
// 	freopen("output2.out", "w", stdout);
// #endif

	char puzzle[5][5];
	char c;
	int index = 0, space_i = 0, space_j = 0, config = 1;
	int num = 1;
	while((c = getchar()) != EOF && c != 'Z'){
		puzzle[index/5][index%5] = c;
		if(c == ' '){
			space_i = index/5;
			space_j = index%5;
		}
		if(index == 4 || index == 9 || index == 14 || index == 19 || index == 24)
			getchar();
		if(index != 24){
			index ++;
		}else{
			config = 1;
			while((c = getchar()) != EOF && c != '0'){
				if(config && (isalpha(c) || isdigit(c))){
					switch(c){
						case 'A': 
							if(space_i-1<0)
								config = 0;
							else{
								puzzle[space_i][space_j] = puzzle[space_i-1][space_j];
								puzzle[space_i-1][space_j] = ' ';
								space_i --;
								config = 1;
							}
							break;
						case 'B':
							if(space_i+1 >= 5)
								config = 0;
							else{
								puzzle[space_i][space_j] = puzzle[space_i+1][space_j];
								puzzle[space_i+1][space_j] = ' ';
								space_i ++;
								config = 1;
							}
							break;
						case 'L':
							if(space_j-1<0)
								config = 0;
							else{
								puzzle[space_i][space_j] = puzzle[space_i][space_j-1];
								puzzle[space_i][space_j-1] = ' ';
								space_j --;
								config = 1;
							}
							break;
						case 'R':
							if(space_j+1 >= 5)
								config = 0;
							else{
								puzzle[space_i][space_j] = puzzle[space_i][space_j+1];
								puzzle[space_i][space_j+1] = ' ';
								space_j ++;
								config = 1;
							}
							break;
						default:
							config = 0;
					}
				}
			}
			if(num != 1){
				printf("\n");
			}
			printf("Puzzle #%d:\n", num);
			if(config){
				for(int i = 0; i < 5; i++){
					for(int j = 0; j < 5; j++){
						if(j)
							printf(" ");
						printf("%c", puzzle[i][j]);
					}
					printf("\n");
				}
			} else {
				printf("This puzzle has no final configuration.\n");
			}
			index = 0;
			num++;
			getchar();
		}
	}
}