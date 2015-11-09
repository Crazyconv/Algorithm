#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	string word;
	set<string> dict;
	while(cin >> word){
		dict.insert(word);
	}

	for(set<string>::iterator s = dict.begin(); s != dict.end(); s++){
		string part1, part2;
		for(int i = 1; i < s->length(); i++){
			part1 = s->substr(0,i);
			if(dict.count(part1)){
				part2 = s->substr(i);
				if(dict.count(part2)){
					cout << *s << endl;
					break;
				}
			}
		}
	}
	return 0;
}