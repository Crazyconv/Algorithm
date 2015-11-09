#define LOCAL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char table[36][7];
char context[100][11];
char contextcode[100][61];
char word[81];
int contextcount = 0;
int order[100];

void printtable(){
	for(int i = 0; i < 36; i++){
		if(table[i][0] == '.' || table[i][0] == '-'){
			if(i < 26)
				printf("%c    ", 'A' + i);
			else
				printf("%c    ", i - 26 + '0');
			printf("%s", table[i]);
			printf("\n");
		}
	}
}

void printcontext(){
	for(int i = 0; i < contextcount; i++){
		printf("%s\n", context[i]);
	}
}

void printcontextcode(){
	for(int i = 0; i < contextcount; i++){
		printf("%s\n", contextcode[i]);
	}
}

void printfsortedcontextcode(){
	for(int i = 0; i < contextcount; i++){
		printf("%s - %s\n", contextcode[order[i]], context[order[i]]);
	}
}

char readchar(){
	char ch;
	while(1){
		ch = getchar();
		if(isalpha(ch) || isdigit(ch) || ch == '*'){
			return ch;
		}
	}
}

void sortcontext(){
	for(int i = 0; i < contextcount-1; i++){
		for(int j = i+1; j < contextcount; j++){
			if(strcmp(contextcode[order[i]], contextcode[order[j]]) > 0){
				int temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			} 
			// else if(strcmp(contextcode[order[i]], contextcode[order[j]]) == 0){
			// 	if(strlen(context[order[i]]) > strlen(context[order[j]])){
			// 		int temp = order[i];
			// 		order[i] = order[j];
			// 		order[j] = temp;
			// 	}
			// }
		}
	}
}

int getless(char shorts[], char longs[], int shortlength, int longlength){
	if(shortlength >= longlength)
		return -1;
	int i = 0;
	while(i < shortlength){
		if(shorts[i] != longs[i]){
			return -1;
		}
		i++;
	}
	return longlength - i;
}

int getextra(char longs[], char shorts[], int longlength, int shortlength){
	if(shortlength >= longlength)
		return -1;
	int i = 0;
	while(i < shortlength){
		if(shorts[i] != longs[i]){
			return -1;
		}
		i++;
	}
	return longlength - i;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	memset(table, 0, sizeof(table));
	memset(context, 0, sizeof(context));
	memset(contextcode, 0, sizeof(contextcode));

	// input table
	while(1){
		char character = readchar();
		if(character == '*')
			break;
		else if(isalpha(character)){
			scanf("%s", table[character - 'A']);
		} else {
			scanf("%s", table[character - '0' + 26]);
		}
	}
	// printtable();

	// input context
	while(1){
		scanf("%s", context[contextcount]);
		if(context[contextcount][0] == '*')
			break;
		contextcount ++;
	}
	// printcontext();

	// convert context to code
	for(int i = 0; i < contextcount; i ++){
		int location = 0;
		for(int j = 0; j < 10 && context[i][j] != '\0'; j++){
			int index = 0;
			if(isalpha(context[i][j]))
				index = context[i][j] - 'A';
			else
				index = context[i][j] - '0' + 26;
			for(int m = 0; m < 6 && (table[index][m] != '\0'); m++){
				contextcode[i][location] = table[index][m];
				location ++;
			}
		}
	}
	// printcontextcode();

	// initialize order
	for(int i = 0; i < contextcount; i ++){
		order[i] = i;
	}
	for(int i = contextcount; i < 100; i++){
		order[i] = -1;
	}

	sortcontext();
	// printfsortedcontextcode();

	// input words
	while(1){
		scanf("%s", word);
		if(word[0] == '*')
			break;

		int multiple = 0, question = 1;
		int start = 0, end = contextcount - 1, mid = 0;
		while(start <= end){
			mid = (start + end)/2;
			if(strcmp(contextcode[order[mid]], word) == 0){
				question = 0;
				while(mid - 1 >= 0 && strcmp(contextcode[order[mid-1]], word) == 0){
					multiple = 1;
					mid --;
				}
				printf("%s", context[order[mid]]);

				if(multiple){
					printf("!");
				} else if (mid + 1 < contextcount && strcmp(contextcode[order[mid+1]], word) == 0){
					printf("!");
				}
				printf("\n");
				break;
			} else if (strcmp(contextcode[order[mid]], word) < 0){
				start = mid + 1;		
			} else {
				end = mid - 1;
			}
		}
		if(question){
			// int wordlength = strlen(word);
			// char smallword[]
			// for(int i = 1; i + wordlength < 60 && i < wordlength - 1; i++){
			// 	for(int j = 0; j < wordlength - i; j++){

			// 	}
			// }
			if (strcmp(contextcode[order[mid]], word) < 0){
				start = mid;
				end = mid + 1;
			} else {
				start = mid - 1;
				end = mid;
			}

			int least = -1, extra = 100, lessindex, extraindex;
			for(int i = start; i >= 0; i--){
				least = getless(contextcode[order[i]], word, strlen(contextcode[order[i]]), strlen(word));
				if(least != -1){
					lessindex = i;
					break;
				}
			}
			for(int i = end; i < contextcount; i++){
				int extranum = getextra(contextcode[order[i]], word, strlen(contextcode[order[i]]), strlen(word));
				if(extranum == -1){
					break;
				} else if (extranum < extra){
					extraindex = i;
					extra = extranum;
				}
			}
			if(least != -1 && extra != 100){
				if(least < extra){
					printf("%s", context[order[lessindex]]);
				} else {
					printf("%s", context[order[extraindex]]);
				}
			} else if (least != -1){
				printf("%s", context[order[lessindex]]);
			} else if(extra != 100){
				printf("%s", context[order[extraindex]]);
			}
			printf("?\n");
		}
		
	}
	return 0;
}
