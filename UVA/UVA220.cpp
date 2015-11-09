// #define LOCAL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char board[9][9];
char player, enemy, inst;
int move_x, move_y;
int step_x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int step_y[8] = {1, 1, 0, -1, -1, -1, 0, 1};

char gotchar(){
	while(1){
		char ch = getchar();
		if(isalpha(ch) || ch == '-')
			return ch;
	}
}

void turn(){
	char temp = player;
	player = enemy;
	enemy = temp;
}

void count(){
	int black = 0, white = 0;
	for(int i = 1; i < 9; i++){
		for(int j = 1; j < 9; j++){
			if(board[i][j] == 'B')
				black++;
			else if(board[i][j] == 'W')
				white++;
		}
	}
	printf("Black - %2d White - %2d\n", black, white);
}

int checkdirection(int i, int row, int col, int change){
	char target = enemy;
	int c_row = row, c_col = col;
	c_row += step_x[i];
	c_col += step_y[i];
	while(c_row >= 1 && c_row <= 8 && c_col >= 1 && c_col <=8){
		if(target == enemy){
			if(board[c_row][c_col] != target){
				break;
			} else {
				target = player;
			}
		} else if (target == player){
			if(board[c_row][c_col] == player){
				if(change){
					while(row != c_row || col != c_col){
						board[row][col] = player;
						row += step_x[i];
						col += step_y[i];
					}
				}
				return 1;
			} else if(board[c_row][c_col] == '-'){
				break;
			}
		}
		c_row += step_x[i];
		c_col += step_y[i];
	}
	return 0;
}

int check(int row, int col){
	if(board[row][col] == '-'){
		for(int i = 0; i < 8; i++){
			if(checkdirection(i, row, col, 0)){
				return 1;
			}
		}
	}
	return 0;
}

void list(){
	int notfound = 1;
	int first = 1;
	for(int row = 1; row <= 8; row++){
		for(int col = 1; col <= 8; col++){
			if(check(row, col)){
				if(first)
					first = 0;
				else 
					printf(" ");
				printf("(%d,%d)", row, col);
				notfound = 0;
			}
		}
	}
	if(notfound){
		printf("No legal move.");
	}
	printf("\n");
}

void move(){
	if(!check(move_x, move_y)){
		turn();
	}
	for(int i = 0; i < 8; i++){
		checkdirection(i, move_x, move_y, 1);
	}
	count();
	turn();
}

void printboard(){
	for(int i = 1; i < 9; i++){
		for(int j = 1; j < 9; j++){
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int gamenum;
	scanf("%d", &gamenum);
	while(gamenum--){
		int position;
		memset(board, 0, sizeof(board));
		for(int i = 1; i < 9; i++){
			for(int j = 1; j < 9; j++){
				board[i][j] = gotchar();
			}
		}
		// printboard();
		player = gotchar();

		enemy = (player == 'B')? 'W':'B';
		while(1){
			inst = gotchar();
			if(inst == 'L'){
				list();
			} else if (inst == 'M'){
				scanf("%d", &position);
				move_x = position/10;
				move_y = position%10;
				move();
			} else {
				printboard();
				break;
			}
		}
		if(gamenum){
			printf("\n");
		}
	}
	return 0;
}
