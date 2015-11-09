#define LOCAL

#include <stdio.h>
#include <string.h>
int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	long long recordnum, sizeP, sizeQ;
	while(scanf("%lld %lld %lld", &recordnum, &sizeP, &sizeQ) == 3){
		long long ansA = 0, ansB = 0;
		long long smallest = 1LL << 60;
		for(int A = 0; A <= 33; A++){
			for(int B = 0; B <= 100; B++){
				if(((sizeP + (sizeP << A)) >> B) >= sizeQ){
					long long pos = (recordnum - 1) * sizeP;
					long long temp = ((pos + (pos << A)) >> B);
					if(temp < smallest){
						ansA = A;
						ansB = B;
						smallest = temp;
					}
				}
			}
		}
		smallest += sizeQ;
		printf("%lld %lld %lld\n", smallest, ansA, ansB);
	}
	return 0;
}
