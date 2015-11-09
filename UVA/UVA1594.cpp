#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <set>

using namespace std;

string its(int arr[], int length){
	stringstream ss;
	for(int i = 0; i < length; i++){
		ss << arr[i] << "_";
	}
	return ss.str();
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while(T--){
		int length;
		scanf("%d", &length);

		int num[length], new_num[length];
		set<string> sequence;
		string item;
		bool zero = true;

		for(int i = 0; i < length; i ++){
			scanf("%d", num + i);
			if(num[i] != 0)
				zero = false;
		}
		if(zero){
			printf("ZERO\n");
			continue;
		}
		
		sequence.insert(its(num, length));

		for(int step = 1; step <= 1000; step++){
			zero = true;
			for(int i = 0; i < length; i ++){
				new_num[i] = abs(num[i] - num[(i+1)%length]);
				if(new_num[i] != 0)
					zero = false;
			}
			for(int i = 0; i < length; i ++){
				num[i] = new_num[i];
			}
			if(zero)
				break;
			item = its(new_num, length);
			if(sequence.count(item)){
				break;
			}
			sequence.insert(item);
		}

		if(zero)
			printf("ZERO\n");
		else
			printf("LOOP\n");

	}
	return 0;
}