#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// 1~n的排列
void permute_1(int n, int *A, int cur){
	if(cur == n){
		printf("permutation 1-%d: ", n);
		for(int i = 0; i < n; i++){
			printf("%d ", A[i]);
		}
		printf("\n");
	} else {
		for(int i = 1; i <= n; i++){
			bool ok = true;
			for(int j = 0; j < cur; j++){
				if(A[j] == i){
					ok = false;
					break;
				}
			}
			if(ok){
				A[cur] = i;
				permute_1(n, A, cur+1);
			}
		}
	}
}

int count(int n, int*A, int num){
	int c = 0;
	for(int i = 0; i < n; i++){
		if(A[i] == num)
			c++;
	}
	return c;
}

// 可重集的排列
void permute_2(int n, int *P, int *A, int cur){
	if(cur == n){
		for(int i = 0; i < n; i++){
			printf("%d ", A[i]);
		}
		printf("\n");
	} else {
		for(int i = 0; i < n;){
			int num = P[i];
			if(count(n, P, num) > count(cur, A, num)){
				A[cur] = num;
				permute_2(n, P, A, cur+1);
			}
			int j;
			for(j = i+1; j < n; j++){
				if(P[j] != num)
					break;
			}
			i = j; 
		}
	}
}

// 增量构造子集
void subset_1(int n, int *A, int cur){	
	for(int i = 0; i < cur; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	if(cur < n){
		int next = cur? A[cur-1]:0;
		for(int i = next+1; i <= n; i++){
			A[cur] = i;
			subset_1(n, A, cur+1);
		}
	}
}

// 位向量法
void subset_2(int n, int *A, int cur){
	if(cur == n){
		for(int i = 1; i <= n; i++){
			if(A[i-1] == 1){
				printf("%d ", i);
			}
		}
		printf("\n");
	} else {
		A[cur] = 1;
		subset_2(n, A, cur+1);
		A[cur] = 0;
		subset_2(n, A, cur+1);
	}
}

// 二进制法
void printsubset(int n, int A){
	for(int i = 1; i <= n; i++){
		if(A & (1<<(i-1))){
			printf("%d ", i);
		}
	}
	printf("\n");
}
void subset_3(int n){
	for(int i = 0; i < (1<<n); i++)
		printsubset(n, i);
}

int main(){
	int A[4] = {0};
	// permute_1(4, A, 0);
	// subset_1(4, A, 0);
	// subset_2(4, A, 0);
	subset_3(4);

	// int P[6] = {4, 2, 5, 2, 4, 6};
	// int B[6];
	// sort(P, P+6);
	// permute_2(6, P, B, 0);
	return 0;
}