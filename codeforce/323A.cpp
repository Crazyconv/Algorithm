#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	int h, v;
	set<int> asphalted_h;
	set<int> asphalted_v;
	for(int i = 1; i <= n*n; i++){
		scanf("%d%d", &h, &v);
		if(asphalted_h.find(h) == asphalted_h.end() && 
			asphalted_v.find(v) == asphalted_v.end()){
			printf("%d\n", i);
			asphalted_h.insert(h);
			asphalted_v.insert(v);
		}
	}
	return 0;
}