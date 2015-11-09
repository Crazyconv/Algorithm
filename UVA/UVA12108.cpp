#define LOCAL

#include <stdio.h>
#include <string.h>

void printpatttern(int pattern[][11], int length[], int snum){
	for(int i = 0; i < snum; i++){
		for(int j = 0; j < length[i]; j++){
			printf("%d ", pattern[i][j]);
		}
		printf("\n");
	}
}

int GCD(int a, int b){
	int temp;
	while(a!=b && a!=1 && b!=1){
		if(a < b){
			temp = a; a = b; b = temp;
		}
		a = a - b;
	}
	if(a == 1 || b == 1)
		return 1;
	else
		return a;
}



int LCM(int arr[], int len){
	int lcm = arr[0];
	for(int i = 1; i < len; i++){
		lcm = lcm / GCD(lcm, arr[i]) * arr[i];
	}
	return lcm;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int snum;
	int casenum = 1;
	while((scanf("%d", &snum)) > 0 && snum > 0){
		int pattern[snum][11], length[snum];
		for (int i = 0; i < snum; i++){
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			length[i] = a + b;
			for(int j = 0; j < length[i]; j++){
				// sleep = 0, awaken = 1;
				if((j-1+c)%(length[i]) < a)
					pattern[i][j] = 1;
				else
					pattern[i][j] = 0;
			}
		}
		// printpatttern(pattern, length, snum);

		int impossible = 1;
		int awakenpoint = 0;
		int i;
		for(i = 0; i < LCM(length, snum); i++){
			int awakennum = 0;
			for(int j = 0; j < snum; j ++){
				if(pattern[j][i%length[j]]){
					awakennum ++;
				}
			}
			if(awakennum >= (snum+1)/2){
				impossible = 0;
				awakennum = 0;
				int status[snum];
				for(int j = 0; j < snum; j++){
					status[j] = 0;
				}
				while(i < LCM(length, snum) && awakennum < snum){
					for(int j = 0; j < snum; j++){
						if(status[j] == 0 && pattern[j][i%length[j]]){
							status[j] = 1;
							awakennum ++;
						}
					}
					i++;
				}
				break;
			}
		}
		printf("Case %d: ", casenum);
		if(impossible){
			printf("-1\n");
		} else {
			printf("%d\n", i);
		}
		casenum ++;
	}
	return 0;
}
