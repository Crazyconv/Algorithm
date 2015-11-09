#include <stdio.h>
#include <string.h>
// #define LOCAL

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	char s[1000000], t[1000000];
	while(scanf("%s %s", s, t) > 0){
		int n_s = 0, n_t = 0, found = 0;
		for(; n_s < strlen(s); n_s++){
			found = 0;
			while(n_t < strlen(t)){
				if(t[n_t] == s[n_s]){
					found = 1;
					n_t ++;
					break;
				}
				n_t ++;
			}
			if(!found)
				break;
		}
		if(found){
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}