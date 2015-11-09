#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int d;
	int num = 1;
	string temp;
	char va[3];
	while(scanf("%d", &d) && d){
		getline(cin, temp);
		int v[d];
		string leaves;
		int cases;
		for(int i = 0; i < d; i++){
			scanf("%s", va);
			v[i] = va[1] - '0';
		}
		getline(cin, temp);
		getline(cin, leaves);
		scanf("%d", &cases);
		getline(cin, temp);
		printf("S-Tree #%d:\n", num);
		while(cases--){
			string inputs;
			int index = 0;
			getline(cin, inputs);
			for(int i = 0; i < d; i++){
				if(inputs[v[i] - 1] == '1'){
					index = index + (1 << (d - 1 - i));
				}
			}
			printf("%c", leaves[index]);
		}
		printf("\n\n");
		num ++;
	}
	return 0;
}