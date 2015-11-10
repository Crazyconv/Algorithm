#include <cstdio>
#include <string>
#include <iostream>

#include "../template/heap.cpp"

using namespace std;

#ifndef C_SWAP
#define C_SWAP
void c_swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
#endif

void print(int arr[], int len){
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void merge_sort(int arr[], int start, int end){
	if(end > start+1){
		int mid = start + (end - start)/2;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid, end);

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

void quick_sort(int a[], int start, int end){
	if(end > start+1){
		int middle = partition(a, start, end);
		quick_sort(a, start, middle);
		quick_sort(a, middle+1, end);
	}
}

void tw_quick_sort(int a[], int start, int end){
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
		tw_quick_sort(a, start, lt);
		tw_quick_sort(a, gt+1, end);
	}
}

void bubble_sort(int a[], int len){
	bool change = true;
	for(int i = len - 1; i >= 1 && change; i --){
		change = false;
		for(int j = 0; j < i; j++){
			if(a[j] > a[j+1]){
				c_swap(a, j, j+1);
				change = true;
			}
		}
	}
}

void insertion_sort(int a[], int len){
	for(int i = 1; i < len; i++){
		int j, temp = a[i];
		for(j = i-1; j >= 0 && a[j] > temp; j--){
			a[j+1] = a[j];
		}
		a[j+1] = temp;
	}
}

// 在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种
// 每次交换一对元素，它们当中至少有一个将被移动到最终位置
// 因此对n个元素的表进行排序总共进行至多n-1次交换
void selection_sort(int a[], int len){
	for(int i = 0; i < len - 1; i++){
		int min_index = i;
		for(int j = i + 1; j < len; j++){
			if(a[j] < a[min_index]){
				min_index = j;
			}
		}
		c_swap(a, min_index, i);
	}
}

// 可能希尔排序最重要的地方在于当用较小步长排序后，以前用的较大步长仍然是有序的。
// 不同步长有不同时间复杂度
// n / 2^i -> O(n^2)
// 2^k - 1 -> O(n^(3/2))
// 2^i*3^j -> O(n * (logn)^2)
void shell_sort(int a[], int len){
	for(int gap = len/2; gap > 0; gap /= 2){
		for(int i = gap; i < len; i++){
			int temp = a[i], j;
			for(j = i - gap; j >= 0 && a[j] > temp; j -= gap){
				a[j+gap] = a[j];
			}
			a[j+gap] = temp;
		}
	}
}

int main(){
	int arr[] = {9, 2, 4, 7, 3, 7, 12, 8, 7, 2, 10};
	heap_sort(arr, 11);
	print(arr, 11);
	return 0;
}