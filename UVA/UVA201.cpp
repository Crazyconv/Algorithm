// #define LOCAL
// #define TESTING

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int squarenum[9];

char gotchar(){
	while(1){
		char ch = getchar();
		if(isalpha(ch))
			return ch;
	}
}

int min(int x, int y){
	if(x > y)
		return y;
	else
		return x;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int n, m, problemnum = 1;;
	while(scanf("%d%d", &n, &m) == 2){
		int link_h[n+1][n], link_v[n][n+1];
		memset(link_h, 0, sizeof(link_h));
		memset(link_v, 0, sizeof(link_v));
		memset(squarenum, 0, sizeof(squarenum));

		for(int i = 0; i < m; i++){
			char type;
			int x, y;
			type = gotchar();
			scanf("%d %d", &x, &y);

			if(type == 'H'){
				link_h[x][y] = 1;
			} else {
				link_v[y][x] = 1;
			}
		}

#ifdef TESTING
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n-1; j++){
				if(link_h[i][j]){
					printf("- ");
				} else {
					printf("^ ");
				}
			}
			printf("\n");
		}

		for(int i = 1; i <= n-1; i++){
			for(int j = 1; j <= n; j++){
				if(link_v[i][j]){
					printf("| ");
				} else {
					printf("^ ");
				}
			}
			printf("\n");
		}
#endif

		// for each point, check available size
		for(int x = 1; x < n; x++){
			for(int y = 1; y < n; y++){
				int maxsize = min(n-x, n-y);
				for(int size = 1; size <= maxsize; size++){
					if(link_h[x][y+size-1] == 1 && link_v[x+size-1][y] == 1){
						int square = 1;
						for(int innersize = 1; innersize <= size; innersize++){
							if(link_h[x+size][y+innersize-1] != 1){
								square = 0;
								break;
							}
						}
						if(square){
							for(int innersize = 1; innersize <= size; innersize++){
								if(link_v[x+innersize-1][y+size] != 1){
									square = 0;
									break;
								}
							}
						}
						if(square){
							squarenum[size] ++;
						}
					} else {
						break;
					}
				}
			}
		}

		int square_found = 0;
		if(problemnum != 1){
			printf("\n**********************************\n\n");
		}
		printf("Problem #%d\n\n", problemnum);
		for(int i = 1; i < n; i++){
			if(squarenum[i] > 0){
				printf("%d square (s) of size %d\n", squarenum[i], i);
				square_found = 1;
			}
		}
		if(square_found == 0){
			printf("No completed squares can be found.\n");
		}
		problemnum ++;
	}



	return 0;
}
