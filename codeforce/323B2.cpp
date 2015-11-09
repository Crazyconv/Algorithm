

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

const int maxn = 1000+10;

int main(){
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	int turn = -1;
	int info = 0;
	while(info < n){
		turn ++;
		for(int i = 0; i < n; i++){
			if(a[i] <= info){
				a[i] = maxn;
				info++;
			}
		}
		if(info < n){
			turn ++;
			for(int i = n-1; i >=0; i--){
				if(a[i] <= info){
					a[i] = maxn;
					info++;
				}
			}
		}
	}
	printf("%d\n", turn);
	return 0;
}