#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <sstream>

using namespace std;

void process(string &line){
	for(int i = 0; i < line.length(); i++){
		if(!isalnum(line[i]))
			line[i] = ' ';
	}
}

void getdic(map<string, string> &m){
	string line, key, value;
	getline(cin, line);
	process(line);
	stringstream ss(line);
	while(ss >> key >> value){
		m[key] = value;
	}
}

void printresult(set<string> s, string mark){
	bool first = true;
	cout << mark;
	for(set<string>::iterator i = s.begin(); i != s.end(); i++){
		if(first)
			first = false;
		else
			cout << ",";
		cout << *i;
	}
	cout << endl;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	string line;
	getline(cin, line);

	while(T--){
		map<string, string> m1, m2;
		set<string> add, del, change;
		bool nochanges = true;

		getdic(m1);
		getdic(m2);

		for(map<string, string>::iterator i = m1.begin(); i != m1.end(); i++){
			if(m2.count(i->first)){
				if(i->second != m2[i->first]){
					change.insert(i->first);
				}
			} else {
				del.insert(i->first);
			}
		}
		for(map<string, string>::iterator i = m2.begin(); i != m2.end(); i++){
			if(!m1.count(i->first))
				add.insert(i->first);
		}

		if(!add.empty()){
			printresult(add, "+");
			nochanges = false;
		}

		if(!del.empty()){
			printresult(del, "-");
			nochanges = false;
		}

		if(!change.empty()){
			printresult(change, "*");
			nochanges = false;
		}

		if(nochanges){
			cout << "No changes" << endl;
		}

		cout << endl;
	}
	return 0;
}