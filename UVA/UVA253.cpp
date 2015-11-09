// #define LOCAL

#include <stdio.h>
#include <string.h>

void swap(char *line, int x, int y){
	char temp = *(line+x);
	*(line+x) = *(line+y);
	*(line+y) = temp;
}

int allidentical(char *line1, char *line2){
	for(int i = 0; i < 6; i++){
		if(*(line1 + i) != *(line2 + i)){
			return 0;
		}
	}
	return 1;
}

int identical(char *line1, char *line2){
	int id = allidentical(line1, line2);
	if(id == 0){
		swap(line1, 0, 5);
		swap(line1, 1, 4);
		id = allidentical(line1, line2);
	}
	return id;
}


int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int convert[12][6] = {
		{1,2,3,4,5,6},
		{1,3,5,2,4,6},
		{1,5,4,3,2,6},
		{1,4,2,5,3,6},
		{5,1,3,4,6,2},
		{5,3,6,1,4,2},
		{5,6,4,3,1,2},
		{5,4,1,6,3,2},
		{3,2,6,1,5,4},
		{3,1,2,5,6,4},
		{3,5,1,6,2,4},
		{3,6,5,2,1,4}
	};

	char line[15];
	while(scanf("%s", line)>0){
		char temp[6];
		int id = 0;
		for(int i = 0; i < 12; i++){
			for(int j = 0; j < 6; j++){
				temp[j] = line[convert[i][j]-1];
			}
			if(identical(temp, line+6)){
				printf("TRUE\n");
				id = 1;
				break;
			}
		}
		if(!id){
			printf("FALSE\n");
		}
	}
	return 0;
}
