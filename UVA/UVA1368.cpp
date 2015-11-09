#include <stdio.h>
// #define LOCAL

int main(){
#ifdef LOCAL
	freopen("input2.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	char vol[4] = {'A', 'C', 'G', 'T'};
	int T;
	scanf("%d", &T);
	while(T--){
		int x, y;
		scanf("%d %d", &x, &y);
		getchar();

		char seq[x][y];
		int num[4][y];
		int distance = 0;

		for(int i = 0; i < 4; i++){
			for (int j = 0; j < y; j++){
				num[i][j] = 0;
			}
		}
		for(int i = 0; i < x; i ++){
			for (int j = 0; j < y; j++){
				seq[i][j] = getchar();
				switch(seq[i][j]){
					case 'A':
						num[0][j] ++;
						break;
					case 'C':
						num[1][j] ++;
						break;
					case 'G':
						num[2][j] ++;
						break;
					case 'T':
						num[3][j] ++;
						break;
				}
			}
			getchar();
		}
		// for(int i = 0; i < 4; i++){
		// 	printf("%c: ", vol[i]);
		// 	for (int j = 0; j < y; j++){
		// 		printf("%d ", num[i][j]);
		// 	}
		// 	printf("\n");
		// }
		for(int j = 0; j < y; j++){
			int index = 0;
			for(int i = 1; i < 4; i++){
				if(num[i][j] > num[index][j]){
					index = i;
				}
			}
			for(int m = 0; m < x; m++){
				if(seq[m][j] != vol[index])
					distance ++;
			}
			printf("%c", vol[index]);
		}
		printf("\n%d\n", distance);
	}
}