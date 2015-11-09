#include <stdio.h>
#include <string.h>
// #define LOCAL

void str_to_int(char *s, int *i, int size){
	for(int k = 0; k < size; k++){
		i[k] = s[k] - '0';
	}
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	
	// read and convert
	char s1[101], s2[101];
	int h1[101], h2[101];
	while(scanf("%s%s", s1, s2) > 0){
		int l1, l2, length = 0;
		if(strlen(s1) < strlen(s2)){
			l1 = strlen(s1);
			l2 = strlen(s2);
			str_to_int(s1, h1, l1);
			str_to_int(s2, h2, l2);
		} else {
			l1 = strlen(s2);
			l2 = strlen(s1);
			str_to_int(s1, h2, l2);
			str_to_int(s2, h1, l1);
		}

		for(int diff = 0; diff <= l2 - l1; diff++){
			int fit = 1;
			for(int i = 0; i < l1; i++){
				if(h1[i] + h2[i+diff] > 3){
					fit = 0;
					break;
				}
			}
			if(fit){
				length = l2;
				break;
			}
		}

		if(!length){
			for(int diff = 1; diff < l1; diff++){
				int fit = 1;
				// case 1:
				for(int i = 0; i < l1 - diff; i++){
					if(h1[diff + i] + h2[i] > 3){
						fit = 0;
						break;
					}
				}
				if(!fit){
					fit = 1;
					for(int i = 0; i < l1 - diff; i++){
						if(h1[i] + h2[l2-l1+diff+i] > 3){
							fit = 0;
							break;
						}
					}
				}
				if(fit){
					length = l2 + diff;
					break;
				}
			}
		}
		if(!length){
			length = l1 + l2;
		}
		printf("%d\n", length);

	}
	// baohe

	// liangbian
	return 0;
}