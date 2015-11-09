#define LOCAL

#include <stdio.h>
#include <string.h>

void sort(int arr[], int length){
	int temp;
	for(int i = 0; i < length - 1; i ++){
		for(int j = i+1; j < length; j ++){
			if(arr[i] > arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int m, n;
	double volume;
	int region = 1;
	while(scanf("%d %d", &m, &n) == 2 && m != 0){
		int ele[m*n];
		for(int i = 0; i < m*n; i++){
			scanf("%d", ele+i);
		}
		scanf("%lf", &volume);
		volume /= 100;

		sort(ele, m*n);

		int n_below = 1;
		double counted_volume = 0, water_level = ele[0];
		if(m*n == 1){
			water_level += volume;
		}else{
			while(n_below < m*n){
				while(n_below < m*n && ele[n_below] == water_level){
					n_below ++;
				}

				double temphight = water_level + (volume - counted_volume)/(n_below);
				if(n_below < m * n &&  temphight >= ele[n_below]){
					water_level = ele[n_below];
					counted_volume += ((ele[n_below] - ele[n_below-1]) * n_below);
				} else {
					water_level = temphight;
					break;
				} 
			}
		}
		printf("Region %d\n", region);
		printf("Water level is %.2lf meters.\n", water_level);
		printf("%.2lf percent of the region is under water.\n\n", (double)n_below/m/n*100);
		region ++;
	}
	return 0;
}
