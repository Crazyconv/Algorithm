#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef map<double, vector<double> > DMap;

bool isequal(double x, double y){
	if(fabs(x-y) < 1E-6)
		return true;
	else
		return false;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while(T--){
		int num;
		double x, y;
		DMap points;

		scanf("%d", &num);
		for(int i = 0; i < num; i++){
			scanf("%lf %lf", &x, &y);
			points[y].push_back(x);
		}
		
		bool symm = true;
		double symm_x = 0.0;

		for(DMap::iterator m = points.begin(); m != points.end(); m++){
			vector<double> &v = m->second;
			sort(v.begin(), v.end());
			if(m == points.begin())
				symm_x = v.front() + v.back();
			for(int i = 0; i < (v.size()+1)/2; i++){
				if(!isequal(*(v.begin()+i) + *(v.end()-1-i), symm_x)){
					symm = false;
					break;
				}
			}
			if(!symm){
				break;
			}
		}
		if(symm){
			printf("YES\n");
		} else{
			printf("NO\n");
		}
	}
	return 0;
}