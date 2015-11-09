#define LOCAL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char table[36][10];
char context[120][16];
char contextcode[120][70];
char word[90];
int contextcount = 0;
int length[120];

int check(char *arr1, char *arr2, int length){
	for(int i = 0; i < length; i++){
		if(*(arr1+i) != *(arr2+i)){
			return 0;
		}
	}
	return 1;
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

int max(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	memset(table, 0, sizeof(table));
	memset(context, 0, sizeof(context));
	memset(contextcode, 0, sizeof(contextcode));
	memset(length, 0, sizeof(length));

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
		length[i] = location;
		contextcode[i][location] = '\0';
	}
	// printcontextcode();


	// input words
	while(1){
		memset(word, 0, sizeof(word));
		scanf("%s", word);
		if(word[0] == '*')
			break;

		int wordlen = strlen(word);
		int match = 0;
		for(int i = 0; i < contextcount; i ++){
			if(length[i] == wordlen){
				if(strcmp(contextcode[i], word) == 0){
					if(!match){
						printf("%s", context[i]);
						match = 1;
					} else {
						printf("!");
						break;
					}
				}
			}
		}
		if(match)
			printf("\n");
		else{
			for(int i = 1; i <= max(wordlen-1, 60-wordlen); i++){
				match = 0;
				for(int j = 0; j < contextcount; j++){
					if(length[j] == wordlen - i && check(contextcode[j], word, wordlen-i)){
						match = 1;
						printf("%s", context[j]);
						break;
					} else if (length[j] == wordlen + i && check(contextcode[j], word, wordlen)){
						match = 1;
						printf("%s", context[j]);
						break;
					}
				}
				if(match){
					break;
				}
			}
			printf("?\n");
		}
	}
	return 0;
}
