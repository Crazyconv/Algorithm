#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int n_card;
	while(scanf("%d", &n_card) && n_card){
		queue<int> q_card;
		for(int i = 1; i <= n_card; i++){
			q_card.push(i);
		}

		printf("Discarded cards:");
		int num = q_card.front();
		q_card.pop();
		int first = 1;
		while(!q_card.empty()){
			if(first)
				first = 0;
			else
				printf(",");
			printf(" %d", num);
			num = q_card.front();
			q_card.pop();
			q_card.push(num);
			num = q_card.front();
			q_card.pop();
		}
		printf("\n");
		
		printf("Remaining card: %d\n", num);
	}


	return 0;
}