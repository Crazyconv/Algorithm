#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct job{
	int p;
	bool my;

	job(int p, bool my): p(p), my(my){}
};

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while(T--){
		int n, my, p;
		vector<int> pl;
		queue<job> pq;
		scanf("%d %d", &n, &my);
		for(int i = 0; i < n; i++){
			scanf("%d", &p);
			pl.push_back(p);
			if(i == my)
				pq.push(job(p, true));
			else
				pq.push(job(p, false));
		}

		sort(pl.begin(), pl.end());

		int time = 0;
		while(1){
			job j = pq.front();
			if(pl.back() > j.p){
				pq.pop();
				pq.push(j);
			} else {
				time ++;
				if(j.my)
					break;
				pq.pop();
				pl.resize(pl.size()-1);
			}
		}
		printf("%d\n", time);
	}

	return 0;
}