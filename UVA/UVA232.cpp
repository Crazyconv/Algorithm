#include <stdio.h>
//#define LOCAL

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int x, y, num = 1;
	while(1){
		scanf("%d", &x);
		if(x == 0)
			break;
		scanf("%d", &y);

		char crossword[x][y];
		int status[x][y];
		

		int location = 0;
		for(int i = 0; i < x; i++){
			getchar();
			for(int j = 0; j < y; j++){
				crossword[i][j] = getchar();
				if(crossword[i][j] != '*' && (i == 0 || j == 0 ||
					(i - 1 >= 0 && crossword[i-1][j] == '*') ||
					(j - 1 >= 0 && crossword[i][j-1] == '*'))){
					status[i][j] = ++location;
				}
			}
		}

		if(num != 1){
			printf("\n");
		}

		printf("puzzle #%d:\n", num);
		printf("Across");
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				if(crossword[i][j] != '*'){
					if(j == 0 || 
						(j-1 >= 0 && crossword[i][j-1] == '*')){
						printf("\n%3d.", status[i][j]);
						int m = j;
						while(m < y && crossword[i][m] != '*'){
							printf("%c", crossword[i][m]);
							m++;
						}
					}
				}
			}
		}

		printf("\nDown");
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				if(crossword[i][j] != '*'){
					if(i == 0 || 
						(i-1 >= 0 && crossword[i-1][j] == '*')){
						printf("\n%3d.", status[i][j]);
						int m = i;
						while(m < x && crossword[m][j] != '*'){
							printf("%c", crossword[m][j]);
							m++;
						}
					}
				}
			}
		}

		printf("\n");
		num ++;
	}
	return 0;
}