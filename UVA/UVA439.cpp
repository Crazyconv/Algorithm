#define LOCAL

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <utility>
using namespace std;

int d[8][8];
int m[8][2] = {
	{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
	{1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};


int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int s1, s2, t1, t2;
	string line, s, t;
	while(getline(cin, line)){
		stringstream ss(line);
		ss >> s >> t;
		s1 = s[0] - 'a';
		s2 = s[1] - '1';
		t1 = t[0] - 'a';
		t2 = t[1] - '1';

		memset(d, -1, sizeof(d));
		d[s1][s2] = 0;
		if(s1 != t1 || s2 != t2){
			queue<pair<int, int> > points;
			points.push(make_pair(s1, s2));
			while(!points.empty()){
				bool find = false;
				pair<int, int> p = points.front();
				points.pop();
				for(int i = 0; i < 8; i ++){
					int pp1 = p.first+m[i][0], pp2 =p.second+m[i][1];
					if(pp1 >= 0 && pp1 <= 7 && pp2 >=0 && pp2 <=7 &
						d[pp1][pp2] == -1){ 
						d[pp1][pp2] = d[p.first][p.second] + 1;
						if(pp1 == t1 && pp2 == t2){
							find = true;
							break;
						} else {
							points.push(make_pair(pp1, pp2));
						}
					}
				}
				if(find)
					break;
			}
		}
		cout << "To get from " << s << " to " << t << " takes " << d[t1][t2] << " knight moves." << endl;
	}
	return 0;
}