#define LOCAL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char readchar(){
	while(1){
		char ch = getchar();
		if(isalnum(ch))
			return ch;
	}
}
int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif


	int disknum, blocksize, blocknum;
	int parity;
	int casenum = 1;
	while(scanf("%d %d %d", &disknum, &blocksize, &blocknum) > 1){
		char diskdata[disknum][blocksize * blocknum + 1];

		parity = (readchar() == 'E')? 0 : 1;
		for(int i = 0; i < disknum; i ++){
			scanf("%s", diskdata[i]);
		}

		// check valid
		int valid = 1;
		for(int i = 0; i < blocknum * blocksize; i++){
			int xnum = 0, invalidindex, invalidbit = parity;
			for(int j = 0; j < disknum; j++){
				if(diskdata[j][i] == 'x' || diskdata[j][i] == 'X'){
					invalidindex = j;
					xnum ++;
					if(xnum > 1){
						break;
					}
				} else {
					invalidbit = invalidbit ^ (diskdata[j][i] - '0');
				}
			}
			if(xnum > 1){
				valid = 0;
				break;
			} else if (xnum == 1){
				diskdata[invalidindex][i] = invalidbit + '0';
			} else if (invalidbit == 1){
				valid = 0;
				break;
			}
		}

		if(valid){
			printf("Disk set %d is valid, contents are: ", casenum);
			int index = 0, asc = 0;
			for(int i = 0; i < blocknum; i++){
				for(int j = 0; j < disknum; j++){
					if(i % disknum != j){
						for(int k = 0; k < blocksize; k++){
							asc = (asc << 1) + (diskdata[j][i*blocksize+k] - '0');
							index ++;
							if(index == 4){
								printf("%X", asc);
								index = 0;
								asc = 0;
							}
						}
					}
				}
			}
			if(index != 0){
				printf("%X", asc << (4-index));
			}
			printf("\n");
		} else {
			printf("Disk set %d is invalid.\n", casenum);
		}
		casenum++;
	}
	return 0;
}
