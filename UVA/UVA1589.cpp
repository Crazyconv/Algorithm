// #define LOCAL
// #define TESTING
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int N;
char red[7];
int valid[7];
int location[7][2];
int b_x, b_y, c_x, c_y;
int r_x, r_y;
int move[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int leg[8][2] = {-1, 0, -1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, -1, 0, -1};
int horse[8][2] = {-2, -1, -2, 1, -1, 2, 1, 2, 2, 1, 2, -1, 1, -2, -1, -2};
int occupy[11][10];

void test(){
	printf("occupy:\n");
	for(int i = 1; i <=10; i++){
		for(int j = 1; j <= 9; j++){
			printf("%d ", occupy[i][j]);
		}
		printf("\n");
	}
	printf("valid:\n");
	for(int i = 0; i < N; i++){
		printf("%d ", valid[i]);
	}
	printf("\nred:\n");
	for(int i = 0; i < N; i++){
		printf("%c ", red[i]);
	}
}

int fly(){
	if(r_y == b_y){
		if(r_x > b_x){
			for(int i = b_x+1; i < r_x; i++){
				if(occupy[i][r_y] == 1)
					return 0;
			}
		} else {
			for(int i = r_x+1; i < b_x; i ++){
				if(occupy[i][r_y] == 1)
					return 0;
			}
		}
		return 1;
	}
	return 0;
}

int checkGeneral(int index){
	if(valid[index] && location[index][1] == c_y){
		int diff, start = c_x + 1;
		diff = location[index][0] - c_x;
		if(diff < 0){
			start = location[index][0] + 1;
			diff = 0 - diff;
		}
		for(int i = 0; i < diff - 1; i++){
			if(occupy[start + i][c_y] == 1){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int checkChariot(int index){
	if(valid[index] && location[index][1] == c_y){
		int diff, start = c_x + 1;
		diff = location[index][0] - c_x;
		if(diff < 0){
			start = location[index][0] + 1;
			diff = 0 - diff;
		}
		for(int i = 0; i < diff - 1; i++){
			if(occupy[start + i][c_y] == 1){
				return 0;
			}
		}
		return 1;
	} else if(valid[index] && location[index][0] == c_x){
		int diff, start = c_y + 1;
		diff = location[index][1] - c_y;
		if(diff < 0){
			start = location[index][1] + 1;
			diff = 0 - diff;
		}
		for(int i = 0; i < diff - 1; i++){
			if(occupy[c_x][start + i] == 1){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int checkCannon(int index){
	int num = 0;
	if(valid[index] && location[index][1] == c_y){
		int diff, start = c_x + 1;
		diff = location[index][0] - c_x;
		if(diff < 0){
			start = location[index][0] + 1;
			diff = 0 - diff;
		}
		for(int i = 0; i < diff - 1; i++){
			if(occupy[start + i][c_y] == 1){
				num++;
				if(num > 1)
					return 0;
			}
		}
		if(num == 1)
			return 1;
		else
			return 0;
	} else if(valid[index] && location[index][0] == c_x){
		int diff, start = c_y + 1;
		diff = location[index][1] - c_y;
		if(diff < 0){
			start = location[index][1] + 1;
			diff = 0 - diff;
		}
		for(int i = 0; i < diff - 1; i++){
			if(occupy[c_x][start + i] == 1){
				num++;
				if(num > 1)
					return 0;
			}
		}
		if(num == 1)
			return 1;
		else
			return 0;
	}
	return 0;
}
int checkHorse(int index){
	if(valid[index]){
		for(int i = 0; i < 8; i++){
			if(occupy[location[index][0] + leg[i][0]][location[index][1] + leg[i][1]] != 1){
				if(location[index][0] + horse[i][0] == c_x && location[index][1] + horse[i][1] == c_y){
					return 1;
				}
			}
		}
	}
	return 0;
}

char gotchar(){
	while(1){
		char ch;
		scanf("%c", &ch);
		if(isalpha(ch))
			return ch;
	}
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	while(scanf("%d %d %d", &N, &b_x, &b_y) == 3 && N!=0){
		memset(red, 0, sizeof(red));
		memset(location, 0 , sizeof(location));
		memset(valid, 0, sizeof(valid));
		memset(occupy, 0, sizeof(occupy));

		for(int i = 0; i < N; i++){
			red[i] = gotchar();
			valid[i] = 1;
			scanf("%d %d", &location[i][0], &location[i][1]); 
			occupy[location[i][0]][location[i][1]] = 1;

			if(red[i] == 'G'){
				r_x = location[i][0];
				r_y = location[i][1];
			}
		}


		if(fly()){
			printf("NO\n");
		} else{
			int checkmate = 1;
			for(int m = 0; m < 4; m++){

				int check = 0;
				int invalid = -1;
				c_x = b_x + move[m][0];
				c_y = b_y + move[m][1];
				//  || (c_x >= 8 && c_x <= 10)
// #ifdef TESTING
// 				printf("x y: %d %d\n", c_x, c_y);
// #endif
				if(((c_x >= 1 && c_x <= 3) || (c_x >= 8 && c_x <= 10)) && c_y >= 4 && c_y <= 6){
					occupy[c_x][c_y] = 1;
					for(int i = 0; i < N; i++){
						if(location[i][0] == c_x && location[i][1] == c_y){
							valid[i] = 0;
							invalid = i;
							break;
						}
					}
					for(int i = 0; i < N; i++){
						switch(red[i]){
							case 'G':
								if(checkGeneral(i)){
									check = 1;
								}
								break;
							case 'H':
								if(checkHorse(i)){
									check = 1;					
								}
								break;
							case 'C':
								if(checkCannon(i)){
									check = 1;
								}
								break;
							case 'R':
								if(checkChariot(i)){
									check = 1;	
								}
								break;
							default:
								;
						}
					}

					if(!check){
						checkmate = 0;
						break;
					}
					// restore some variable
					if(invalid != -1){
						valid[invalid] = 1;
					} else {
						occupy[c_x][c_y] = 0;
					}
				}


			}
			
			if(checkmate){
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}

	}
	return 0;
}