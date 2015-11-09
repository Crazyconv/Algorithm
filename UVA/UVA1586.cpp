#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
	int T;
	char s[80];
	scanf("%d",&T);

	while(T--){
		memset(s, 0 ,sizeof(s));
		double factor = 0, mass = 0;
		int num = 0, base = 1;
		scanf("%s", s);
		for(int i = 0; i < sizeof(s); i++){
			if(isalpha(s[i])){
				if(num == 0)
					num = 1;
				mass += factor * num;

				num = 0;
				base = 1;
				switch(s[i]){
					case 'c':
					case 'C':
						factor = 12.01;
						break;
					case 'H':
					case 'h':
						factor = 1.008;
						break;
					case 'O':
					case 'o':
						factor = 16.00;
						break;
					case 'N':
					case 'n':
						factor = 14.01;
						break;
				}
			} else if(isdigit(s[i])){
				num = (s[i] - '0') + num * base;
				base *= 10;
			}

		}
		if(num == 0)
			num = 1;
		mass += factor * num;
		printf("%.3lf\n", mass);
	}
	return 0;
}