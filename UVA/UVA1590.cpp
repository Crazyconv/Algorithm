// #define LOCAL

#include <stdio.h>
#include <string.h>
int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int num;
	while(scanf("%d", &num) > 0){
		int ips[num][4];
		int net[4] = {0}, mask[4] = {0};
		for(int i = 0; i < num; i ++){
			scanf("%d.%d.%d.%d", &ips[i][0], &ips[i][1], &ips[i][2], &ips[i][3]);
		}

		for(int i = 0; i < 4; i++){
			//check whether all same, if yes, net[i] = , mask[i] = 255
			//else ... break;
			//...: for 1 - 7, check each the same or not,  if yes, ner[i] += ,  if no, break; 

			//check whether all the same
			int same = 1;
			for(int j = 0; j < num-1; j++){
				if(ips[j][i] != ips[j+1][i]){
					same = 0;
					break;
				}
			}
			if(same){
				net[i] = ips[0][i];
				mask[i] = 255;
			} else {
				for(int m = 7; m >= 0; m--){
					same = 1;
					for(int j = 0; j < num-1; j++){
						if((ips[j][i] >> m) != (ips[j+1][i] >> m)){
							same = 0;
							break;
						}
					}
					if(same){
						mask[i] += (1 << m);
					} else {
						break;
					}
				}
				net[i] = mask[i] & ips[0][i];
				break;
			}
		}
		printf("%d.%d.%d.%d\n", net[0], net[1], net[2], net[3]);
		printf("%d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
	}
	return 0;
}
