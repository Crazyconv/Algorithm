// http://blog.csdn.net/morewindows/article/details/6709644
// children of n: 2n+1, 2n+2
// parent of n: (n-1)/2

// max heap

#include <cstdio>

#ifndef C_SWAP
#define C_SWAP
void c_swap(int a[], int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
#endif

void fix_up(int a[], int i){
    int temp = a[i];
    int j = (i-1)/2;
    while(j >= 0 && a[j] < temp){
        a[i] = a[j];
        i = j;
        j = (i-1)/2;
    }
    a[i] = temp;
}

void add_num(int a[], int i, int num){
    a[i] = num;
    fix_up(a, i);
}

void fix_down(int a[], int i, int n){
    int j = 2 * i + 1;
    int temp = a[i];
    while(j < n){
        if(j + 1 < n && a[j+1] > a[j])
            j++;
        if(a[j] <= temp)
            break;
        a[i] = a[j];
        i = j;
        j = 2 * i + 1;
    }
    a[i] = temp;
}

void delete_num(int a[], int i, int n){
    c_swap(a, i, n-1);
    fix_down(a, i, n-1);
}

void build_heap(int a[], int n){
    for(int i = n/2 - 1; i >= 0; i--)
        fix_down(a, i, n);
}

void heap_sort(int a[], int n){
    build_heap(a, n);
    for(int i = n-1; i > 0; i--){
        c_swap(a, i, 0);
        fix_down(a, 0, i);
    }
}

// void print(int arr[], int len){
//     for(int i = 0; i < len; i++){
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
// }

// int main(){
//     int arr[] = {9, 2, 4, 7, 3, 7, 12, 8, 7, 2, 10};
//     heap_sort(arr, 11);
//     print(arr, 11);
//     return 0;
// }

