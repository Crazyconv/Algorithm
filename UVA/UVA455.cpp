#include <stdio.h>
#include <string.h>
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		char s[80];
		scanf("%d");
		scanf("%s", s);
		int fail = 1;
		for(int i = 1; i < strlen(s); i++){
			if(s[i] == s[0]){
				if(strlen(s) % i == 0){
					fail = 0;
					for(int j = 1; j < strlen(s)/i; j++){
						for(int k = 0; k < i; k++){
							if(s[j*i + k] != s[k]){
								fail = 1;
								break;
							}
						}
						if(fail)
							break;
					}
					if(!fail){
						printf("%d\n", i);
						break;
					}
				}
			}
		}
		if(fail)
			printf("%d\n", int(strlen(s)));
		if(T!=0)
			printf("\n");
	}
	return 0;
}