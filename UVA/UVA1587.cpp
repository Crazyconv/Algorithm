#include <stdio.h>
#include <string.h>
// #define LOCAL

void init(int *arr, int size, int value){
	for(int i = 0; i < size; i++){
		arr[i] = value;
	}
}

int check(int *arr, int size){
	for(int i = 0; i < size - 1; i++){
		if(arr[i] == arr[i+1]){
			return 0;
		}
	}
	return 1;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output2.out", "w", stdout);
#endif

	while(1){
		int all[12];
		int length[3] = {0};
		int num[3] = {0};
		int location[3][12] = {0};
		int fit, impossible = 1;

		for(int i = 0; i < 12; i++){
			if(scanf("%d", &(all[i])) != 1){
				return 0;
			}
		}
		//process
		for(int i = 0; i < 12; i++){
			fit = 0;
			for(int j = 0; j < 3; j++){
				if(all[i] == length[j]){
					location[j][num[j]] = i/2;
					num[j] ++;
					fit = 1;
					break;
				} else if(length[j] == 0){
					length[j] = all[i];
					location[j][num[j]] = i/2;
					num[j] ++;
					fit = 1;
					break;
				}
			}
			if(!fit){
				break;
			}
		}
		if(fit){
			if(num[0] == 12){
				impossible = 0;
			} else if (num[0] == 4 && num[1] == 4 && num[2] == 4){
				if(check(location[0],4) && check(location[1], 4) && check(location[2], 4)){
					impossible = 0;
				}
			} else if (num[0] == 4 && num[1] == 8){
				if(check(location[0], 4)){
					impossible = 0;
				}
			} else if (num[0] == 8 && num[1] == 4){
				if(check(location[1], 4)){
					impossible = 0;
				}
			}
		}

		if(impossible){
			printf("IMPOSSIBLE\n");
		} else {
			printf("POSSIBLE\n");
		}
	}

	return 0;
}