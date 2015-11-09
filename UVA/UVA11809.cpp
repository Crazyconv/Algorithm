#include <stdio.h>
#include <string.h>
#include <math.h>
#define ep 1e-6
#define log102 log10(2)
// #define LOCAL

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	double A[30][10] = {0}, B[30][10] = {0};
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 10; j++){
			long double part = 1 - pow(2, -j-1);
			long inte = pow(2, i+1) - 1;

			// calculate A and B
			double b_log = log10(part) + log102 * inte;
			B[i][j] = floor(b_log);
			A[i][j] = pow(10, b_log - B[i][j]);
		}
	}

	// for(int i = 0; i < 30; i++){
	// 	for(int j = 0; j < 10; j++){
	// 		printf("%lf ", B[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// printf("\n");

	// for(int i = 0; i < 30; i++){
	// 	for(int j = 0; j < 10; j++){
	// 		printf("%lf ", A[i][j]);
	// 	}
	// 	printf("\n");
	// }


	char num[1000];
	while(scanf("%s", num) && strcmp(num, "0e0")){
		for(int i = 0; i < strlen(num); i++){
			if(num[i] == 'e'){
				num[i] = ' '; 
				break;
			}
		}

		double a, b;
		sscanf(num, "%lf %lf", &a, &b);

		int found = 0, i, j;
		for(i = 0; i < 30; i++){
			for(j = 0; j < 10; j++){
				if(fabs(B[i][j] - b) < ep && fabs(A[i][j] - a) < ep){
					printf("%d %d\n", j, i+1);
					found = 1;
					break;
				}
			}
			if(found)
				break;
		}
		
	}
	return 0;
}