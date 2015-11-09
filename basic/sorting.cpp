#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

void print(int arr[], int len){
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void mergesort(int arr[], int start, int end){
	if(end > start+1){
		int mid = start + (end - start)/2;
		mergesort(arr, start, mid);
		mergesort(arr, mid, end);

		int T[end-start];
		int L = start, R = mid, i = 0;
		while(L != mid || R != end){
			if(R == end || (L != mid && arr[L] < arr[R]))
				T[i++] = arr[L++];
			else
				T[i++] = arr[R++];
		}
		for(i = 0; i < end-start; i++){
			arr[start+i] = T[i];
		}
	}
}

void c_swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int partition(int a[], int start, int end){
	// [start, i) <=
	// (j, end) >
	int pivot = a[start];
	int i = start + 1;
	int j = end - 1;
	while(1){
		if(i > j) break;
		while(i < end && a[i] <= pivot)
			i++;
		while(j >= start && a[j] > pivot)
			j--;
		if(i < j){
			c_swap(a, i, j);
			i++;
			j--;
		}
	}
	c_swap(a, start, j);
	return j; 
}

void quicksort(int a[], int start, int end){
	if(end > start+1){
		int middle = partition(a, start, end);
		quicksort(a, start, middle);
		quicksort(a, middle+1, end);
	}
}

void twquicksort(int a[], int start, int end){
	if(end - start > 1){
		// [start, lt) <
		// [lt, i) =
		// (gt, end) >
		int lt = start;
		int gt = end - 1;
		int pivot = a[start];
		int i = start + 1;
		while(1){
			if(i > gt) break;
			if(a[i] < pivot){
				c_swap(a, i, lt);
				i++; lt++;
			} else if(a[i] > pivot){
				c_swap(a, i, gt);
				gt--;
			} else{
				i++;
			}
		}
		twquicksort(a, start, lt);
		twquicksort(a, gt+1, end);
	}
}

int main(){
	int arr[] = {9, 2, 4, 7, 3, 7, 12, 8, 7, 2, 10};
	//mergesort(arr, 0, 11);
	//twquicksort(arr, 0, 11);
	quicksort(arr, 0, 11);
	print(arr, 11);
	return 0;
}