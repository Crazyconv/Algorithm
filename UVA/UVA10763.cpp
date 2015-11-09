#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

typedef map<int, list<int> > IntMap;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int num;
	while(scanf("%d", &num) && num){
		IntMap wishes;
		int s1, s2;
		for (int i = 0; i < num; i ++){
			scanf("%d %d", &s1, &s2);
			if(wishes.count(s2) && wishes[s2].size()){
				list<int> &cans = wishes[s2];
				list<int>::iterator l = std::find(cans.begin(), cans.end(), s1);
				if(l != cans.end())
					cans.erase(l);
				else
					wishes[s1].push_back(s2);
			}else
				wishes[s1].push_back(s2);
		}

		bool fail = false;
		for(IntMap::iterator m = wishes.begin(); m != wishes.end(); m++){
			list<int> cans = m -> second;
			if(cans.size()){
				fail = true;
				break;
			}
		}

		if(fail){
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}
	return 0;
}